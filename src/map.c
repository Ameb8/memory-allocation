#include <stdio.h>
#include <stdlib.h>
#include "../include/combos.h"
#include "../include/list.h"


typedef struct {
    List** buckets;
    List* used_buckets;
    int size;
    int capacity
} Map;


typedef struct {
    int* program_blocks;
    int* block_sizes;
    int num_sizes;
    int num_combos;
} Combo;

unsigned long hash_component(const Combo* c) {
    unsigned long hash = 5381;

    for (int i = 0; i < c->num_sizes; i++) 
        hash = ((hash << 5) + hash) ^ c->program_blocks[i];

    return hash;
}

Map* map_create(int capacity) {
    Map* map = malloc(sizeof(Map));
    map->buckets = calloc(capacity, sizeof(List*));
    map->used_buckets = list_create();

    return map;
}

Map* map_insert(Map* map, Combo* c) {
    long index = hash_component(c) % map->capacity;

    if(!map->buckets[index]) {
        map->buckets[index] = list_create();
        list_add(map->used_buckets, index, sizeof(unsigned long));
    }

    list_add(map->buckets[index], c, sizeof(Combo*));
}

Map* 