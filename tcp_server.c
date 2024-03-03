#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <WinSock.h>
#include <winsock2.h>

#include <Ws2tcpip.h>



int main(void)
{

        char server_message[256] = "You have reached the server";

        // creates the socket
        int server_socket;
        server_socket = socket(AF_INET, SOCK_STREAM, 0);

        // define the server address

        struct sockaddr_in server_address;
        server_address.sin_family = AF_INET;
        server_address.sin_port = htons(9002);
        server_address.sin_addr.s_addr = INADDR_ANY;

        //bind the socket to our specifeid IP and port
        bind(server_socket, (struct sockaddr*) &server_address, sizeof(server_address);

        listen(server_socket, 5);

        int client_socket;
        client_socket = accept(server_socket, NULL, NULL);

        send(client_socket, server_message, sizeof(server_message), 0);


        return 0;

}

