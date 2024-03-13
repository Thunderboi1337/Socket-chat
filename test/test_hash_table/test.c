#include "hash_storage.h"

Users test_user;

int main(void)
{

    printf("Jacob => %u\n", hash("Jacob"));
    printf("Denis => %u\n", hash("Denis"));
    printf("Lars => %u\n", hash("Lars"));
    printf("Lasse => %u\n", hash("Lasse"));

    return 0;
}