#ifndef COMBOS_H
#define COMBOS_H

#include "list.h"

typedef struct {
    int* program_blocks;
} Combo;

extern int* block_sizes;
extern int* block_amounts;
extern int num_sizes;

Combo* combo_create(int* program_blocks, int* block);
void combo_print(int* program_blocks);
void init_blocks(List* blocks);

#endif