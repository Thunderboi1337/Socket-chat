#include "unity.h"
#include "hash_storage.h"

Users test_user;

void setUp(void) {}

void tearDown(void) {}

void test_hash_delete_function(void)
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
    Users Dick = {.username = "Dick"};
    Users James = {.username = "James"};
    Users Oliver = {.username = "Oliver"};

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
    hash_table_add_user(&Dick);
    hash_table_add_user(&James);
    hash_table_add_user(&Oliver);

    hash_table_print();

    hash_table_delete("Dude");
    hash_table_delete("Doris");
    hash_table_delete("Bob");
    hash_table_delete("Ida");
    hash_table_delete("Marcus");
    hash_table_delete("Soufien");
    hash_table_delete("Daniel");
    hash_table_delete("Martins");
    hash_table_delete("Homajon");
    hash_table_delete("Dick");
    hash_table_delete("James");
    hash_table_delete("Oliver");

    TEST_ASSERT_FALSE(hash_table_lookup("Dude"));
    TEST_ASSERT_FALSE(hash_table_lookup("Doris"));
    TEST_ASSERT_FALSE(hash_table_lookup("Bob"));
    TEST_ASSERT_FALSE(hash_table_lookup("Ida"));
    TEST_ASSERT_FALSE(hash_table_lookup("Marcus"));
    TEST_ASSERT_FALSE(hash_table_lookup("Soufien"));
    TEST_ASSERT_FALSE(hash_table_lookup("Daniel"));
    TEST_ASSERT_FALSE(hash_table_lookup("Martins"));
    TEST_ASSERT_FALSE(hash_table_lookup("Homajon"));
    TEST_ASSERT_FALSE(hash_table_lookup("Dick"));
    TEST_ASSERT_FALSE(hash_table_lookup("James"));
    TEST_ASSERT_FALSE(hash_table_lookup("Oliver"));

    hash_table_print();
}

void test_same_name_error(void)
{

    Users Oliver = {.username = "Oliver"};

    hash_table_init();

    hash_table_add_user(&Oliver);
    hash_table_add_user(&Oliver);
    hash_table_add_user(&Oliver);

    hash_table_print();

    hash_table_delete("Oliver");

    TEST_ASSERT_FALSE(hash_table_lookup("Oliver"));
}

int main(void)
{

    UNITY_BEGIN();

    RUN_TEST(test_hash_delete_function);

    RUN_TEST(test_same_name_error);

    return UNITY_END();
}