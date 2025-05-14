#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/list.h"
#include "../include/combos.h"
#include "../include/tree.h"

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

Tree* tree_create() {
    return calloc(1, sizeof(Tree));
}

TreeNode* node_create(int* blocks, int num_blocks) {
    int* blocks_copy = malloc(num_sizes * sizeof(int));
    memcpy(blocks_copy, blocks, num_sizes * sizeof(int));

    TreeNode* node = malloc(sizeof(TreeNode));
    node->blocks = list_create();
    list_add(node->blocks, blocks_copy);
    node->num_blocks = num_blocks;
    node->left = NULL;
    node->right = NULL;

    return node;
}

int get_num_blocks(int* blocks) {
    int num_blocks;
    for(int i = 0; i < num_sizes; i++)
        num_blocks += blocks[i];
    
    return num_blocks;
}

void node_insert(TreeNode* node, int num_blocks, int* blocks, int height, int* max_height) {
    if(height > *max_height) // Update tree's height
        (*max_height)++;

    if(num_blocks < node->num_blocks) { // Search left subtree
        if(!node->left)
            node->left = node_create(blocks, num_blocks);
        else
            node_insert(node->left, num_blocks, blocks, height + 1, max_height);
    } else if(num_blocks > node->num_blocks) { // Search right subtree
        if(!node->right)
            node->right = node_create(blocks, num_blocks);
        else
            node_insert(node->right, num_blocks, blocks, height + 1, max_height);
    } else { // Node found
        list_add(node->blocks, blocks);
    }
}

void tree_insert(Tree* tree, int* blocks) {
    if(!tree || !blocks)
        return;

    int num_blocks = get_num_blocks(blocks);

    if(tree->root == NULL)
        tree->root = node_create(blocks, num_blocks);

    node_insert(tree->root, num_blocks,blocks, 1, &tree->height);
}

TreeNode* pop(TreeIt* tree_it) {
    if(!tree_it || tree_it->stack_size < 0)
        return NULL;

    return tree_it->stack[tree_it->stack_size--];
}

void push_left(TreeIt* tree_it, TreeNode* node) {
    TreeNode* temp = node->left;

    while(temp)
        tree_it->stack[tree_it->stack_size++] = temp;
}

TreeIt* tree_it_create(Tree* tree) {
    if(!tree) return NULL;
    if(!tree->root) return NULL;

    TreeIt* tree_it = malloc(sizeof(TreeIt));
    tree_it->tree = tree;

    TreeNode* stack[tree->height];
    tree_it->stack_size = 0;
    push_left(tree_it, tree->root);

    TreeNode* node = tree_it->stack[tree_it->stack_size--];
    tree_it->list = list_it_create(node->blocks);
    tree_it->current = list_it_next(tree_it->list);
}

bool tree_it_has_next(TreeIt* tree_it) {
    if(!tree_it || !tree_it->current)
        return false;

    return true;
}

int* tree_it_next(TreeIt* tree_it) {
    if(!tree_it || tree_it->current) 
        return NULL;
    
    int* ret = tree_it->current;

    if(list_it_has_next(tree_it->list)) {
        tree_it->current = list_it_next(tree_it->list);

        return ret;
    }

    TreeNode* next_node = pop(tree_it);
    push_left(tree_it, next_node->right);
    tree_it->list = list_it_create(next_node->blocks);
    tree_it->current = list_it_next(tree_it->list);

    return ret;
}
