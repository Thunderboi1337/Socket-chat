
#include "tcp_client.h"

void send_entries(int socketFD)
{
    char *line = NULL;
    size_t lineSize = 0;
    printf("type and we will send(type exit)...\n");

    while (true)
    {
        printf("> ");
        ssize_t charCount = getline(&line, &lineSize, stdin);
        if (charCount > 0)
        {
            line[charCount - 1] = '\0';

            if (strcmp(line, "exit") == 0)
                break;

            ssize_t amountWasSent = send(socketFD, line, strlen(line), 0);
            if (amountWasSent == -1)
            {
                perror("send");
                break;
            }
        }
        else if (charCount == -1)
        {
            perror("getline failed");
            break;
        }
    }

    free(line);
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

void tcp_client_user_request(int socket_fd)
{
    char buffer[256] = "user_list_request";

    ssize_t amountWasSent = send(socket_fd, buffer, strlen(buffer), 0);
}
