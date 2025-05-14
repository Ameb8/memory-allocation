#ifndef COMBOS_H
#define COMBOS_H

typedef struct {
    int* program_blocks;
    int* block_sizes;
    int num_sizes;
    int num_combos;
} Combo;

Combo* combo_create(int* program_blocks, int* block);
void print_comb(Combo* combo);

#endif