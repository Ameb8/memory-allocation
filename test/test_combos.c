#ifdef TEST

#include <stdio.h>
#include "../include/combos.h"
#include "test_util.h"
#include "test_combos.h"
#include "../include/big_int.h"

/*
    int blocks[7][2] = {
        {1, 4},
        {2, 1},
        {3, 4},
        {4, 2},
        {5, 2},
        {6, 1},
        {7, 3}
    };
*/

void print_ar(int* arr, char* name) {
    printf("%s: ", name);
    for(int i = 0; i < num_sizes; i++) {
        printf("%d, ", arr[i]);
    }

    printf("\n");
}


void test_init() {
    #ifdef DEBUG 
    print_ar(block_sizes, "Block Sizes");
    print_ar(block_amounts, "Block Amounts");
    #endif

    int exp_sizes[] = {7, 6, 5, 4, 3, 2, 1};
    int exp_amounts[] = {3, 1, 2, 2, 4, 1, 4};
    int exp_num_sizes = 7;

    ASSERT_INT_EQ(num_sizes, exp_num_sizes);

    for(int i = 0; i < 7; i++) {
        ASSERT_INT_EQ(block_sizes[i], exp_sizes[i]);
        ASSERT_INT_EQ(block_amounts[i], exp_amounts[i]);
    }
}

void test_get_num_combos_large() {
    int blck_amounts[] = {
        10000, 2000, 3000, 400, 150000
    };
    int sizes = 5;

    int test_cases[3][5] = {
        {20, 620, 12, 3, 9},
        {10, 5, 35, 400, 20},
        {10, 0, 0, 1, 50}
    };

    char* exp_results[] = {
        "1.9229e190", "3.9425e214", "2.2818e230"
    };

    for(int i = 0; i < 3; i++) {
        ASSERT_STR_EQ(bigint_to_sci(get_num_combos(test_cases[i], blck_amounts, sizes)), exp_results[i]);
    }
}


void test_get_num_combos() {
    int test_cases[3][7] = {
        {1, 1, 1, 1, 1, 1, 1},
        {3, 0, 0, 2, 4, 0, 0},
        {2, 0, 1, 0, 2, 0, 3}
    };

    char* exp_results[] = {"192", "1", "144"};

    for(int i = 0; i < 3; i++)
        ASSERT_STR_EQ(bigint_to_string(get_num_combos(test_cases[i], block_amounts, num_sizes)), exp_results[i]);
    
    test_get_num_combos_large();
}

void test_combos() {
    test_init();
    end_sub_test("INIT");
    test_get_num_combos();
    end_sub_test("NUM COMBOS");
}

#endif