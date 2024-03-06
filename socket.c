#include "socket.h"

int create_tcp_ipv4_socket()
{
    return socket(AF_INET, SOCK_STREAM, 0);
}

struct sockaddr_in *create_tcp_ipv4_adress(char *ip, int port)
{

    struct sockaddr_in *adress = malloc(sizeof(struct sockaddr_in));
    adress->sin_family = AF_INET;
    adress->sin_port = htons(port);
    inet_pton(AF_INET, ip, &adress->sin_addr.s_addr);
    return adress;
}