#include "hash_storage.h"

Users test_user;

int main(void)
{

    Users Dude = {.username = "Dude"};
    Users Doris = {.username = "Doris"};
    Users Bob = {.username = "Bob"};
    Users Ida = {.username = "Ida"};
    Users Marcus = {.username = "Marcus"};
    Users Soufien = {.username = "Soufien"};
    Users Daniel = {.username = "Daniel"};
    Users Martins = {.username = "Martins"};
    Users Homajon = {.username = "Homajon"};

    hash_table_init();

    hash_table_add_user(&Dude);
    hash_table_add_user(&Doris);
    hash_table_add_user(&Bob);
    hash_table_add_user(&Ida);
    hash_table_add_user(&Marcus);
    hash_table_add_user(&Soufien);
    hash_table_add_user(&Daniel);
    hash_table_add_user(&Martins);
    hash_table_add_user(&Homajon);

    hash_table_print("");

    hash_table_lookup("Ida");
    hash_table_lookup("Jens");
    hash_table_lookup("Doris");

    hash_table_delete("Doris");

    hash_table_lookup("Doris");

    hash_table_delete("Doris");

    hash_table_print();

    return 0;
}