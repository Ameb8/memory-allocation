#ifdef TEST
#ifndef TEST_UTIL_H
#define TEST_UTIL_H

#include <stdio.h>

void test_results();
void end_sub_test(char* test_name);
void pass();
void fail();
 
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

#endif
#endif