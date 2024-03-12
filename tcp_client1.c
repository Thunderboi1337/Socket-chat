#include <stdbool.h>
#include <unistd.h>
#include <pthread.h>
#include "socket.h"

void send_entries(int socketFD)
{
    char *name = NULL;
    size_t nameSize = 0;
    printf("please enter your name?\n");
    ssize_t nameCount = getline(&name, &nameSize, stdin);
    name[nameCount - 1] = 0;

    char *line = NULL;
    size_t lineSize = 0;
    printf("type and we will send(type exit)...\n");

    char buffer[1024];

    while (true)
    {

        ssize_t charCount = getline(&line, &lineSize, stdin);
        line[charCount - 1] = 0;

        sprintf(buffer, "%s:%s", name, line);

        if (charCount > 0)
        {
            if (strcmp(line, "exit") == 0)
                break;

            ssize_t amountWasSent = send(socketFD,
                                         buffer,
                                         strlen(buffer), 0);
        }
    }
}

void *listen_to_msg(void *arg)
{
    int socket_fd = *((int *)arg);

    char msg_buffer[1024];

    while (true)
    {
        ssize_t amount_received = recv(socket_fd, msg_buffer, 1024, 0);

        if (amount_received > 0)
        {
            msg_buffer[amount_received] = 0;
            printf("%s\n", msg_buffer);
        }
        if (amount_received == 0)
        {
            // Connection closed by the client
            printf("Client closed the connection\n");
            break;
        }
    }

    close(socket_fd);
    return NULL;
}

void create_threads(int *socket_fd)
{
    pthread_t id;
    pthread_create(&id, NULL, listen_to_msg, socket_fd);
}

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