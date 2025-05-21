#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "../include/combos.h"
#include "../include/big_int.h"

int* block_sizes = NULL; // Holds size of all available blocks
int* block_amounts = NULL; // Holds amount of all available blocks
int num_sizes; // Holds number of different block sizes available

// Initialize global variables for available block sizes and amounts
void init_blocks(List* blocks) {
    #ifdef DBG
    printf("init blocks called (list size: %d)\n", list_size(blocks));
    #endif

    num_sizes = list_size(blocks); // Set number of block sizes

    // Allocate memory for available blocks
    block_sizes = malloc(num_sizes * sizeof(int));
    block_amounts = malloc(num_sizes * sizeof(int));

    // Create list iterator
    ListIt* list_it = list_it_create(blocks);
    int i = 0;

    // Add block sizes and amounts to global vars
    while(list_it_has_next(list_it)) {
        int* vals = list_it_next(list_it);
        block_sizes[i] = vals[0];
        block_amounts[i++] = vals[1];
    }
}

// Each block stores a list of combinations (arrays of ints), their sizes, and how many
typedef struct {
    int **combos;     // combo list
    int *combo_sizes; // number of items in each combo
    int count;        // number of combos
} BlockCombos;

BlockCombos *all_blocks;


// Generate combinations of k items from 1 to n
void generate_combinations(int n, int k, int start, int depth, int *combo, int block_index) {
    if (depth == k) {
        BlockCombos *block = &all_blocks[block_index];
        block->combos = realloc(block->combos, sizeof(int *) * (block->count + 1));
        block->combo_sizes = realloc(block->combo_sizes, sizeof(int) * (block->count + 1));
        block->combos[block->count] = malloc(sizeof(int) * k);
        for (int i = 0; i < k; ++i)
            block->combos[block->count][i] = combo[i];
        block->combo_sizes[block->count] = k;
        block->count++;
        return;
    }

    for (int i = start; i <= n; ++i) {
        combo[depth] = i;
        generate_combinations(n, k, i + 1, depth + 1, combo, block_index);
    }
}


// Recursive function to print all combinations (Cartesian product of block combos)
void print_all(int depth, int *indices) {
    if (depth == num_sizes) {
        for (int i = 0; i < num_sizes; ++i) {
            int idx = indices[i];
            for (int j = 0; j < all_blocks[i].combo_sizes[idx]; ++j) {
                printf("%d(%d) ", block_sizes[i], all_blocks[i].combos[idx][j]);
            }
        }
        printf("\n");
        return;
    }

    for (int i = 0; i < all_blocks[depth].count; ++i) {
        indices[depth] = i;
        print_all(depth + 1, indices);
    }
}


void generate_all_combinations(int* program_blocks) {
    all_blocks = malloc(sizeof(BlockCombos) * num_sizes);

    for (int i = 0; i < num_sizes; ++i) {
        all_blocks[i].combos = NULL;
        all_blocks[i].combo_sizes = NULL;
        all_blocks[i].count = 0;

        int k = program_blocks[i];
        int n = block_amounts[i];

        if (k == 0) {
            // Represent "no selection" as an empty combo
            all_blocks[i].combos = malloc(sizeof(int *));
            all_blocks[i].combos[0] = NULL;
            all_blocks[i].combo_sizes = malloc(sizeof(int));
            all_blocks[i].combo_sizes[0] = 0;
            all_blocks[i].count = 1;
        } else {
            int *combo = malloc(sizeof(int) * k);
            generate_combinations(n, k, 1, 0, combo, i);
            free(combo);
        }
    }

    // Recursively print all Cartesian combinations
    int *indices = malloc(sizeof(int) * num_sizes);
    print_all(0, indices);
    free(indices);
}


// Display blocks in combo to user
void combo_print(int* program_blocks) {
    // Get possible number of combinations with given block allocation
    BigInt* num_possible = get_num_combos(program_blocks, block_amounts, num_sizes);

    printf("\n\n\033[1m"); //  Add new lines and start bold formatting
    bigint_print(num_possible); // Print number of combinations possible
    printf(" Possible Combinations containing:\n");

    bool first = true;

    // Iterate through block sizes in combo
    for(int i = 0; i < num_sizes; i++) {
        if(program_blocks[i] > 0) { // Print blocks used in  allocation
            if(!first) // Dont put comma in front of first item
                printf(", ");

            first = false; // Set first to false

            // Print number of each block type used
            printf("x%d %d-Byte Block", program_blocks[i], block_sizes[i]);
            
            if(program_blocks[i] > 1)
                printf("s"); // Add s if more than one used
        }
    }

    printf("\033[0m\n\n"); // Remove bold formatting and add newlines

    free(num_possible); // Free BigInt
    generate_all_combinations(program_blocks); // Print individual combinations
}
