#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../include/big_int.h"


#define MAX_DIGITS 400      // Max number of digits
#define PRINT_DIGITS 5      // Number of digits to print after decimal


// Structure to hold numbers up to 10^400 - 1
typedef struct BigInt {
    int digits[MAX_DIGITS]; // Array to store digits
    int size; // Tracks number of digits used
} BigInt;


// Instantiates BigInt
BigInt* bigint_create(int value) {
    BigInt* a = (BigInt*)malloc(sizeof(BigInt));
    if(!a) // Handle allocation failure
        return NULL;

    // Initialize value to zero
    memset(a->digits, 0, sizeof(a->digits));
    a->size = 0;

    while(value > 0) { // extract digits from input integer
        a->digits[a->size++] = value % 10;
        value /= 10;
    }

    if(a->size == 0) // Ensure size is 1 for value 0
        a->size = 1;

    return a;
}


// Print BigInt
void bigint_print(const BigInt* a) {
    if(a->size < 11) { // Print normally if less then 11 digits
        for(int i = a->size - 1; i >= 0; i--)
            printf("%d", a->digits[i]);
    } else { // Print in scientific notation
        printf("%d", a->digits[a->size - 1]);  // Most significant digit

        // Digits after decimal
        if (PRINT_DIGITS > 1) {
            printf(".");
            int printed = 1;
            for (int i = a->size - 2; i >= 0 && printed < PRINT_DIGITS; i--) {
                printf("%d", a->digits[i]);
                printed++;
            }
        }

        // Print exponent
        printf("e+%d", a->size - 1);
    }
}


// Multiply big int by integer
void bigint_mul_int(BigInt *a, int b) {
    int carry = 0; // Stores overflow from digit multiplication

    // Multiply each BigInt digit by b
    for(int i = 0; i < a->size; i++) {
        int prod = a->digits[i] * b + carry;// Multiply and add previous carry
        a->digits[i] = prod % 10; // Store least significant digit
        carry = prod / 10; // Update carry
    }

    while (carry) { // Add remaining carry as new digits
        a->digits[a->size++] = carry % 10;
        carry /= 10;
    }
}


// Divides a BigInt by integer b
void bigint_div_int(BigInt *a, int b) {
    int rem = 0; // Stores remainder

    // Iterate through BigInt digits
    for(int i = a->size - 1; i >= 0; i--) {
        int current = rem * 10 + a->digits[i]; // Add remainder to current number
        a->digits[i] = current / b; // store result of division at current position
        rem = current % b; // update remainder to carry over
    }

    // Adjust size to remove leading zeros
    while(a->size > 1 && a->digits[a->size - 1] == 0) {
        a->size--;
    }
}

// Compute binomial coefficient of n over k
BigInt* compute_binomial(int n, int k) {
    BigInt* res = bigint_create(1); // initialize result with 1

    // Use multiplicative formula to comput C(n, k)
    for(int i = 1; i <= k; i++) {
        bigint_mul_int(res, n - i + 1);
        bigint_div_int(res, i);
    }

    return res;
}


// Get number of combos with given block amount
BigInt* get_num_combos(int* restrict program_blocks, int* restrict block_amounts, int num_sizes) {
    BigInt* result = bigint_create(1);  // initialize result as 1

    // Loop through each selected block type
    for (int i = 0; i < num_sizes; i++) {
        // Get binomial inputs
        int n = block_amounts[i]; // Total blocks of this type
        int k = program_blocks[i]; // Blocks chosen from this type

        if (k > n)
            return bigint_create(0);  // Invalid case

        if (k == 0 || k == n)
            continue; // skip iteration, possibilities will be 1

        // Compute C(n, k)
        BigInt* binom = compute_binomial(n, k);

        // Multiply current result by binom
        BigInt* new_result = bigint_create(0);  // temp result
        new_result->size = 1;
        new_result->digits[0] = 0;

        // Multiply binom with result using long multiplication
        for (int j = 0; j < binom->size; j++) {
            BigInt temp = *result;
            bigint_mul_int(&temp, binom->digits[j]);
            for (int k = 0; k < j; k++) {
                bigint_mul_int(&temp, 10); // Shift left
            }

            // Add temp to new_result
            for (int d = 0, carry = 0; d < MAX_DIGITS; d++) {
                int sum = new_result->digits[d] + (d < temp.size ? temp.digits[d] : 0) + carry;
                new_result->digits[d] = sum % 10;
                carry = sum / 10;
            }

            // Adjust size of new result
            new_result->size = MAX_DIGITS;
            while (new_result->size > 1 && new_result->digits[new_result->size - 1] == 0)
                new_result->size--;
        }

        free(result); // Free old result
        result = new_result; // Update result
        free(binom); // Free temporary binomial result
    }

    return result;
}


#ifdef TEST

char* bigint_to_string(const BigInt* a) {
    // Allocate enough space for digits + null terminator
    char* str = (char*)malloc(a->size + 1);
    if (!str) return NULL;

    for (int i = 0; i < a->size; i++) {
        str[a->size - 1 - i] = a->digits[i] + '0';  // convert digit to char
    }

    str[a->size] = '\0';  // null-terminate
    return str;
}


char* bigint_to_sci(const BigInt* a) {
    if (a->size == 0) {
        // Handle zero explicitly
        char* zero_str = (char*)malloc(6); // "0.000e0"
        if (!zero_str) return NULL;
        strcpy(zero_str, "0.000e0");
        return zero_str;
    }

    // Allocate enough space for: sign + 1 digit + '.' + PRINT_DIGITS - 1 + "e" + exponent (say 5 digits max) + null
    char* str = (char*)malloc(PRINT_DIGITS + 10);
    if (!str) return NULL;

    int exponent = a->size - 1;

    // Most significant digits start from the end of the array
    int index = a->size - 1;
    str[0] = a->digits[index] + '0';
    str[1] = '.';

    // Copy next PRINT_DIGITS - 1 digits (or pad with zero if fewer)
    for (int i = 1; i < PRINT_DIGITS; i++) {
        index--;
        str[i + 1] = (index >= 0) ? (a->digits[index] + '0') : '0';
    }

    str[PRINT_DIGITS + 1] = 'e';
    snprintf(str + PRINT_DIGITS + 2, 8, "%d", exponent);

    return str;
}

#endif