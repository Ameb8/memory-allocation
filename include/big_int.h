#ifndef BIG_INT_H
#define BIG_INT_H

typedef struct BigInt BigInt;
void bigint_print(const BigInt *a);
BigInt* get_num_combos(int* program_blocks, int* block_amounts, int num_sizes);

#endif