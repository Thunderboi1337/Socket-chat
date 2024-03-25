#ifndef TCP_SERVER_H
#define TCP_SERVER_H

#include <stdbool.h>
#include <unistd.h>
#include <pthread.h>
#include "socket.h"
#include "hash_storage.h"

struct Accepted_socket
{
    int accepted_sockets_fd;
    struct sockaddr_in address;
    int error;
    bool accpted_successfully;
};

struct Accepted_socket *accept_incoming_connections(int server_socket_fd);

void start_accept_incoming_Connections(int server_socket_fd);

void send_userrequest_on_separate_thread(struct Accepted_socket *pSocket);

void *username_request(void *socket_fd_);

void receive_and_display_on_separate_thread(struct Accepted_socket *pSocket);

void send_received_msg(char *buffer, int socket_fd);

void *receive_and_display(void *socket_fd_);

bool setup_hash_table();

#endif