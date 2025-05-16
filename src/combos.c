#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "../include/combos.h"

int* block_sizes = NULL;
int* block_amounts = NULL;
int num_sizes;

void init_blocks(List* blocks) {
    num_sizes = list_size(blocks);
    block_sizes = malloc(num_sizes * sizeof(int));
    block_amounts = malloc(num_sizes * sizeof(int));

    ListIt* list_it = list_it_create(blocks);
    int i = 0;

    while(list_it_has_next(list_it)) {
        int* vals = list_it_next(list_it);
        block_sizes[i] = vals[0];
        block_amounts[i++] = vals[1];
    }
}

int factorial(int n) {
    int result = 1;

    for(int i = 2; i <= n; i++)
        result *= i;

    return result;
}

int get_num_combos(int* program_blocks) {
    int num_combos = 0;
    
    for(int i = 0; i < num_sizes;i++) {
        if(program_blocks[i] > 0) {
            int n = block_amounts[i];
            int k = program_blocks[i];

            if(k > n)
                return 0;
            if(k == n)
                continue;
            
            num_combos += (factorial(n)) / (factorial(k) * factorial(n - k));
        }
    }

    return num_combos;
}


void combo_print(int* program_blocks) {
    int num_possible = get_num_combos(program_blocks);
    int used = 0;
    printf("\n\n%d possible combinations of:\n", num_possible);

    for(int i = 0; i < num_sizes; i++) {
        if(program_blocks[i] > 0) {
            printf("%d %d byte blocks", program_blocks[i], block_sizes[i]);
            used += program_blocks[i];

            if(i < num_sizes - 1)
                printf(", ");
        }
    }

    printf("\tTotal Blocks Used: %d\n", used);
}