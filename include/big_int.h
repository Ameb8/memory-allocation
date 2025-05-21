#ifndef BIG_INT_H
#define BIG_INT_H

typedef struct BigInt BigInt;
void bigint_print(const BigInt *a);
BigInt* get_num_combos(int* program_blocks, int* block_amounts, int num_sizes);

#ifdef TEST
char* bigint_to_string(const BigInt* a);
char* bigint_to_sci(const BigInt* a);
#endif

#endif