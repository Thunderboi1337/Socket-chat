#include "hash_storage.h"

Users *hash_table[TABLE_SIZE];

unsigned int hash(char *name)
{
    int length = strnlen(name, MAX_NAME);

    unsigned int hashed_name = 0;
    for (int i = 0; i < length; i++)
    {
        hashed_name += name[i];
        hashed_name = (hashed_name * name[i] % TABLE_SIZE);
    }

    return hashed_name;
}

bool hash_table_init()
{

    for (int i = 0; i < TABLE_SIZE; i++)
    {
        hash_table[i] = NULL;
    }

    return true;
}

void hash_table_print()
{
    for (int i = 0; i < TABLE_SIZE; i++)
    {
        if (hash_table[i] == NULL)
        {
            printf("\t%i\t---\n", i);
        }
        else
        {
            printf("\t%i\t%s\n", i, hash_table[i]->username);
        }
    }
}

bool hash_table_add_user(Users *User)
{
    bool status = false;

    if (User == NULL)
    {
        status = false;
    }
    else
    {
        int index = hash(User->username);
        for (int i = 0; i < TABLE_SIZE; i++)
        {
            int try = (i + index) % TABLE_SIZE;
            if (hash_table[try] == NULL)
            {
                hash_table[try] = User;
                status = true;

                i = TABLE_SIZE;
            }
            else
            {
                status = false;
            }
        }
    }

    return status;
}
Users *hash_table_lookup(char *name)
{
    int index = hash(name);
    if (hash_table[index] != NULL && strncmp(hash_table[index]->username, name, TABLE_SIZE) == 0)
    {
        return hash_table[index];
    }
    else
    {
        return NULL;
    }
}

Users *hash_table_delete(char *name)
{
    int index = hash(name);
    if (hash_table[index] != NULL && strncmp(hash_table[index]->username, name, TABLE_SIZE) == 0)
    {
        Users *tmp = hash_table[index];
        hash_table[index] = NULL;
        return tmp;
    }
    else
    {

        return NULL;
    }
}