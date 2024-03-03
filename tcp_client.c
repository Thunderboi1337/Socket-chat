#include <stdio.h>
#include <stdlib.h>

#include <sys/types.h>
#include <WinSock.h>
#include <winsock2.h>

#include <Ws2tcpip.h>



int main(void)
{

        // create a socket
        int network_socket;
        network_socket = socket(AF_INET, SOCK_STREAM, 0);

        // Specift an adress family for the socket
        struct sockaddr_in server_address;
        server_address.sin_family = AF_INET;
        server_address.sin_port = htons(9002);
        server_address.sin_addr.s_addr = INADDR_ANY;


        int connection_status = connect(network_socket, (struct sockaddr *) &server_address, sizeof(server_address));

        if(connection_status == -1)
        {
            printf("There was a connection ERROR");

        }

        //recives data from server
        char server_response[254];
        recv(network_socket, &server_address, sizeof(server_response), 0);

        // print out the server repsones
        printf("The server response: %s\n ", server_response );


        close(network_socket);



    return 0;
}