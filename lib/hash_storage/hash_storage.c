#include "hash_storage.h"

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