#include <stdio.h>
#include "../include/get_combinations.h"

int main() {
    int block_size[] = {10, 7, 5, 4, 3, 1};
    int block_amount[] = {1, 1, 2, 1, 1, 10};
    int program_size = 10;
    get_combinations(block_size, block_amount, 6, program_size);
}