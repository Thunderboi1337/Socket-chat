#include "tcp_server.h"

int main(void)
{

    int server_socket_fd = create_tcp_ipv4_socket();
    struct sockaddr_in *server_address = create_tcp_ipv4_adress("", 2000);

    int binded = bind(server_socket_fd, (struct sockaddr *)server_address, sizeof(*server_address));

    if (binded != 0)
    {
        perror("Bind failed");
    }

    int listend = listen(server_socket_fd, 10);

    if (listend != 0)
    {
        perror("Listen failed");
    }

    if (false == setup_hash_table())
    {
        perror("Hashtable failed");
    }

    start_accept_incoming_Connections(server_socket_fd);

    shutdown(server_socket_fd, SHUT_RDWR);

    return 0;
}