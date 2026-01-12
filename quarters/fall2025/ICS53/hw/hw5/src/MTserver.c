#include <pthread.h>
#include <signal.h>

#include "server.h"
#include "protocol.h"
#include "MThelpers.h"

/******DECLARE ALL LOCKS HERE BETWEEN THES LINES FOR MANUAL GRADING************/

pthread_mutex_t charity_log_mutex;
pthread_mutex_t stats_mutex;
pthread_mutex_t max_donations_mutex;
pthread_mutex_t charities_mutexes[5];

/******************************************************************************/

// Global variables, statistics collected since server start-up
int clientCnt;             // # of client connections made, Updated by the main thread
uint64_t maxDonations[3];  // 3 highest total donations amounts (sum of all donations to all
                           // charities in one connection), updated by client threads
                           // index 0 is the highest total donation
charity_t charities[5];    // Global variable, one charity per index
FILE* charity_log;

void* handle_connection(void* fd_param) {
    int client_fd = *((int*)fd_param);
    free(fd_param);

    int donation_total = 0;

    unsigned char* buf[MESSAGE_SIZE];
    ssize_t n_read = 0;

    while ((n_read = read(client_fd, buf, MESSAGE_SIZE)) > 0) {
        message_t msg = *((message_t*)(buf));

        switch (msg.msgtype) {
            case DONATE: {
                int amount = msg.msgdata.donation.amount;
                int charity = msg.msgdata.donation.charity;

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
                        3 * sizeof(int)
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

                close(client_fd);

                LOCK(&max_donations_mutex);
                {
                    for (int i = 0; i < 3; ++i) {
                        if (donation_total >= maxDonations[i]) {
                            for (int j = i + 1; j < 3; ++j) {
                                maxDonations[j] = maxDonations[j - 1];
                            }

                            maxDonations[i] = donation_total;
                            break;
                        }
                    }
                }
                UNLOCK(&max_donations_mutex);
            }

            default: {
                message_t response = { .msgtype = ERROR };
                write(client_fd, &response, MESSAGE_SIZE);

                LOCK(&charity_log_mutex);
                {
                    fprintf(
                        charity_log,
                        "%d ERROR\n",
                        client_fd
                    );
                }
                UNLOCK(&charity_log_mutex);
            }
        }
    }

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
    FILE* log_file = fopen(log_filename, "w");
    if (!log_file) {
        exit(2);
    }

    ThreadList threads = {0};

    pthread_mutex_init(&charity_log_mutex, NULL);
    pthread_mutex_init(&stats_mutex, NULL);
    pthread_mutex_init(&max_donations_mutex, NULL);

    for (int i = 0; i < 5; ++i) {
        pthread_mutex_init(&charities_mutexes[i], NULL);
    }

    // Initiate server socket for listening
    int listen_fd = socket_listen_init(port_number);
    printf("Currently listening on port: %d.\n", port_number);
    int client_fd;
    struct sockaddr_in client_addr;
    unsigned int client_addr_len = sizeof(client_addr);

    while(1) {
        thread_list_prune(&threads);

        client_fd = accept(listen_fd, (SA*)&client_addr, &client_addr_len);
        if (client_fd < 0) {
            printf("server acccept failed\n");
            exit(EXIT_FAILURE);
        }

        int* fd_param = malloc(sizeof(int));

        pthread_t tid;
        if (pthread_create(&tid, NULL, &handle_connection, fd_param) != 0) {
        }

        thread_list_push(&threads, tid);
        clientCnt += 1;
    }

    close(listen_fd);
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


