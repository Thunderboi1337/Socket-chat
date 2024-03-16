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

    TEST_ASSERT_TRUE(hash_table_init());

    TEST_ASSERT_TRUE(hash_table_add_user(&Dude));
    TEST_ASSERT_TRUE(hash_table_add_user(&Doris));
    TEST_ASSERT_TRUE(hash_table_add_user(&Bob));
    TEST_ASSERT_TRUE(hash_table_add_user(&Ida));
    TEST_ASSERT_TRUE(hash_table_add_user(&Marcus));
    TEST_ASSERT_TRUE(hash_table_add_user(&Soufien));
    TEST_ASSERT_TRUE(hash_table_add_user(&Daniel));
    TEST_ASSERT_TRUE(hash_table_add_user(&Martins));
    TEST_ASSERT_TRUE(hash_table_add_user(&Homajon));
    TEST_ASSERT_TRUE(hash_table_add_user(&Dick));
    TEST_ASSERT_TRUE(hash_table_add_user(&James));
    TEST_ASSERT_TRUE(hash_table_add_user(&Oliver));

    hash_table_print();

    TEST_ASSERT_EQUAL_STRING("Dude", hash_table_delete("Dude"));
    TEST_ASSERT_EQUAL_STRING("Doris", hash_table_delete("Doris"));
    TEST_ASSERT_EQUAL_STRING("Bob", hash_table_delete("Bob"));
    TEST_ASSERT_EQUAL_STRING("Ida", hash_table_delete("Ida"));
    TEST_ASSERT_EQUAL_STRING("Marcus", hash_table_delete("Marcus"));
    TEST_ASSERT_EQUAL_STRING("Soufien", hash_table_delete("Soufien"));
    TEST_ASSERT_EQUAL_STRING("Daniel", hash_table_delete("Daniel"));
    TEST_ASSERT_EQUAL_STRING("Martins", hash_table_delete("Martins"));
    TEST_ASSERT_EQUAL_STRING("Homajon", hash_table_delete("Homajon"));
    TEST_ASSERT_EQUAL_STRING("Dick", hash_table_delete("Dick"));
    TEST_ASSERT_EQUAL_STRING("James", hash_table_delete("James"));
    TEST_ASSERT_EQUAL_STRING("Oliver", hash_table_delete("Oliver"));

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

    TEST_ASSERT_TRUE(hash_table_init());

    hash_table_add_user(&Oliver);
    hash_table_add_user(&Oliver);
    hash_table_add_user(&Oliver);

    hash_table_print();

    TEST_ASSERT_EQUAL_STRING("Oliver", hash_table_delete("Oliver"));
    TEST_ASSERT_EQUAL_PTR(NULL, hash_table_delete("Oliver"));

    hash_table_print();

    TEST_ASSERT_FALSE(hash_table_lookup("Oliver"));
}

void test_max_amount(void)
{

    TEST_ASSERT_TRUE(hash_table_init());

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
    Users Adam = {.username = "Adam"};
    Users Jonas = {.username = "Jonas"};
    Users Kim = {.username = "Kim"};
    Users Erik = {.username = "Erik"};
    Users Emil = {.username = "Emil"};
    Users Johan = {.username = "Johan"};
    Users Gustaf = {.username = "Gustaf"};
    Users Jens = {.username = "Jens"};
    Users Overkill = {.username = "Overkill"};

    hash_table_print();

    TEST_ASSERT_TRUE(hash_table_add_user(&Dude));
    TEST_ASSERT_TRUE(hash_table_add_user(&Doris));
    TEST_ASSERT_TRUE(hash_table_add_user(&Bob));
    TEST_ASSERT_TRUE(hash_table_add_user(&Ida));
    TEST_ASSERT_TRUE(hash_table_add_user(&Marcus));
    TEST_ASSERT_TRUE(hash_table_add_user(&Soufien));
    TEST_ASSERT_TRUE(hash_table_add_user(&Daniel));
    TEST_ASSERT_TRUE(hash_table_add_user(&Martins));
    TEST_ASSERT_TRUE(hash_table_add_user(&Homajon));
    TEST_ASSERT_TRUE(hash_table_add_user(&Dick));
    TEST_ASSERT_TRUE(hash_table_add_user(&James));
    TEST_ASSERT_TRUE(hash_table_add_user(&Oliver));
    TEST_ASSERT_TRUE(hash_table_add_user(&Adam));
    TEST_ASSERT_TRUE(hash_table_add_user(&Jonas));
    TEST_ASSERT_TRUE(hash_table_add_user(&Kim));
    TEST_ASSERT_TRUE(hash_table_add_user(&Erik));
    TEST_ASSERT_TRUE(hash_table_add_user(&Emil));
    TEST_ASSERT_TRUE(hash_table_add_user(&Johan));
    TEST_ASSERT_TRUE(hash_table_add_user(&Gustaf));
    TEST_ASSERT_TRUE(hash_table_add_user(&Jens));

    TEST_ASSERT_FALSE(hash_table_add_user(&Overkill));

    hash_table_print();
}

int main(void)
{

    UNITY_BEGIN();

    RUN_TEST(test_hash_delete_function);

    RUN_TEST(test_same_name_error);

    RUN_TEST(test_max_amount);

    return UNITY_END();
}