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


// Provide message and exits program when input arguments are invalid
void print_help() {
    printf("Exactly 1 command line argument must be passed to the program\n");
    printf("Please run again, passing the size of the program in bytes as argument\n");
    printf("Argument must be a positive integer\n");
    exit(0);
}


// Converts string to positive integer, returns INT_MIN if invalid
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


// Prompt user to input integer and attempt to parse
int get_user_int(char* prompt) {
    char input[100]; // Buffer to hold user input
    int valid_input = INT_MIN;
    
    while(valid_input == INT_MIN) { // Loop until a valid positive int is entered
        printf("%s", prompt);
        fgets(input, sizeof(input), stdin); // Read user input
        
        // Remove any trailing newline character
        input[strcspn(input, "\n")] = '\0';

        if(!strcmp(input, "") || !strcmp(input, "exit"))
            return INT_MIN; // Abort input collection
        
        valid_input = parse_pos_int(input); // Parse the input
        
        if(valid_input == INT_MIN) // Re-prompt user
            printf("Invalid Input: Please enter a positive integer\n");
    }

    return valid_input;
}


// Validate input arguments are valid and convert to integer
int validate_args(int argc, char* argv[]) {
    if(argc != 1)
        print_help();

    int program_size = parse_pos_int(argv[0]);

    if(program_size == INT_MIN)
        print_help(); // Argument values invalid

    return program_size;
}


// Get a block size and amount from user
int* get_block() {
    // Get block size
    int size = get_user_int("Please enter the size (Bytes) of a free memory block: ");
    
    if(size == INT_MIN)
        return NULL; // Size invalid

    //Create prompt for collecting block amount
    char prompt[100];
    snprintf(prompt, sizeof(prompt), "Please enter the number of %d-Byte blocks available: ", size);

    int amount = get_user_int(prompt); // Get block amount from user

    if(amount == INT_MIN)
        return NULL; // Block amount invalid

    // Return size/amount as length-2 array
    int* vals = malloc(2 * sizeof(int));
    vals[0] = size;
    vals[1] = amount;

    #ifdef DBG
    printf("Size: %d, Amount: %d\n", vals[0], vals[1]);
    #endif

    return vals;
}


// Get blocks from user
void get_available_blocks() {
    List* blocks = list_create(); // Create list to hold user blocks
    int* block = NULL;

    do { // Collect memory blocks
        block = get_block(); // Get block from user

        #ifdef DBG
        printf("Block received\n");
        #endif

        if(block) // Add to list if valid
            list_increment(blocks, block);
    } while(block != NULL);

    init_blocks(blocks); // Initialize block sizes
}


// Run program
void run(int program_size) {
    get_available_blocks(); // Collect block sizes and amount

    #ifdef DBG
    printf("get_available_blocks() executed\n");
    #endif

    Tree* combos = get_combinations(program_size); // Get combinations

    #ifdef DBG
    printf("combos retrieved\n");
    #endif

    tree_print(combos); // Print combinations
}


int main(int argc, char* argv[]) {
    // Run if compiled with test flag
    #ifdef TEST
    run_tests();
    return 0;
    #endif

    if(argc != 2) // Check if correct number of arguments
        print_help();

    int program_size = parse_pos_int(argv[1]); // Parse program size
    
    if(program_size == INT_MIN)
        print_help(); // Program size invalid
    
    run(program_size); // Run program

    return 0;
}