#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/list.h"
#include "../include/combos.h"
#include "../include/tree.h"

#ifndef TEST
typedef struct TreeNode TreeNode;

typedef struct TreeNode {
    int num_blocks;
    List* blocks;
    TreeNode* left;
    TreeNode* right;

} TreeNode;

typedef struct Tree {
    TreeNode* root;
    int size;
    int num_sizes;
    int height;
} Tree;

typedef struct TreeIt {
    Tree* tree;
    int* current;
    ListIt* list;
    TreeNode** stack;
    int stack_size;
} TreeIt;

#endif

Tree* tree_create() {
    return calloc(1, sizeof(Tree));
}


TreeNode* node_create(int* blocks, int num_blocks) {
    TreeNode* node = malloc(sizeof(TreeNode));
    node->blocks = list_create();
    list_add(node->blocks, blocks);
    node->num_blocks = num_blocks;
    node->left = NULL;
    node->right = NULL;

    return node;
}


int get_num_blocks(int* blocks) {
    int num_blocks = 0;
    for(int i = 0; i < num_sizes; i++)
        num_blocks += blocks[i];
    
    return num_blocks;
}


void node_insert(TreeNode* node, int num_blocks, int* blocks, int height, int* max_height) {
    if(num_blocks < node->num_blocks) { // Search left subtree
        if(!node->left) { // Insert location found
            node->left = node_create(blocks, num_blocks);
            if(height == *max_height) // Update tree's height
                (*max_height)++;
        } else // Search next level
            node_insert(node->left, num_blocks, blocks, height + 1, max_height);
    } else if(num_blocks > node->num_blocks) { // Search right subtree
        if(!node->right) { // Insert location found
            node->right = node_create(blocks, num_blocks);
            if(height == *max_height) // Update tree's height
                (*max_height)++;
        } else // Search next level
            node_insert(node->right, num_blocks, blocks, height + 1, max_height);
    } else { // Node found
        list_add(node->blocks, blocks);
    }
}


void tree_insert(Tree* tree, int* blocks) {
    if(!tree || !blocks)
        return;

    int* blocks_copy = malloc(num_sizes * sizeof(int));
    memcpy(blocks_copy, blocks, num_sizes * sizeof(int));

    int num_blocks = get_num_blocks(blocks_copy);


    if(tree->root == NULL) {
        tree->root = node_create(blocks_copy, num_blocks);
        tree->height = 1;
        return;
    }

    node_insert(tree->root, num_blocks, blocks_copy, 1, &tree->height);
}


// Recursively print all elements in tree
void print_node(TreeNode* node) {
    if(node->left) // Print combos with fewer blocks
        print_node(node->left);

    // Print all combos with current number of blocks
    ListIt* list_it = list_it_create(node->blocks);
    printf("\n\n\033[1mAllocations With %d Blocks:\033[0m", node->num_blocks);

    while(list_it_has_next(list_it)) {
        combo_print(list_it_next(list_it));
    }
    
    if(node->right) // Print combos with more blocks
        print_node(node->right);
}


// Print all combos in tree
void tree_print(Tree* tree) {
    print_node(tree->root);
    printf("\n\n");
}


#ifdef TEST

int get_root(Tree* tree) {
    return tree->root->num_blocks;
}

int tree_height(Tree* tree) {
    return tree->height;
}
#endif