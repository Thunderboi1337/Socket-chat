#ifndef HASH_STORAGE_H
#define HASH_STORAGE_H

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define MAX_NAME 256
#define TABLE_SIZE 20

typedef struct
{
    char username[MAX_NAME];

} Users;

unsigned int hash(char *name);

#endif