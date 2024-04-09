#include <stdio.h>
#include "menu.h"
#include "tcp_client.h"

void menu_run(int socket_fd)
{

    while (1)
    {

        printf("_____________MENU_____________\n");
        printf("(1)Show registerd users\n");
        printf("(2)select user\n");
        printf("(3)exit\n");
        printf("_______________________________\n");

        char select;
        select = getchar();
        switch (select)
        {
        case '1':
            menu_get_userlist(socket_fd);

        case '2':
            // select user

        case '3':
            // exit
            break;

        default:
            printf("You didn't select an option dude..... try again\n\n");
        }
    }
}

void menu_get_userlist(int socket_fd)
{
    tcp_client_user_request(socket_fd);
}
