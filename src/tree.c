#include <stdio.h>
#include <stdlib.h>
#include "../include/list.h"
#include "../include/combos.h"
#include "../include/tree.h"

typedef struct {
    int num_blocks;
    List* combos;
    TreeNode* left;
    TreeNode* right;

} TreeNode;


typedef struct {
    TreeNode* root;
    int size;
    int num_sizes;
    int height;
} Tree;

typedef struct {
    Tree* tree;
    Combo* current;
    ListIt* list;
    TreeNode** stack;
    int stack_size;
} TreeIt;

Tree* tree_create() {
    return calloc(1, sizeof(Tree));
}

TreeNode* node_create(Combo* c, int num_blocks) {
    TreeNode* node = malloc(sizeof(TreeNode));
    node->combos = list_create();
    list_add(node->combos, c);
    node->num_blocks = num_blocks;
    node->left = NULL;
    node->right = NULL;


    return node;
}

int get_num_blocks(Combo* c) {
    int num_blocks;
    for(int i = 0; i < c->num_sizes; i++)
        num_blocks += c->num_sizes;
    
    return num_blocks;
}

void node_insert(TreeNode* node, int num_blocks, Combo* c, int height, int* max_height) {
    if(height > *max_height) // Update tree's height
        (*max_height)++;

    if(num_blocks < node->num_blocks) { // Search left subtree
        if(!node->left)
            node->left = node_create(c, num_blocks);
        else
            node_insert(node->left, num_blocks, c, height + 1, max_height);
    } else if(num_blocks > node->num_blocks) { // Search right subtree
        if(!node->right)
            node->right = node_create(c, num_blocks);
        else
            node_insert(node->right, num_blocks, c, height + 1, max_height);
    } else { // Node found
        list_add(node->combos, c);
    }
}

void tree_insert(Tree* tree, Combo* c) {
    int num_blocks = get_num_blocks(c);

    if(tree->root == NULL)
        tree->root = node_create(c, num_blocks);

    node_insert(tree->root, num_blocks, c, 1, &tree->height);
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

/*
    Tree* tree;
    TreeNode* current;
    ListIt* list;
    Combo* stack;
    int stack_size;
*/


TreeIt* tree_it_create(Tree* tree) {
    if(!tree) return NULL;
    if(!tree->root) return NULL;

    TreeIt* tree_it = malloc(sizeof(TreeIt));
    tree_it->tree = tree;

    TreeNode* stack[tree->height];
    tree_it->stack_size = 0;
    push_left(tree_it, tree->root);

    TreeNode* node = tree_it->stack[tree_it->stack_size--];
    tree_it->list = list_it_create(node->combos);
    tree_it->current = list_it_next(tree_it->list);
}

bool tree_it_has_next(TreeIt* tree_it) {
    if(!tree_it || !tree_it->current)
        return false;

    return true;
}

Combo* tree_it_next(TreeIt* tree_it) {
    if(!tree_it || tree_it->current) return NULL;
    Combo* ret = tree_it->current;

    if(list_it_has_next(tree_it->list)) {
        tree_it->current = list_it_next(tree_it->list);

        return ret;
    }

    TreeNode* next_node = pop(tree_it);
    push_left(tree_it, next_node->right);
    tree_it->list = list_it_create(next_node->combos);
    tree_it->current = list_it_next(tree_it->list);

    return ret;
}
