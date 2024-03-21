#include <stdbool.h>
#include <unistd.h>
#include <pthread.h>
#include "socket.h"
#include "hash_storage.h"

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

struct Accepted_socket *accept_incoming_connections(int server_socket_fd);

void start_accept_incoming_Connections(int server_socket_fd);

void send_userrequest_on_separate_thread(struct Accepted_socket *pSocket);

void *username_request(void *socket_fd_);

void receive_and_display_on_separate_thread(struct Accepted_socket *pSocket);

void send_received_msg(char *buffer, int socket_fd);

void *receive_and_display(void *socket_fd_);

bool setup_hash_table();

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
        }

        return accepted_sockets;
}

void start_accept_incoming_Connections(int server_socket_fd)
{
        int socket_fd = server_socket_fd;

        while (true)
        {
                struct Accepted_socket *client_socket = accept_incoming_connections(socket_fd);
                accepted_socketss[accpted_sockets_count++] = *client_socket;

                send_userrequest_on_separate_thread(client_socket);

                // receive_and_display_on_separate_thread(client_socket);
        }
}

void send_userrequest_on_separate_thread(struct Accepted_socket *pSocket)
{
        pthread_t id;
        int *fd = malloc(sizeof(int));
        *fd = pSocket->accepted_sockets_fd;
        pthread_create(&id, NULL, username_request, fd);
}

void *username_request(void *socket_fd_)
{
        int *socket_fd_ptr = (int *)socket_fd_;
        int socket_fd = *socket_fd_ptr;

        char buffer[1024] = "Please enter your username: ";

        send(socket_fd, buffer, strlen(buffer), 0);

        Users *user = malloc(sizeof(Users));

        char username[MAX_BUFFER_SIZE];
        ssize_t amount_received = recv(socket_fd, username, MAX_BUFFER_SIZE - 1, 0);
        if (amount_received > 0)
        {
                username[amount_received] = '\0';
                printf("Username received from client: %s\n", username);

                user->socket_fd = socket_fd;
                user->username = strdup(username);
        }
        else
        {
                printf("No username received\n");
        }

        hash_table_add_user(user);

        hash_table_lookup(user->username);

        // Register username and socket_fd in the hash table
        //

        free(user->username);
        free(user);

        return NULL;
        // Send message to socket asking for name then store name
}

void receive_and_display_on_separate_thread(struct Accepted_socket *pSocket)
{
        pthread_t id;
        int *fd = malloc(sizeof(int));
        *fd = pSocket->accepted_sockets_fd;
        pthread_create(&id, NULL, receive_and_display, fd);
}

void *receive_and_display(void *socket_fd_)
{
        int *socket_fd_ptr = (int *)socket_fd_;
        int socket_fd = *socket_fd_ptr;

        char msg_buffer[1024];

        // get name of person to whom to write first..

        // int socket_fd = hash_table_get_socket();

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

bool setup_hash_table()
{
        bool status = hash_table_init();

        return status;
}