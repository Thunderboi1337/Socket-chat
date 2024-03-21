#ifndef HASH_STORAGE_H
#define HASH_STORAGE_H

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define MAX_NAME 256
#define TABLE_SIZE 20
#define DELETED_NODE (Users *)(0xFFFFFFFFFFFFFFFFUL)

typedef struct
{

    int socket_fd;
    char *username;

} Users;

unsigned int hash(char *name);

bool hash_table_init();

void hash_table_print();

bool hash_table_add_user(Users *User);

Users *hash_table_lookup(char *name);

Users *hash_table_delete(char *name);

#endif