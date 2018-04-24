#include "avl.h"
#include <assert.h>
#include <stddef.h>
#include <stdio.h>

typedef struct {
    int number;
    avl_node_t node;
} test_avl_t;

static int test_avl_compare(const avl_node_t *lhs,
                            const avl_node_t *rhs,
                            const void *aux)
{
    const test_avl_t *a = avl_ref(lhs, test_avl_t, node);
    const test_avl_t *b = avl_ref(rhs, test_avl_t, node);
    if (a->number < b->number)
        return -1;
    if (a->number > b->number)
        return 1;
    return 0;
}

int avl()
{
    avl_tree_t tree;
    avl_init(&tree, NULL);

    test_avl_t a = {1, {0, NULL, NULL, NULL, NULL}};
    test_avl_t b = {2, {0, NULL, NULL, NULL, NULL}};
    test_avl_t c = {3, {0, NULL, NULL, NULL, NULL}};

    avl_insert(&tree, &a.node, &test_avl_compare);
    avl_insert(&tree, &b.node, &test_avl_compare);
    avl_insert(&tree, &c.node, &test_avl_compare);

    int expected[4][2] = {
        [1] = {2, -1},
        [2] = {3, 1},
        [3] = {-1, 2},
    };

    avl_node_t *node = avl_head(&tree);
    while (node) {
        avl_node_t *next = avl_next(node);
        avl_node_t *prev = avl_prev(node);
        test_avl_t *c = avl_ref(node, test_avl_t, node);
        test_avl_t *n = next ? avl_ref(next, test_avl_t, node) : NULL;
        test_avl_t *p = prev ? avl_ref(prev, test_avl_t, node) : NULL;

        assert(expected[c->number][0] == (n ? n->number : -1));
        assert(expected[c->number][1] == (p ? p->number : -1));

        node = next;
    }
    return 0;
}

int main()
{
    return avl();
}
