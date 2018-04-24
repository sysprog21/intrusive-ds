#include "rb.h"
#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

typedef struct {
    int number;
    rb_node_t node;
} test_rb_t;

int test_rb_compare(const rb_node_t *lhs, const rb_node_t *rhs, const void *aux)
{
    const test_rb_t *a = rb_ref(lhs, test_rb_t, node);
    const test_rb_t *b = rb_ref(rhs, test_rb_t, node);
    if (a->number < b->number)
        return -1;
    if (a->number > b->number)
        return 1;
    return 0;
}

int rb()
{
    rb_tree_t tree;
    rb_init(&tree, NULL);

    test_rb_t a = {1, {0, NULL, NULL}};
    test_rb_t b = {2, {0, NULL, NULL}};
    test_rb_t c = {3, {0, NULL, NULL}};

    rb_insert(&tree, &a.node, &test_rb_compare);
    rb_insert(&tree, &b.node, &test_rb_compare);
    rb_insert(&tree, &c.node, &test_rb_compare);

    int expected[4][2] = {
        [1] = {2, -1},
        [2] = {3, 1},
        [3] = {-1, 2},
    };

    rb_node_t *node = rb_head(&tree);
    while (node) {
        rb_node_t *next = rb_next(node);
        rb_node_t *prev = rb_prev(node);
        test_rb_t *c = rb_ref(node, test_rb_t, node);
        test_rb_t *n = next ? rb_ref(next, test_rb_t, node) : NULL;
        test_rb_t *p = prev ? rb_ref(prev, test_rb_t, node) : NULL;

        assert(expected[c->number][0] == (n ? n->number : -1));
        assert(expected[c->number][1] == (p ? p->number : -1));

        node = next;
    }
    return 0;
}

int main()
{
    return rb();
}
