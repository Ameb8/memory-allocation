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
void print_combo(Combo* combo);
void init_blocks(List* blocks);

#endif