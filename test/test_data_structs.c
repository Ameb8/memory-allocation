#ifdef TEST


#include "../include/list.h"
#include "test_util.h"
#include "test_data_structs.h"

void test_list() {
    List* list = list_create();

    ASSERT_INT_EQ(0, list_size(list));

    int it_1[] = {1, 1};
    int it_2[] = {2, 1};
    int it_3[] = {3, 1};

    list_add(list, it_1);
    list_add(list, it_2);
    list_add(list, it_3);

    ASSERT_INT_EQ(3, list_size(list));

    int it_4[] = {1, 1};
    
    list_increment(list, it_4);

    ASSERT_INT_EQ(3, list_size(list));

    ListIt* it = list_it_create(list);

    int* res = list_it_next(it);
    ASSERT_INT_EQ(3, res[0]);
    ASSERT_INT_EQ(1, res[1]);

    res = list_it_next(it);
    ASSERT_INT_EQ(2, res[0]);
    ASSERT_INT_EQ(1, res[1]);

    res = list_it_next(it);
    ASSERT_INT_EQ(1, res[0]);
    ASSERT_INT_EQ(2, res[1]);
}

void test_data_structs() {
    test_list();
}


#endif