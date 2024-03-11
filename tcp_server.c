#include <stdbool.h>
#include <unistd.h>
#include <pthread.h>
#include "socket.h"

#define MAX_BUFFER_SIZE 256

struct Accepted_socket
{
        int accepted_sockets_fd;
        struct sockaddr_in address;
        int error;
        bool accpted_successfully;
};

struct Accepted_socket accepted_socketss[10];
int accpted_sockets_count = 0;

struct Accepted_socket *accept_incoming_connections(int server_socket_fd)
{
        struct sockaddr_in client_address;
        int client_address_size = sizeof(struct sockaddr_in);
        int client_socket_fd = accept(server_socket_fd, &client_address, &client_address_size);

        struct Accepted_socket *accepted_sockets = malloc(sizeof(struct Accepted_socket));
        accepted_sockets->address = client_address;
        accepted_sockets->accepted_sockets_fd = client_socket_fd;
        accepted_sockets->accpted_successfully = client_socket_fd > 0;

        if (!accepted_sockets->accpted_successfully)
        {
                accepted_sockets->error = client_socket_fd;
                perror("Accept failed");
        }
        else
        {
                printf("Client accepted!\n");
        }

        return accepted_sockets;
}

void *receive_and_display(void *arg)
{
        int socket_fd = *((int *)arg);

        char msg_buffer[1024];

        while (true)
        {
                ssize_t amount_received = recv(socket_fd, msg_buffer, 1024, 0);

                if (amount_received > 0)
                {
                        msg_buffer[amount_received] = '\0'; // Null-terminate the received data
                        printf("Client response: %s\n", msg_buffer);

                        send_received_msg(msg_buffer, socket_fd);
                }
                else if (amount_received == 0)
                {
                        // Connection closed by the client
                        printf("Client closed the connection\n");
                        break;
                }
        }

        free(arg); // Remember to free the dynamically allocated memory for the socket FD
        return NULL;
}

void start_accept_incoming_Connections(int server_socket_fd)
{
        while (true)
        {
                struct Accepted_socket *client_socket = accept_incoming_connections(server_socket_fd);

                receive_and_display_on_separate_thread(client_socket);
        }
}

void receive_and_display_on_separate_thread(struct Accepted_socket *pSocket)
{
        pthread_t id;
        int *fd = malloc(sizeof(int));
        *fd = pSocket->accepted_sockets_fd;
        pthread_create(&id, NULL, receive_and_display, fd);
}

void send_received_msg(char *buffer, int socket_fd)
{
        for (int i = 0; i < accpted_sockets_count; i++)
        {
                if (accepted_socketss[i].accepted_sockets_fd != socket_fd)
                {
                        send(accepted_socketss[i].accepted_sockets_fd, buffer, strlen(buffer), 0);
                }
        }
}

int main(void)
{
        // creates the socket and address
        int server_socket_fd = create_tcp_ipv4_socket();
        struct sockaddr_in *server_address = create_tcp_ipv4_adress("", 2000);

        // bind the socket to our specified IP and port
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

        start_accept_incoming_Connections(server_socket_fd);

        shutdown(server_socket_fd, SHUT_RDWR);

        return 0;
}
