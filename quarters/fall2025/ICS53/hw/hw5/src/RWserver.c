#include "debug.h"
#include "protocol.h"
#include "RWhelpers.h"
#include "server.h"

#include <errno.h>
#include <pthread.h>
#include <semaphore.h>
#include <signal.h>

/*******DECLARE ALL LOCKS HERE BETWEEN THES LINES FOR MANUAL GRADING***********/

pthread_mutex_t client_cnt_mutex; // Global lock for client count
pthread_mutex_t charity_log_mutex; // Global lock for the actions log

// Reader priortized RW-locking for charity data
int charities_reader_count = 0; 
pthread_mutex_t charities_reader_lock;
sem_t charities_sem;

// Reader priortized RW-locking for max donations
int max_donations_reader_count = 0; 
pthread_mutex_t max_donations_reader_lock;
sem_t max_donations_sem;

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
    RW_W_GET(&max_donations_sem);
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
    RW_W_RELEASE(&max_donations_sem);
}

bool is_valid_charity(int charity) {
    return 0 <= charity && charity < 5;
}

void* writer_thread(void* port_param) {
    int writer_port = *((int*)port_param);
    free(port_param);

    int writer_listen_fd = socket_listen_init(writer_port); 

    struct sockaddr_in client_addr;
    unsigned int client_addr_len = sizeof(client_addr);
    int client_fd;

    while (1) {
connection_listen:
        client_fd = accept(writer_listen_fd, (SA*)&client_addr, &client_addr_len);

        if (client_fd < 0) {
            if (errno != EINTR) {
                printf("server acccept failed\n");
                exit(EXIT_FAILURE);
            }

            if (sigint_flag) {
                goto quit_thread;
            } else {
                goto connection_listen;
            }
        }

        LOCK(&client_cnt_mutex);
        {
            clientCnt += 1;
        }
        UNLOCK(&client_cnt_mutex);

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

                    RW_W_GET(&charities_sem);
                    {
                        charities[charity].totalDonationAmt += amount;
                        charities[charity].numDonations += 1;

                        if (amount > charities[charity].topDonation) {
                            charities[charity].topDonation = amount;
                        }
                    }
                    RW_W_RELEASE(&charities_sem);

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
    }

quit_thread:
    return NULL;
}

void* handler_reader_connection(void* fd_param) {
    int client_fd = *((int*)fd_param);
    free(fd_param);

    unsigned char* buf[MESSAGE_SIZE];
    ssize_t n_read = 0;

    while (1) {
        n_read = read(client_fd, buf, MESSAGE_SIZE);

        if (n_read < 0) {
            if (errno != EINTR) {
                break;
            }

            if (sigint_flag) {
                break;
            }
        }

        message_t msg = *((message_t*)(buf));

        switch (msg.msgtype) {
            case CINFO: {
                int charity = msg.msgdata.donation.charity;

                if (!is_valid_charity(charity)) {
                    send_error(client_fd);
                    break;
                }

                message_t response = {0};

                RW_R_GET(&charities_reader_lock, &charities_sem, &charities_reader_count);
                {
                    response.msgtype = CINFO;
                    response.msgdata.charityInfo = charities[charity];
                }
                RW_R_RELEASE(&charities_reader_lock, &charities_sem, &charities_reader_count);

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

                RW_R_GET(&max_donations_reader_lock, &max_donations_sem, &max_donations_reader_count);
                {
                    response.msgtype = TOP;
                    memcpy(
                        response.msgdata.maxDonations,
                        maxDonations,
                        3 * sizeof(uint64_t)
                    );
                }
                RW_R_RELEASE(&max_donations_reader_lock, &max_donations_sem, &max_donations_reader_count);

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

            case STATS: {
                charity_t low = charities[0];
                int low_idx = 0;

                charity_t high = charities[0];
                int high_idx = 0;

                RW_R_GET(&charities_reader_lock, &charities_sem, &charities_reader_count);
                {
                    for (int i = 0; i < 5; ++i) {
                        if (charities[i].totalDonationAmt > high.totalDonationAmt) {
                            high = charities[i];
                            high_idx = i;
                        } else if (charities[i].totalDonationAmt < low.totalDonationAmt) {
                            low = charities[i];
                            low_idx = i;
                        }
                    }
                }
                RW_R_RELEASE(&charities_reader_lock, &charities_sem, &charities_reader_count);

                message_t response = {0};

                response.msgtype = STATS;
                response.msgdata.stats.charityID_low = low_idx;
                response.msgdata.stats.amount_low = low.totalDonationAmt;
                response.msgdata.stats.charityID_high = high_idx;
                response.msgdata.stats.amount_high = high.totalDonationAmt;

                write(client_fd, &response, MESSAGE_SIZE);

                LOCK(&charity_log_mutex);
                {
                    fprintf(
                        charity_log,
                        "%d STATS %d:%lu %d:%lu\n",
                        client_fd,
                        high_idx,
                        high.totalDonationAmt,
                        low_idx,
                        low.totalDonationAmt
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
                fprintf(stderr, USAGE_MSG_RW);
                exit(EXIT_FAILURE);
        }
    }

    // 3 positional arguments necessary
    if (argc != 4) {
        fprintf(stderr, USAGE_MSG_RW);
        exit(EXIT_FAILURE);
    }
    unsigned int r_port_number = atoi(argv[1]);
    unsigned int w_port_number = atoi(argv[2]);
    char *log_filename = argv[3];

    // INSERT SERVER INITIALIZATION CODE HERE
    ThreadList threads = {0};

    pthread_mutex_init(&client_cnt_mutex, NULL);
    pthread_mutex_init(&charity_log_mutex, NULL);

    pthread_mutex_init(&charities_reader_lock, NULL);
    sem_init(&charities_sem, false, 1);

    pthread_mutex_init(&max_donations_reader_lock, NULL);
    sem_init(&max_donations_sem, false, 1);

    charity_log = fopen(log_filename, "w");
    if (!charity_log) {
        exit(2);
    }

    struct sigaction sigact = {
        .sa_handler = sigint_handler,
    };

    if (sigaction(SIGINT, &sigact, NULL) < 0) {
        fprintf(stderr, "Failed to install signal handler\n");
        exit(EXIT_FAILURE);
    }

    // CREATE WRITER THREAD HERE
    int* writer_port = malloc(sizeof(int));
    *writer_port = w_port_number;

    pthread_t writer_thread_tid;
    if (pthread_create(&writer_thread_tid, NULL, &writer_thread, writer_port) != 0) {
        error("Failed to spawn writer thread");
        exit(EXIT_FAILURE);
    }
    thread_list_push(&threads, writer_thread_tid);

    // Initiate server socket for listening for reader clients
    int reader_listen_fd = socket_listen_init(r_port_number); 
    printf("Listening for readers on port %d.\n", r_port_number);

    int reader_fd;
    struct sockaddr_in client_addr;
    unsigned int client_addr_len = sizeof(client_addr);

    while(1) {
connection_listen:
        if (sigint_flag) {
            goto shutdown_server;
        }

        thread_list_prune(&threads, false);

        reader_fd = accept(reader_listen_fd, (SA*)&client_addr, &client_addr_len);

        if (reader_fd < 0) {
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
        *fd_param = reader_fd;

        pthread_t tid;
        if (pthread_create(&tid, NULL, &handler_reader_connection, fd_param) != 0) {
            error("Failed to spawn thread\n");
            exit(EXIT_FAILURE);
        }

        thread_list_push(&threads, tid);

        LOCK(&client_cnt_mutex);
        {
            clientCnt += 1;
        }
        UNLOCK(&client_cnt_mutex);
    }

shutdown_server:
    thread_list_signal(&threads, SIGINT);
    thread_list_prune(&threads, true);
    thread_list_destroy(&threads);

    close(reader_listen_fd);

    RW_R_GET(&charities_reader_lock, &charities_sem, &charities_reader_count);
    for (int i = 0; i < 5; ++i) {
        printf(
            "%d, %u, %lu, %lu\n", 
            i,
            charities[i].numDonations,
            charities[i].topDonation,
            charities[i].totalDonationAmt
        );
    }
    RW_R_RELEASE(&charities_reader_lock, &charities_sem, &charities_reader_count);

    RW_R_GET(&max_donations_reader_lock, &max_donations_sem, &max_donations_reader_count);
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
    RW_R_RELEASE(&max_donations_reader_lock, &max_donations_sem, &max_donations_reader_count);

    LOCK(&charity_log_mutex);
    {
        fclose(charity_log);
    }
    UNLOCK(&charity_log_mutex);

    // pthread_mutex_destroy(&client_cnt_mutex);
    // pthread_mutex_destroy(&charity_log_mutex);
    // pthread_mutex_destroy(&charities_reader_lock);
    // sem_destroy(&charities_sem);
    // pthread_mutex_destroy(&max_donations_reader_lock);
    // sem_destroy(&max_donations_sem);

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


