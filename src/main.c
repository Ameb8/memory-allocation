#include <stdio.h>
#include "../include/get_combinations.h"
#include "../include/tree.h"

void run(int block_size[], int block_amount[], int program_size) {
    Tree* combos = get_combos(block_size, block_amount, 6, program_size);
    TreeIt* tree_it = tree_it_create(combos);

    while(tree_it_has_next(tree_it)) {
        
    }
}

int main() {
    int block_size[] = {10, 7, 5, 4, 3, 1};
    int block_amount[] = {1, 1, 2, 1, 1, 10};
    int program_size = 10;
    get_combinations(block_size, block_amount, 6, program_size);
}