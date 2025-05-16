#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../include/get_combinations.h"
#include "../include/combos.h"


void generate_combos(int program_size, int mem_used, int* program_blocks, int index, Tree* combos) {
    if(index >= num_sizes) // Index out of bounds
        return;

    // Add current block until run out or size limit reached/exceeded
    while(mem_used < program_size && block_amounts[index] > 0) {
        mem_used += block_sizes[index];
        block_amounts[index] -= 1;
        program_blocks[index] += 1;
    }

    if(mem_used == program_size) // Combo found
        tree_insert(combos, program_blocks);
    else if(mem_used < program_size) // Ran out of blocks
        generate_combos(program_size, mem_used, program_blocks, index + 1, combos);

    while(program_blocks[index] > 0) { // Decrement current block amount used and continue search
        mem_used -= block_sizes[index];
        block_amounts[index] += 1;
        program_blocks[index] -= 1;
        generate_combos(program_size, mem_used, program_blocks, index + 1, combos);
    }
}


// block_size and block_amounts must be sorted in descending order by block size
Tree* get_combinations(int program_size) {
    int* used_blocks = calloc(num_sizes, sizeof(int));
    Tree* combos = tree_create();
    generate_combos(program_size, 0, used_blocks, 0, combos);

    return combos;
}