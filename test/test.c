#ifdef TEST

#include "test_util.h"
#include "test_data_structs.h"
#include "../include/combos.h"
#include "../include/list.h"
#include "test_combo.h"
#include "test.h"

void initialize_test() {
    List* blocks_list = list_create();

    // Initialize block types
    int blocks[7][2] = {
        {1, 4},
        {2, 1},
        {3, 4},
        {4, 2},
        {5, 2},
        {6, 1},
        {7, 3}
    };

    // Convert blocks to list
    for(int i = 0; i < 7; i++)
        list_add(blocks_list, blocks[i]);

    // Initialize global state in combos.c
    init_blocks(blocks_list);
}

void run_tests() {
    initialize_test();

    test_data_structs();
    test_combos();
    test_results();
}

#endif