typedef struct {
    int* program_blocks;
    int* block_sizes;
    int num_sizes;
    int num_combos;
} Combo;

Combo* combo_create(int* program_blocks, int* block)

