#include <stdio.h>
#include "menu.h"
#include "tcp_client.h"

void menu_run(int socket_fd)
{
    char select;
    do
    {
        printf("_____________MENU_____________\n");
        printf("(1) Show registered users\n");
        printf("(2) Select user\n");
        printf("(3) Exit\n");
        printf("______________________________\n");

        select = getchar();
        while (getchar() != '\n')
            ; // Clear the input buffer to remove newline character

        switch (select)
        {
        case '1':
            menu_get_userlist(socket_fd);
            break;

        case '2':
            // select user
            printf("User selection not implemented.\n");
            break;

        case '3':
            // exit
            printf("Exiting.\n");
            return;

        default:
            printf("You didn't select an option dude..... try again\n\n");
        }
    } while (select != '3'); // Loop until the user selects '3' for exit
}

void menu_get_userlist(int socket_fd)
{
    tcp_client_user_request(socket_fd);
}