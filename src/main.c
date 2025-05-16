#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <errno.h>
#include <ctype.h>
#include <string.h>
#include "../include/get_combinations.h"
#include "../include/tree.h"
#include"../include/list.h"
#include "../test/test.h"

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

int get_user_int(char* prompt) {
    char input[100]; // Buffer to hold user input
    int valid_input = INT_MIN;
    
    while(valid_input == INT_MIN) { // Loop until a valid positive int is entered
        printf("%s", prompt);
        fgets(input, sizeof(input), stdin); // Read user input
        
        // Remove any trailing newline character
        input[strcspn(input, "\n")] = '\0';

        if(!strcmp(input, "") || !strcmp(input, "exit"))
            return INT_MIN;
        
        valid_input = parse_pos_int(input); // Parse the input
        
        if (valid_input == INT_MIN) {
            printf("Invalid Input: Please enter a positive integer\n");
        }
    }

    return valid_input;
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
    int size = get_user_int("Please enter the size of a free memory block: ");
    
    if(size == INT_MIN)
        return NULL;

    char prompt[100];
    snprintf(prompt, sizeof(prompt), "Please enter the number of %d size blocks available: ", size);

    int amount = get_user_int(prompt);

    if(amount == INT_MIN)
        return NULL;

    int* vals = malloc(2 * sizeof(int));
    vals[0] = size;
    vals[1] = amount;

    return vals;
}

void get_available_blocks() {
    List* blocks = list_create();
    int* block = NULL;
    
    do {
        block = get_block();

        if(block)
            list_increment(blocks, block);
    } while(block != NULL);

    init_blocks(blocks);
}

void run(int program_size) {
    get_available_blocks();
    Tree* combos = get_combinations(program_size);
    tree_print(combos);
}


int main(int argc, char* argv[]) {
    if(argc != 2)
        print_help();

    int program_size = parse_pos_int(argv[1]);
    
    if(program_size == INT_MIN)
        print_help();
    
    run(program_size);
}