#ifdef TEST

#include "test_util.h"
#include "../include/combos.h"

int num_tests = 0;
int num_failed = 0;
int total_tests = 0;
int total_failed = 0;

void test_results() {
    printf("\nFINAL RESULTS: %d/%d tests passed\n", total_tests - total_failed, total_tests);
}

void end_sub_test(char* test_name) {
    printf("\n%s TEST RESULTS: %d/%d tests passed\n", test_name, num_tests - num_failed, num_tests);
    num_tests = 0;
    num_failed = 0;
}

void pass() {
    num_tests++;
    total_tests++;
}

void fail() {
    num_failed++;
    total_failed++;
    pass();
}

void print_array(int* arr, int size, char* name) {
    printf("%s: ", name);
    for(int i = 0; i < size; i++) {
        printf("%d, ", arr[i]);
    }
    printf("\n");
}

#endif