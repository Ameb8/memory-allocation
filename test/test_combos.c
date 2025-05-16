#ifdef test

#include <stdio.h>
#include "../include/combos.h"
#include "test_util.h"

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

void test_combos() {
    test_init();
    end_sub_test("INIT");
}

#endif