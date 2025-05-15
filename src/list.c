#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "../include/list.h"
#include "../include/combos.h"

typedef struct ListNode {
    int* blocks;
    struct ListNode* next;
} ListNode;

typedef struct ListIt {
    ListNode* node;
} ListIt;

typedef struct List {
    ListNode* head;
    int size;
} List;

List* list_create() {
    List *list = calloc(1, sizeof(List));

    return list;
}

void list_add(List* list, int* blocks) {
    if(!list) return;
    if(!blocks) return;

    #ifdef DEBUG
    printf("Adding new block: size=%d, amount=%d\n", blocks[0], blocks[1]);
    #endif

    list->size++;
    ListNode* node = malloc(sizeof(ListNode));
    node->blocks = blocks;

    node->next = list->head;
    list->head = node;
} 

void list_increment(List* list, int* blocks) {
    if(!list || !blocks)
        return;

    ListNode* temp = list->head;

    while(temp) {
        if(temp->blocks[0] == blocks[0]) {
            temp->blocks[1] += blocks[1];
            return;
        }

        temp = temp->next;
    }

    list_add(list, blocks);
}

int list_size(List* list) {
    return list->size;
}

void list_free(List *list) {
    if(!list) return;

    ListNode* current = list->head;

    while(current) {
        ListNode* temp = current;
        current = current->next;
        free(temp->blocks);
        free(temp);
    }

    free(list);
}

ListIt* list_it_create(List* list) {
    if(!list)
        return NULL;

    ListIt* list_it= malloc(sizeof(ListIt));
    list_it->node = list->head;

    return list_it;
}

bool list_it_has_next(ListIt* list_it) {
    if(!list_it)
        return NULL;

    if(!list_it->node)
        return false;

    return true;
}

int* list_it_next(ListIt* list_it) {
    if(!list_it)
        return NULL;

    int* blocks = list_it->node->blocks;
    list_it->node = list_it->node->next;

    return blocks;
}

