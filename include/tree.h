#ifndef TREE_H
#define TREE_H
#include <stdbool.h>
#include "../include/combos.h"

typedef struct TreeNode TreeNode;
typedef struct Tree Tree;
typedef struct TreeIt TreeIt;


Tree* tree_create();
void tree_insert(Tree* tree, Combo* c);
TreeIt* tree_it_create(Tree* tree);
bool tree_it_has_next(TreeIt* tree_it);
Combo* tree_it_next(TreeIt* tree_it);

#endif