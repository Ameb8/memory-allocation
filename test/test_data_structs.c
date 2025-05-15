#ifdef TEST

#include <stdlib.h>
#include "../include/list.h"
#include "../include/tree.h"
#include "test_util.h"
#include "test_data_structs.h"

void test_list() {
    List* list = list_create();

    ASSERT_INT_EQ(0, list_size(list)); // Test size

    // Populate list
    int it_1[] = {1, 1};
    int it_2[] = {2, 1};
    int it_3[] = {3, 1};

    list_add(list, it_1);
    list_add(list, it_2);
    list_add(list, it_3);

    ASSERT_INT_EQ(3, list_size(list)); // Test size

    int it_4[] = {1, 1};
    
    list_increment(list, it_4);

    ASSERT_INT_EQ(3, list_size(list)); // Test size

    ListIt* it = list_it_create(list);

    int* res = list_it_next(it);
    ASSERT_INT_EQ(3, res[0]);
    ASSERT_INT_EQ(1, res[1]);

    res = list_it_next(it);
    ASSERT_INT_EQ(2, res[0]);
    ASSERT_INT_EQ(1, res[1]);

    res = list_it_next(it);
    ASSERT_INT_EQ(1, res[0]);
    ASSERT_INT_EQ(2, res[1]);

    free(list);
    free(it);
}


void test_tree() {
    // program block values for tree
    int program_blocks[10][7] = {
        {1, 1, 1, 0, 0, 0, 0}, // 3 Blocks
        {1, 1, 1, 1, 1, 0, 0},// 5 blocks
        {1, 0, 0 ,0 ,0, 0, 0}, // 1 block
        {1, 1, 1, 1, 0 , 0, 0}, // 4 blocks
        {1, 1, 1, 0, 0, 0, 0}, // 3 blocks
        {1, 1, 1, 1, 0, 0, 0}, // 4 blocks
        {1, 0, 0, 0, 0, 0, 0}, // 1 block
        {1, 1, 1, 1, 0, 0, 0}, // 4 blocks
        {1, 1, 0, 0, 0, 0, 0}, // 2 blocks
        {1, 1, 1, 1, 1, 1, 1} // 7 blocks
    };

    /* TREE STRUCTURE:
              3
            /   \
           1     5
            \   / \
             2 4   7

        Inorder Traversal:
        1, 2, 3, 4, 5, 7

        List Order by Node:
        Node 1: 2, 6
        Node 2: 8
        Node 3: 4, 0
        Node 4: 7, 5, 3
        Node 5: 1,
        Node 7: 9

        Full order by program_block row index:
        2, 6, 8, 4, 0, 7, 5, 3, 1, 9
    */

    // Create and populate tree
    Tree* tree = tree_create();

    ASSERT_INT_EQ(0, tree_height(tree)); // Test initial height
    int tree_heights[] = {1, 2, 2, 3, 3, 3, 3, 3, 3, 3};

    for(int i = 0; i < 10; i++) {
        tree_insert(tree, program_blocks[i]);
        ASSERT_INT_EQ(tree_height(tree), tree_heights[i]);
    }
        
    TreeIt* tree_it = tree_it_create(tree);
    int exp_res_index[] = {2, 6, 8, 4, 0, 7, 5, 3, 1, 9};
    int index = 0;

    while(tree_it_has_next(tree_it)) {
        int* actual = tree_it_next(tree_it);

        for(int i = 0; i < 7; i++) {// Test values in program_blocks
            ASSERT_INT_EQ(actual[i], program_blocks[exp_res_index[index]][i]);
        }

        index++;
    }   
}


void test_data_structs() {
    test_list();
    end_sub_test("LIST");
    test_tree();
    end_sub_test("TREE");
}

#endif