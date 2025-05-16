#ifndef TREE_H
#define TREE_H
#include <stdbool.h>
#include "../include/combos.h"

typedef struct Tree Tree;
typedef struct TreeIt TreeIt;

Tree* tree_create();
void tree_insert(Tree* tree, int* program_blocks);
void tree_print(Tree* tree);
TreeIt* tree_it_create(Tree* tree);
bool tree_it_has_next(TreeIt* tree_it);
int* tree_it_next(TreeIt* tree_it);

#if defined(TEST) || defined(DEBUG)
int tree_height(Tree* tree);
void tree_print_level_order(Tree* tree);
int get_root(Tree* tree);

typedef struct TreeNode TreeNode;


#endif
#endif