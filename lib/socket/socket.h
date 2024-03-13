#ifndef SOCKET_H
#define SOCKET_H

#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <malloc.h>

int create_tcp_ipv4_socket();

struct sockaddr_in *create_tcp_ipv4_adress(char *ip, int port);

#endif