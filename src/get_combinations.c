#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "../include/get_combinations.h"
#include "../include/combos.h"

// Generates all possible combinations and modifies tree in place to hold them
void generate_combos(int program_size, int mem_used, int* program_blocks, int index, Tree* combos) {
    #ifdef DBG
    printf("generate_combos index: %d\n", index);
    #endif
    
    if(index >= num_sizes) // Index out of bounds
        return;

    // Add current block until run out or size limit reached/exceeded
    while(mem_used < program_size && block_amounts[index] > 0) {
        mem_used += block_sizes[index]; // Add bytes in block to used memory
        block_amounts[index] -= 1; // Decrement blocks available
        program_blocks[index] += 1; // Increment blocks used
    }

    if(mem_used == program_size) // Combo found
        tree_insert(combos, program_blocks); // Save combination
    else if(mem_used < program_size) // Ran out of blocks
        generate_combos(program_size, mem_used, program_blocks, index + 1, combos); // Continue search

    while(program_blocks[index] > 0) { // Decrement current block amount used and continue search
        mem_used -= block_sizes[index]; // Remove bytes in block from used memory
        block_amounts[index] += 1; // Increment blocks available
        program_blocks[index] -= 1; // Decrement blocks used
        generate_combos(program_size, mem_used, program_blocks, index + 1, combos); // Continue search
    }
}


// Generates all possible combinations and saves in tree
Tree* get_combinations(int program_size) {
    #ifdef DBG
    printf("get_combinations() reached\n");
    #endif

    int* used_blocks = calloc(num_sizes, sizeof(int)); // Allocate memory for allocated blocks
    Tree* combos = tree_create(); // Create tree to hold allocations

    #ifdef DEBUG
    printf("Tree created\n");
    #endif

    generate_combos(program_size, 0, used_blocks, 0, combos); // Generate combinations

    return combos;
}