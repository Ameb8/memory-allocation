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


// Instantiate empty list
List* list_create() {
    List *list = calloc(1, sizeof(List));

    return list;
}


// Prepend allocation to list
void list_add(List* list, int* blocks) {
    // Inputs null
    if(!list) return;
    if(!blocks) return;
    
    list->size++; // Update list size
    ListNode* node = malloc(sizeof(ListNode)); // Allocate memory for node
    
    // Set node and list pointers
    node->blocks = blocks;
    node->next = list->head;
    list->head = node;
} 


// If first value in blocks is unique, add to list
// Otherwise, sum 2nd value in blocks with existing entry
void list_increment(List* list, int* blocks) {
    if(!list || !blocks)
        return; // Null inputs

    ListNode* temp = list->head; // Temp node to traverse list

    while(temp) { // Traverse list
        // Existing value found, sum and return
        if(temp->blocks[0] == blocks[0]) {
            temp->blocks[1] += blocks[1];
            return;
        }

        temp = temp->next;
    }

    // Unique value for blocks[0], add to list
    list_add(list, blocks);
}


// Get list size
int list_size(List* list) {
    return list->size;
}


// Free list from memory
void list_free(List *list) {
    if(!list) return;

    ListNode* current = list->head;

    while(current) { // Free all nodes in list
        ListNode* temp = current;
        current = current->next;
        free(temp->blocks);
        free(temp);
    }

    free(list); // Free list itself
}


// Create list iterator
ListIt* list_it_create(List* list) {
    if(!list) // Cannot iterate through null list
        return NULL;

    ListIt* list_it= malloc(sizeof(ListIt)); // Allocate memory
    list_it->node = list->head;  // Set first node in list as current

    return list_it;
}


// Check if more nodes to iterate through
bool list_it_has_next(ListIt* list_it) {
    if(!list_it) // Null input
        return NULL;

    // Current is null
    if(!list_it->node)
        return false;

    return true;
}


// Get next l
int* list_it_next(ListIt* list_it) {
    if(!list_it || !list_it->node)
        return NULL; // Null inputs

    int* blocks = list_it->node->blocks; // Get current element
    list_it->node = list_it->node->next; // Set next element

    return blocks;
}

