#include <stdbool.h>
#include "socket.h"

#define MAX_BUFFER_SIZE 256

int main()
{
    // Create a socket
    int socket_fd = create_tcp_ipv4_socket();
    struct sockaddr_in *adress = create_tcp_ipv4_adress("127.0.0.1", 9002);

    int connection_status = connect(socket_fd, (struct sockaddr *)&adress, sizeof(adress));

    if (connection_status == -1)
    {
        printf("Error connecting to the server\n");
    }

    // Send a message to the server
    char *line = NULL;
    size_t linesSize = 0;
    printf("Type:");

    while (true)
    {
        ssize_t charCount = getline(&line, &linesSize, stdin);

        if (charCount > 0)
        {
            if (strcmp(line, "exit\n") == 0)
            {
                break;
            }

            size_t amountWasSent = send(socket_fd, line, charCount, 0);
        }
    }

    // Close the socket
    close(socket_fd);

    return 0;
}
