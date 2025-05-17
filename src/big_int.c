#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_DIGITS 400
#define PRINT_DIGITS 5

typedef struct BigInt {
    int digits[MAX_DIGITS];
    int size;
} BigInt;


BigInt* bigint_create(int value) {
    BigInt* a = (BigInt*)malloc(sizeof(BigInt));
    if(!a) // Handle allocation failure
        return NULL;

    memset(a->digits, 0, sizeof(a->digits));
    a->size = 0;

    while(value > 0) {
        a->digits[a->size++] = value % 10;
        value /= 10;
    }

    if (a->size == 0) a->size = 1;

    return a;
}

// Print BigInt
void bigint_print(const BigInt *a) {
    if(a->size < 11) {
        for(int i = a->size - 1; i >= 0; i--)
            printf("%d", a->digits[i]);
    } else {
        printf("%d", a->digits[a->size - 1]);  // Most significant digit

        if (PRINT_DIGITS > 1) {
            printf(".");
            int printed = 1;
            for (int i = a->size - 2; i >= 0 && printed < PRINT_DIGITS; i--) {
                printf("%d", a->digits[i]);
                printed++;
            }
        }

        printf("e+%d", a->size - 1);
    }
}

// Multiply big int by integer
void bigint_mul_int(BigInt *a, int b) {
    int carry = 0;
    for(int i = 0; i < a->size; i++) {
        int prod = a->digits[i] * b + carry;
        a->digits[i] = prod % 10;
        carry = prod / 10;
    }

    while (carry) {
        a->digits[a->size++] = carry % 10;
        carry /= 10;
    }
}


void bigint_div_int(BigInt *a, int b) {
    int rem = 0;
    for(int i = a->size - 1; i >= 0; i--) {
        int current = rem * 10 + a->digits[i];
        a->digits[i] = current / b;
        rem = current % b;
    }

    while(a->size > 1 && a->digits[a->size - 1] == 0) {
        a->size--;
    }
}


BigInt* compute_binomial(int n, int k) {
    BigInt* res = bigint_create(1);

    for(int i = 1; i <= k; i++) {
        bigint_mul_int(res, n - i + 1);
        bigint_div_int(res, i);
    }

    return res;
}


BigInt* get_num_combos(int* program_blocks, int* block_amounts, int num_sizes) {
    BigInt* result = bigint_create(1);  // initialize result

    for (int i = 0; i < num_sizes; i++) {
        // Get binomial inputs
        int n = block_amounts[i];
        int k = program_blocks[i];

        if (k > n)
            return bigint_create(0);  // Invalid case

        if (k == 0 || k == n)
            continue; // skip iteration, possibilities will be 1

        BigInt* binom = compute_binomial(n, k);

        // Multiply current result by binom
        BigInt* new_result = bigint_create(0);  // temp result
        new_result->size = 1;
        new_result->digits[0] = 0;

        for (int j = 0; j < binom->size; j++) {
            BigInt temp = *result;
            bigint_mul_int(&temp, binom->digits[j]);
            for (int k = 0; k < j; k++) {
                bigint_mul_int(&temp, 10);
            }

            // Add temp to new_result
            for (int d = 0, carry = 0; d < MAX_DIGITS; d++) {
                int sum = new_result->digits[d] + (d < temp.size ? temp.digits[d] : 0) + carry;
                new_result->digits[d] = sum % 10;
                carry = sum / 10;
            }

            new_result->size = MAX_DIGITS;
            while (new_result->size > 1 && new_result->digits[new_result->size - 1] == 0)
                new_result->size--;
        }

        free(result);
        result = new_result;
        free(binom);
    }

    return result;
}

