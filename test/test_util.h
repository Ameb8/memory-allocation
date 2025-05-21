#ifdef TEST
#ifndef TEST_UTIL_H
#define TEST_UTIL_H

#include <stdio.h>
#include <string.h>

void test_results();
void end_sub_test(char* test_name);
void pass();
void fail();
void print_array(int* arr, int size, char* name);
 
#define ASSERT_INT_EQ(actual, expected) do { \
    int _exp = (expected); \
    int _act = (actual); \
    if((actual) != (expected)) { \
        fail(); \
        printf("\nFAILED in %s: %s != %s at %s:%d (actual=%d, expected=%d)\n", \
             __func__, #actual, #expected, __FILE__, __LINE__, _act, _exp); \
    } else { \
        pass(); \
    } \
} while(0)

#define ASSERT_STR_EQ(actual, expected) do { \
    pass(); \
    if((actual) == NULL || (expected) == NULL || strcmp((actual), (expected)) != 0) { \
        fail(); \
        printf("FAILED in %s: %s != %s (%s != %s) at %s:%d\n", \
            __func__, #actual, #expected, \
            (actual) ? (actual) : "NULL", \
            (expected) ? (expected) : "NULL", \
            __FILE__, __LINE__); \
    } \
} while(0)

#endif
#endif