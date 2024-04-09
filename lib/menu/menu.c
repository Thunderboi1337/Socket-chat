#include <stdio.h>
#include "menu.h"

void menu_run(void)
{

    while (1)
    {

        printf("_____________MENU_____________\n");
        printf("(1)Show registerd users\n");
        printf("(2)select user\n");
        printf("(3)exit\n");
        printf("_______________________________\n");

        getchar();
        char select;
        switch (select)
        {
        case 1:
            // request user list

        case 2:
            // select user

        case 3:
            // exit
            break;

        default:
            printf("You didn't select an option dude..... try again\n\n");
        }
    }
}

void menu_get_userlist(void)
{
    tcp_client_user_request();
}
