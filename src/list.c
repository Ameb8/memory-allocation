#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "../include/list.h"
#include "../include/combos.h"

typedef struct {
    Combo* combo;
    struct ListNode* next;
} ListNode;

typedef struct {
    ListNode* node;
} ListIt;

typedef struct {
    ListNode* head;
} List;

List* list_create() {
    List *list = malloc(sizeof(List));
    list->head = NULL;

    return list;
}

void list_add(List* list, Combo* combo) {
    if(!list) return;
    if(!combo) return;
    
    ListNode* node = malloc(sizeof(ListNode));
    node->combo = combo;

    node->next = list->head;
    list->head = node;
}

void list_free(List *list) {
    if(!list) return;

    ListNode* current = list->head;

    while(current) {
        ListNode* temp = current;
        current = current->next;
        free(temp->combo);
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

Combo* list_it_next(ListIt* list_it) {
    if(!list_it)
        return NULL;

    Combo* c = list_it->node->combo;
    list_it->node = list_it->node->next;

    return c;
}
