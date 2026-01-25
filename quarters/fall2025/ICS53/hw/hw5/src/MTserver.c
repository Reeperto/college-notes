#include <pthread.h>
#include <signal.h>
#include <errno.h>

#include "debug.h"
#include "server.h"
#include "protocol.h"
#include "MThelpers.h"

/******DECLARE ALL LOCKS HERE BETWEEN THES LINES FOR MANUAL GRADING************/

pthread_mutex_t charity_log_mutex; // Global lock for the actions log
pthread_mutex_t max_donations_mutex; // Global lock for maxDonations
pthread_mutex_t charities_mutexes[5]; // Per charity lock

/******************************************************************************/

int clientCnt;
uint64_t maxDonations[3];
charity_t charities[5];
FILE* charity_log;

volatile sig_atomic_t sigint_flag = false;

void sigint_handler(int sig) {
    sigint_flag = true;
}

void send_error(int fd) {
    message_t response = { .msgtype = ERROR };
    write(fd, &response, MESSAGE_SIZE);

    LOCK(&charity_log_mutex);
    {
        fprintf(
            charity_log,
            "%d ERROR\n",
            fd
        );
    }
    UNLOCK(&charity_log_mutex);
}

void update_max_donations(int total) {
    LOCK(&max_donations_mutex);
    {
        for (int i = 0; i < 3; ++i) {
            if (total >= maxDonations[i]) {
                for (int j = 2; j > i; --j) {
                    maxDonations[j] = maxDonations[j - 1];
                }

                maxDonations[i] = total;
                break;
            }
        }
    }
    UNLOCK(&max_donations_mutex);
}

bool is_valid_charity(int charity) {
    return 0 <= charity && charity < 5;
}

void* handle_connection(void* fd_param) {
    int client_fd = *((int*)fd_param);
    free(fd_param);

    int donation_total = 0;

    unsigned char* buf[MESSAGE_SIZE];
    ssize_t n_read = 0;

    while (1) {
        n_read = read(client_fd, buf, MESSAGE_SIZE);

        if (n_read < 0) {
            if (errno != EINTR) {
                break;
            }

            if (sigint_flag) {
                update_max_donations(donation_total);
                break;
            }
        }

        message_t msg = *((message_t*)(buf));

        switch (msg.msgtype) {
            case DONATE: {
                int amount = msg.msgdata.donation.amount;
                int charity = msg.msgdata.donation.charity;

                if (!is_valid_charity(charity)) {
                    send_error(client_fd);
                    break;
                }

                donation_total += amount;

                LOCK(&charities_mutexes[charity]);
                {
                    charities[charity].totalDonationAmt += amount;
                    charities[charity].numDonations += 1;

                    if (amount > charities[charity].topDonation) {
                        charities[charity].topDonation = amount;
                    }
                }
                UNLOCK(&charities_mutexes[charity]);

                write(client_fd, buf, MESSAGE_SIZE);

                LOCK(&charity_log_mutex);
                {
                    fprintf(
                        charity_log,
                        "%d DONATE %d %d\n",
                        client_fd,
                        charity,
                        amount
                    );
                }
                UNLOCK(&charity_log_mutex);

                break;
            }

            case CINFO: {
                int charity = msg.msgdata.donation.charity;

                if (!is_valid_charity(charity)) {
                    send_error(client_fd);
                    break;
                }

                message_t response = {0};

                LOCK(&charities_mutexes[charity]);
                {
                    response.msgtype = CINFO;
                    response.msgdata.charityInfo = charities[charity];
                }
                UNLOCK(&charities_mutexes[charity]);

                write(client_fd, &response, MESSAGE_SIZE);

                LOCK(&charity_log_mutex);
                {
                    fprintf(
                        charity_log,
                        "%d CINFO %d\n",
                        client_fd,
                        charity
                    );
                }
                UNLOCK(&charity_log_mutex);

                break;
            }

            case TOP: {
                message_t response = {0};

                LOCK(&max_donations_mutex);
                {
                    response.msgtype = TOP;
                    memcpy(
                        response.msgdata.maxDonations,
                        maxDonations,
                        3 * sizeof(uint64_t)
                    );
                }
                UNLOCK(&max_donations_mutex);

                write(client_fd, &response, MESSAGE_SIZE);

                LOCK(&charity_log_mutex);
                {
                    fprintf(
                        charity_log,
                        "%d TOP\n",
                        client_fd
                    );
                }
                UNLOCK(&charity_log_mutex);

                break;
            }

            case LOGOUT: {
                LOCK(&charity_log_mutex);
                {
                    fprintf(
                        charity_log,
                        "%d LOGOUT\n",
                        client_fd
                    );
                }
                UNLOCK(&charity_log_mutex);

                update_max_donations(donation_total);
                goto close_connection;
            }

            default: {
                send_error(client_fd);
                break;
            }
        }
    }

close_connection:
    close(client_fd);
    return NULL;
}

int main(int argc, char *argv[]) {
    // Arg parsing
    int opt;
    while ((opt = getopt(argc, argv, "h")) != -1) {
        switch (opt) {
            case 'h':
                fprintf(stderr, USAGE_MSG_MT);
                exit(EXIT_FAILURE);
        }
    }

    // 3 positional arguments necessary
    if (argc != 3) {
        fprintf(stderr, USAGE_MSG_MT);
        exit(EXIT_FAILURE);
    }
    unsigned int port_number = atoi(argv[1]);
    char *log_filename = argv[2];

    // INSERT SERVER INITIALIZATION CODE HERE
    charity_log = fopen(log_filename, "w");
    if (!charity_log) {
        exit(2);
    }

    ThreadList threads = {0};

    pthread_mutex_init(&charity_log_mutex, NULL);
    pthread_mutex_init(&max_donations_mutex, NULL);

    for (int i = 0; i < 5; ++i) {
        pthread_mutex_init(&charities_mutexes[i], NULL);
    }

    struct sigaction sigact = {
        .sa_handler = sigint_handler,
    };

    if (sigaction(SIGINT, &sigact, NULL) < 0) {
        fprintf(stderr, "Failed to install signal handler\n");
        exit(EXIT_FAILURE);
    }

    // Initiate server socket for listening
    int listen_fd = socket_listen_init(port_number);
    printf("Currently listening on port: %d.\n", port_number);
    int client_fd;
    struct sockaddr_in client_addr;
    unsigned int client_addr_len = sizeof(client_addr);

    while(1) {
connection_listen:
        if (sigint_flag) {
            goto shutdown_server;
        }

        thread_list_prune(&threads, false);

        client_fd = accept(listen_fd, (SA*)&client_addr, &client_addr_len);

        if (client_fd < 0) {
            if (errno != EINTR) {
                printf("server acccept failed\n");
                exit(EXIT_FAILURE);
            }

            if (sigint_flag) {
                goto shutdown_server;
            } else {
                goto connection_listen;
            }
        }

        int* fd_param = malloc(sizeof(int));
        *fd_param = client_fd;

        pthread_t tid;
        if (pthread_create(&tid, NULL, &handle_connection, fd_param) != 0) {
            error("Failed to spawn thread\n");
            exit(EXIT_FAILURE);
        }

        thread_list_push(&threads, tid);
        clientCnt += 1;
    }

shutdown_server:
    close(listen_fd);
    thread_list_signal(&threads, SIGINT);
    thread_list_prune(&threads, true);
    thread_list_destroy(&threads);

    for (int i = 0; i < 5; ++i) {
        LOCK(&charities_mutexes[i]);
        {
            printf(
                "%d, %u, %lu, %lu\n", 
                i,
                charities[i].numDonations,
                charities[i].topDonation,
                charities[i].totalDonationAmt
            );
        }
        UNLOCK(&charities_mutexes[i]);
    }

    LOCK(&max_donations_mutex);
    {
        fprintf(
            stderr, 
            "%d\n%lu, %lu, %lu\n", 
            clientCnt,
            maxDonations[0],
            maxDonations[1],
            maxDonations[2]
        );
    }
    UNLOCK(&max_donations_mutex);

    LOCK(&charity_log_mutex);
    {
        fclose(charity_log);
    }
    UNLOCK(&charity_log_mutex);

    return 0;
}

int socket_listen_init(int server_port){
    int sockfd;
    struct sockaddr_in servaddr;

    // socket create and verification
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1) {
        printf("socket creation failed...\n");
        exit(EXIT_FAILURE);
    }
    else
        printf("Socket successfully created\n");

    bzero(&servaddr, sizeof(servaddr));

    // assign IP, PORT
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(server_port);

    int opt = 1;

    if(setsockopt(sockfd, SOL_SOCKET, SO_REUSEPORT, (char *)&opt, sizeof(opt))<0)
    {
    	perror("setsockopt");exit(EXIT_FAILURE);
    }

    // Binding newly created socket to given IP and verification
    if ((bind(sockfd, (SA*)&servaddr, sizeof(servaddr))) != 0) {
        printf("socket bind failed\n");
        exit(EXIT_FAILURE);
    }
    else
        printf("Socket successfully binded\n");

    // Now server is ready to listen and verification
    if ((listen(sockfd, 1)) != 0) {
        printf("Listen failed\n");
        exit(EXIT_FAILURE);
    }
    return sockfd;
}


