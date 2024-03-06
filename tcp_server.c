#include "socket.h"

#define MAX_BUFFER_SIZE 256

int main(void)
{

        // creates the socket and adrees
        int server_socket_fd = create_tcp_ipv4_socket();
        struct sockaddr_in *server_adress = create_tcp_ipv4_adress("", 9002);

        // bind the socket to our specifeid IP and port
        int binded = bind(server_socket_fd, (struct sockaddr *)server_adress, sizeof(*server_adress));

        if (binded == 0)
        {
                printf("binding");
        }

        int listend = listen(server_socket_fd, 10);

        if (listend == 0)
        {
                printf("Listen works");
        }

        struct sockaddr_in clientAdress;
        int clientAdressSize = sizeof(struct sockaddr_in);
        int client_socket_fd = accept(server_socket_fd, (struct sockaddr *)&clientAdress, &clientAdressSize);

        if (client_socket_fd == 0)
        {
                printf("client socket accepted");
        }

        char msg_buffer[1024];
        recv(client_socket_fd, msg_buffer, 1024, 0);

        printf("Client response %s", msg_buffer);

        // Close the socket
        close(server_socket_fd);

        return 0;
}
