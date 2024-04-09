#ifndef TCP_CLIENT_H
#define TCP_CLIENT_H

#include <stdbool.h>
#include <unistd.h>
#include <pthread.h>
#include "socket.h"

void send_name(int socketFD);

void send_entries(int socketFD);

void *listen_to_msg(void *arg);

void create_threads(int *socket_fd);

void tcp_client_user_request(int socket_fd);

#endif