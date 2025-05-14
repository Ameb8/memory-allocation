#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../include/get_combinations.h"
#include "../include/tree.h"

void print_combo(int* program_blocks, int* block_size, int num_sizes) {
    printf("Memory usage:\t");
    int used = 0;
    
    for(int i = 0; i < num_sizes; i++) {
        if(program_blocks[i] > 0) {
            printf("%d %d byte blocks", program_blocks[i], block_size[i]);
            used += program_blocks[i];

            if(i < num_sizes - 1)
                printf(", ");
        }
    }

    printf("\tTotal Blocks Used: %d\n", used);
}

void generate_combos(int* block_size, int* block_amounts, int num_sizes, int program_size, int mem_used, int* program_blocks, int index) {
    if(index >= num_sizes)
        return;

    // Add current block until run out or size limit reached/exceeded
    while(mem_used < program_size && block_amounts[index] > 0) {
        mem_used += block_size[index];
        block_amounts[index] -= 1;
        program_blocks[index] += 1;
    }

    if(mem_used == program_size) { // Combo found
        print_combo(program_blocks, block_size, num_sizes);
    } else if(mem_used < program_size) { // Ran out of blocks
        generate_combos(block_size, block_amounts, num_sizes, program_size, mem_used, program_blocks, index + 1);
    }

    while(program_blocks[index] > 0) { // Decrement current block amount used and continue search
        mem_used -= block_size[index];
        block_amounts[index] += 1;
        program_blocks[index] -= 1;
        generate_combos(block_size, block_amounts, num_sizes, program_size, mem_used, program_blocks, index + 1);
    }
}

// block_size and block_amounts must be sorted in descending order by block size
Tree* get_combinations(int* block_size, int* block_amounts, int num_sizes, int program_size) {
    int* used_blocks = calloc(num_sizes, sizeof(int));
    Tree* combos = tree_create();

    generate_combos(block_size, block_amounts, num_sizes, program_size, 0, used_blocks, 0);

    return combos;
}