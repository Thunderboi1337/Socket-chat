#include "tcp_client.h"

int main()
{
    // Create a socket
    int socketFD = create_tcp_ipv4_socket();
    struct sockaddr_in *address = create_tcp_ipv4_adress("127.0.0.1", 2000);

    int result = connect(socketFD, (struct sockaddr *)address, sizeof(*address));

    if (result == 0)
    {
        printf("Connected");
    }

    create_threads(&socketFD);

    send_entries(socketFD);

    // Close the socket
    close(socketFD);

    return 0;
}