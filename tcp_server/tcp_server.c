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

void receive_and_display_on_separate_thread(struct Accepted_socket *pSocket);

void send_received_msg(char *buffer, int socket_fd);

struct Accepted_socket *accept_incoming_connections(int server_socket_fd);

void *receive_and_display(void *socket_fd_);

void start_accept_incoming_Connections(int server_socket_fd);

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

        start_accept_incoming_Connections(server_socket_fd);

        shutdown(server_socket_fd, SHUT_RDWR);

        return 0;
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

struct Accepted_socket *accept_incoming_connections(int server_socket_fd)
{
        struct sockaddr_in client_address;
        socklen_t client_address_size = sizeof(struct sockaddr_in);
        int client_socket_fd = accept(server_socket_fd, (struct sockaddr *)&client_address, &client_address_size);

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

                // FUNCTION FOR USERNAME AFTER ACEPTION
        }

        return accepted_sockets;
}

void *receive_and_display(void *socket_fd_)
{
        int *socket_fd_ptr = (int *)socket_fd_;
        int socket_fd = *socket_fd_ptr;

        char msg_buffer[1024];

        while (true)
        {
                ssize_t amount_received = recv(socket_fd, msg_buffer, 1024, 0);

                if (amount_received > 0)
                {
                        msg_buffer[amount_received] = '\0';
                        printf("Client response: %s\n", msg_buffer);

                        send_received_msg(msg_buffer, socket_fd);
                }
                else if (amount_received == 0)
                {

                        printf("Client closed the connection\n");
                        break;
                }
        }

        free(socket_fd_ptr);
        return NULL;
}

void start_accept_incoming_Connections(int server_socket_fd)
{
        int socket_fd = server_socket_fd;

        while (true)
        {
                struct Accepted_socket *client_socket = accept_incoming_connections(socket_fd);
                accepted_socketss[accpted_sockets_count++] = *client_socket;

                receive_and_display_on_separate_thread(client_socket);
        }
}
