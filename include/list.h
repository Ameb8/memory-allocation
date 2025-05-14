#ifndef LIST_H
#define LIST_H

typedef struct List List;
typedef struct ListIt ListIt;

List* list_create();
void list_add(List* list, Combo* combo);
void list_free(List *list);
ListIt* list_it_create(List* list);
bool list_it_has_next(ListIt* list_it);
Combo* list_it_next(ListIt* list_it);

#endif