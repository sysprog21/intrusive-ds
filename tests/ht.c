#include "ht.h"
#include <assert.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

typedef struct {
    const char *message;
    hashnode_t node;
} test_hash_t;

size_t hash_func(const void *key, size_t keylen)
{
    // One character keys for test, you can implement a more complex hash
    // function here
    return ((const char *) key)[0];
}

int hash(void)
{
    hashtable_t hash;

    test_hash_t a = {"Hello", {NULL, 0, NULL}};
    test_hash_t b = {"Intrusive", {NULL, 0, NULL}};
    test_hash_t c = {"World", {NULL, 0, NULL}};

    hashtable_init(&hash, 10, &hash_func);

    hashtable_insert(&hash, &a.node, "a", 2);
    hashtable_insert(&hash, &b.node, "b", 2);
    hashtable_insert(&hash, &c.node, "c", 2);

    hashnode_t *ga = hashtable_search(&hash, "a", 2);
    hashnode_t *gb = hashtable_search(&hash, "b", 2);
    hashnode_t *gc = hashtable_search(&hash, "c", 2);

    test_hash_t *aa = hashtable_ref(ga, test_hash_t, node);
    test_hash_t *bb = hashtable_ref(gb, test_hash_t, node);
    test_hash_t *cc = hashtable_ref(gc, test_hash_t, node);

    char *expected[3] = {
        "Hello",
        "Intrusive",
        "World",
    };

    assert(!strcmp(expected[0], aa->message));
    assert(!strcmp(expected[1], bb->message));
    assert(!strcmp(expected[2], cc->message));

    hashtable_destroy(&hash);
    return 0;
}

int main()
{
    return hash();
}
