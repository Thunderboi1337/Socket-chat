#include "hash_storage.h"

static bool hash_table_init_state = false;

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

    hash_table_init_state = true;

    return hash_table_init_state;
}

void hash_table_print()
{
    printf("BEGIN---\n");

    for (int i = 0; i < TABLE_SIZE; i++)
    {
        if (hash_table[i] == NULL)
        {
            printf("\t%i\t---\n", i + 1);
        }
        else if (hash_table[i] == DELETED_NODE)
        {

            printf("\t%i\t---d\n", i + 1);
        }
        else
        {
            printf("\t%i\t%s\n", i + 1, hash_table[i]->username);
        }
    }

    printf("END-----\n");
}

bool hash_table_add_user(Users *User)
{
    bool status = false;

    if (hash_table_init_state)
    {

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
                else if (hash_table[try] != NULL && strncmp(hash_table[try]->username, User->username, TABLE_SIZE) == 0)
                {
                    printf("User already added \n");
                    status = false;
                    i = TABLE_SIZE;
                }
                else if (hash_table[try] == DELETED_NODE)
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
    }
    else
    {
        printf("Hash_table not init");
    }

    return status;
}
Users *hash_table_lookup(char *name)
{
    Users *result = NULL;

    if (hash_table_init_state)
    {
        int index = hash(name);
        for (int i = 0; i < TABLE_SIZE; i++)
        {
            int try = (i + index) % TABLE_SIZE;
            if (hash_table[try] == NULL)
            {
                printf("User not found\n");
                break;
            }
            else if (hash_table[try] == DELETED_NODE)
                continue;
            else if (hash_table[try] != NULL && strncmp(hash_table[try]->username, name, TABLE_SIZE) == 0)
            {
                printf("User found %s\n", name);
                result = hash_table[try];
                break;
            }
        }
    }
    else
    {
        printf("Hash_table not initialized\n");
    }

    return result;
}

Users *hash_table_delete(char *name)
{
    Users *result = NULL;

    if (hash_table_init_state)
    {
        int index = hash(name);
        for (int i = 0; i < TABLE_SIZE; i++)
        {
            int try = (i + index) % TABLE_SIZE;
            if (hash_table[try] == NULL)
            {
                break;
            }
            else if (hash_table[try] == DELETED_NODE)
                continue;
            else if (strncmp(hash_table[try]->username, name, TABLE_SIZE) == 0)
            {
                result = hash_table[try];
                hash_table[try] = DELETED_NODE;
                break;
            }
        }
    }
    else
    {
        printf("Hash_table not initialized\n");
    }

    return result;
}

int hash_table_get_socket(char *name)
{
    int socket = -1; // if user is not found

    if (hash_table_init_state)
    {
        int index = hash(name);
        for (int i = 0; i < TABLE_SIZE; i++)
        {
            int try = (i + index) % TABLE_SIZE;
            if (hash_table[try] == NULL)
            {
                printf("User not found\n");
                break;
            }
            else if (hash_table[try] == DELETED_NODE)
                continue;
            else if (hash_table[try] != NULL && strncmp(hash_table[try]->username, name, TABLE_SIZE) == 0)
            {
                printf("User found %s\n", name);
                socket = hash_table[try]->socket_fd;
                break;
            }
        }
    }
    else
    {
        printf("Hash_table not initialized\n");
    }

    return socket;
}