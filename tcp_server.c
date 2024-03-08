#include "socket.h"
#include <stdbool.h>
#include <pthread.h>

#define MAX_BUFFER_SIZE 256

struct Accepted_sockets
{
        int accepted_sockets_fd;
        struct sockaddr_in address;
        int error;
        bool accpted_successfully;
};

struct Accepted_sockets *accept_incoming_connections(int server_socket_fd);

void receive_and_display(int socketfd);

void start_accept_incoming_Connections(int server_socket_fd);

void accept_new_connetions_receive_n_display(int server_socket_fd);

receive_and_display_on_separate_thread(struct Accepted_sockets *server_socket_fd);

int main(void)
{

        // creates the socket and adrees
        int server_socket_fd = create_tcp_ipv4_socket();
        struct sockaddr_in *server_adress = create_tcp_ipv4_adress("127.0.0.1", 9002);

        // bind the socket to our specifeid IP and port
        int binded = bind(server_socket_fd, (struct sockaddr *)server_adress, sizeof(*server_adress));

        if (binded == 0)
        {
                printf("Binding successful\n");
        }
        else
        {
                perror("Bind failed");
        }

        int listend = listen(server_socket_fd, 10);

        if (listend == 0)
        {
                printf("Listen works\n");
        }
        else
        {
                perror("Listen failed");
        }

        struct Accepted_sockets *client_socket_fd = accept_incoming_connections(server_socket_fd);

        shutdown(server_socket_fd, SHUT_RDWR);

        return 0;
}

struct Accepted_sockets *accept_incoming_connections(int server_socket_fd)
{
        struct sockaddr_in clientAdress;
        int clientAdressSize = sizeof(struct sockaddr_in);
        int client_socket_fd = accept(server_socket_fd, (struct sockaddr *)&clientAdress, &clientAdressSize);

        struct Accepted_sockets *Accepted_sockets = malloc(sizeof(struct Accepted_sockets));
        Accepted_sockets->address = clientAdress;
        Accepted_sockets->accepted_sockets_fd = client_socket_fd;
        Accepted_sockets->accpted_successfully = client_socket_fd > 0;

        if (!Accepted_sockets->accpted_successfully)
        {
                Accepted_sockets->error = client_socket_fd;
        }

        return Accepted_sockets;
}

void receive_and_display(int socket_fd)
{
        char msg_buffer[1024];

        while (true)
        {

                ssize_t amountReceived = recv(socket_fd, msg_buffer, 1024, 0);

                if (amountReceived > 0)
                {
                        msg_buffer[amountReceived] = 0;
                        printf("Client response %s", msg_buffer);
                }
                if (amountReceived < 0)
                {
                        break;
                }
        }

        close(socket_fd);
}

void start_accept_incoming_Connections(int server_socket_fd)
{
        pthread_t id;
        pthread_create(&id, NULL, accept_new_connetions_receive_n_display, server_socket_fd);
}

void accept_new_connetions_receive_n_display(int server_socket_fd)
{
        while (true)
        {
                struct Accepted_sockets *client_socket_fd = accept_incoming_connections(server_socket_fd);

                receive_and_display_on_separate_thread(client_socket_fd);
        }
}

receive_and_display_on_separate_thread(struct Accepted_sockets *socket_fd)
{
        pthread_t id;
        pthread_create(&id, NULL, receive_and_display, socket_fd->accepted_sockets_fd);

        close(socket_fd->accepted_sockets_fd);
}