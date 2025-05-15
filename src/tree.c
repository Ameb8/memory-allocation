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

    int num_blocks = get_num_blocks(blocks);


    if(tree->root == NULL) {
        tree->root = node_create(blocks, num_blocks);
        tree->height = 1;
        return;
    }

    node_insert(tree->root, num_blocks, blocks, 1, &tree->height);
}


TreeNode* pop(TreeIt* tree_it) {
    if(!tree_it || tree_it->stack_size < 0)
        return NULL;

    return tree_it->stack[tree_it->stack_size--];
}


void push_left(TreeIt* tree_it, TreeNode* node) {
    TreeNode* temp = node;

    while (temp) {
        tree_it->stack[tree_it->stack_size++] = temp;
        temp = temp->left;
    }
}


TreeIt* tree_it_create(Tree* tree) {
    if (!tree || !tree->root) return NULL;

    TreeIt* tree_it = malloc(sizeof(TreeIt));
    if (!tree_it) return NULL;

    tree_it->tree = tree;
    tree_it->stack = malloc(tree->height * sizeof(TreeNode*));
    if (!tree_it->stack) {
        free(tree_it);
        return NULL;
    }

    tree_it->stack_size = 0;

    // Push leftmost path from root onto the stack
    push_left(tree_it, tree->root);

    // If the tree is empty or push_left failed
    if (tree_it->stack_size == 0) {
        free(tree_it->stack);
        free(tree_it);
        return NULL;
    }

    // Pop the first node to start the iterator
    TreeNode* node = pop(tree_it);
    if (!node || !node->blocks) {
        free(tree_it->stack);
        free(tree_it);
        return NULL;
    }

    // Initialize list iterator
    tree_it->list = list_it_create(node->blocks);
    if (!tree_it->list) {
        free(tree_it->stack);
        free(tree_it);
        return NULL;
    }

    tree_it->current = list_it_next(tree_it->list);

    // Push right child of the popped node
    push_left(tree_it, node->right);

    return tree_it;
}


bool tree_it_has_next(TreeIt* tree_it) {
    if(!tree_it || !tree_it->current)
        return false;

    return true;
}


int* tree_it_next(TreeIt* tree_it) {
    if (!tree_it || !tree_it->current) return NULL;

    int* ret = tree_it->current;

    if (list_it_has_next(tree_it->list)) {
        tree_it->current = list_it_next(tree_it->list);
        return ret;
    }

    // Move to next node in the stack
    while (tree_it->stack_size > 0) {
        TreeNode* next_node = pop(tree_it);
        push_left(tree_it, next_node->right);

        if (next_node->blocks) {
            //list_it_destroy(tree_it->list);  // Free previous list
            tree_it->list = list_it_create(next_node->blocks);
            tree_it->current = list_it_next(tree_it->list);
            if (tree_it->current)
                return ret;
        }
    }

    tree_it->current = NULL;
    return ret;
}


#ifdef TEST
int tree_height(Tree* tree) {
    return tree->height;
}
#endif
