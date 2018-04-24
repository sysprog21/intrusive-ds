#include "list.h"
#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

typedef struct {
    const char *message;
    link_t link;
} test_list_t;

int list()
{
    list_t list;
    list_init(&list);

    test_list_t a = {"Hello", {NULL, NULL}};
    test_list_t b = {"Intrusive", {NULL, NULL}};
    test_list_t c = {"World", {NULL, NULL}};

    list_push_back(&list, &a.link);
    list_push_back(&list, &b.link);
    list_push_back(&list, &c.link);

    struct {
        char *msg1, *msg2, *msg3;
    } expected[3] = {
        {"Hello", "Intrusive", "(None)"},
        {"Intrusive", "World", "Hello"},
        {"World", "(None)", "Intrusive"},
    };
    int i = 0;

    link_t *node = list_head(&list);
    while (node) {
        link_t *next = list_next(node);
        link_t *prev = list_prev(node);
        test_list_t *c = list_ref(node, test_list_t, link);
        test_list_t *n = next ? list_ref(next, test_list_t, link) : NULL;
        test_list_t *p = prev ? list_ref(prev, test_list_t, link) : NULL;

        assert(!strcmp(expected[i].msg1, c->message));
        assert(!strcmp(expected[i].msg2, n ? n->message : "(None)"));
        assert(!strcmp(expected[i].msg3, p ? p->message : "(None)"));
        i++;

        node = next;
    }
    return 0;
}

int main()
{
    return list();
}
