#include <stdio.h>
#include "uthash.h"

typedef struct NODE {
    int key;
    char name[20];
    struct UT_hash_handle hh;
}NODE;

void iter_hash(NODE *head) {
    NODE *cur = NULL;
    NODE *temp = NULL;
    HASH_ITER(hh, head, cur, temp) {
        printf("%d->%s.", cur->key, cur->name);
    }
    printf("\n");
}

int compare(const void *a, const void *b) {
    NODE a_ = *(NODE *)a;
    NODE b_ = *(NODE *)b;
    return a_.key - b_.key;
}

int compare_area(const void *a, const void *b) {
    int *a_ = (int *)a;
    int *b_ = (int *)b;
    if (a_[0] != b_[0]) {
        return a_[0] - b_[0];
    }
    return a_[1] - b_[1];
}

void test_hash_func() {
    NODE *head = NULL;
    for (int i = 0; i < 10; i++) {
        NODE *node = (NODE *)malloc(sizeof(NODE));
        memset(node, 0, sizeof(NODE));
        node->key = 10 - i;
        sprintf(node->name, "%c%c", 'a' + i * 2, 'b' + i * 2 + 1);
        HASH_ADD_INT(head, key, node);
    }
    NODE *cur = NULL;
    NODE *temp = NULL;
    HASH_ITER(hh, head, cur, temp) {
        printf("%d->%s,", cur->key, cur->name);
    }
    printf("\n");
    NODE *node_del = NULL;
    int find_key = 5;
    HASH_FIND_INT(head, &find_key, node_del);
    if (node_del != NULL) {
        HASH_DEL(head, node_del);
    }
    HASH_SORT(head, compare);
    iter_hash(head);

    int area[][2] = {{32,112}, {32,231}, {23, 324}};
    qsort(area, 3, sizeof(area[0]), compare_area);
    for (int i = 0; i < 3; i++) {
        printf("%d %d\n", area[i][0], area[i][1]);
    }
}

int main() {
    test_hash_func();
    return 0;
}
