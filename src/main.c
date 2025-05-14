#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>
#include <ctype.h>
#include "../include/get_combinations.h"
#include "../include/tree.h"
#include"../include/list.h"

void run(int block_size[], int block_amount[], int program_size) {
    Tree* combos = get_combinations(program_size);
    TreeIt* tree_it = tree_it_create(combos);

    while(tree_it_has_next(tree_it)) {

    }
}

void print_help() {
    printf("Exactly 1 command line argument must be passed to the program\n");
    printf("Please run again, passing the size of the program in bytes as argument\n");
    printf("Argument must be a positive integer\n");
    exit(0);
}

int parse_pos_int(char* str) {
    if (str == NULL || *str == '\0') return INT_MIN;

    char* endptr; // Tracks where valid int chars stop
    errno = 0; // Detects errors when parsing

    long val = strtol(str, &endptr, 10);

    // Check for overflow/underflow
    if (errno == ERANGE || val > INT_MAX || val <= 0)
        return INT_MIN;

    // Check for non-digit characters after the number
    while (*endptr != '\0') {
        if (!isspace((unsigned char)*endptr)) // allow trailing spaces
            return INT_MIN;
        endptr++;
    }

    return (int)val;
}

int validate_args(int argc, char* argv[]) {
    if(argc != 1)
        print_help();

    int program_size = parse_pos_int(argv[0]);

    if(program_size == INT_MIN)
        print_help();

    return program_size;
}

int* get_block() {
    int size = 0;
    int amount = 0;

    do { // Collect block size
        printf("Please enter the size of the block in bytes (positive integer):\t");
        size = parse_pos_int("");
    } while(size < 1);

    do { // Collect amount
        printf("Please enter the amount of %d byte blocks available (positive integer):\t", size);
        amount = parse_pos_int("");
    } while(amount < 1);

    int* vals = malloc(2 * sizeof(int));
    vals[0] = size;
    vals[1] = amount;

    return vals;
}

void get_available_blocks() {
    List* blocks = list_create();
    int* block = NULL;

    do {
        int* block = get_block();
        list_add(blocks, block);
    } while(block != NULL);

    init_blocks(blocks);
}

int main(int argc, char* argv[]) {
    if(argc != 2)
        print_help();

    int program_size = parse_pos_int(argv[1]);
    
    if(program_size == INT_MIN)
        print_help();
    


    int block_size[] = {10, 7, 5, 4, 3, 1};
    int block_amount[] = {1, 1, 2, 1, 1, 10};
    //int program_size = 10;
    get_combinations(program_size);
}