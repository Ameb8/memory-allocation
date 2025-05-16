#ifndef TREE_H
#define TREE_H
#include <stdbool.h>
#include "../include/combos.h"

#ifndef TEST
typedef struct Tree Tree;
typedef struct TreeIt TreeIt;
#endif

#ifdef TEST
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

int tree_height(Tree* tree);
int get_root(Tree* tree);
#endif

Tree* tree_create();
void tree_insert(Tree* tree, int* program_blocks);
void tree_print(Tree* tree);
TreeIt* tree_it_create(Tree* tree);
bool tree_it_has_next(TreeIt* tree_it);
int* tree_it_next(TreeIt* tree_it);

#endif