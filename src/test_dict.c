#include <stdio.h>
#include <assert.h>

#include "dict.h"
#include "bool.h"

int testBasic(bool debug) {
    bool res;
    dict* table = dict_create(100);
    table->debug = debug;

    dict_set(table, "World", "Hello");

    res = strcmp(
        dict_get(table, "World"),
        "Hello"
    ) == 0;

    dict_free(table);

    return res;
}

int testRemoveValue(bool debug) {
    bool res;
    dict* table = dict_create(20);
    table->debug = debug;

    dict_set(table, "World", "Hello");

    dict_remove(table, "World");

    res = dict_get(table, "World") == NULL;

    dict_free(table);

    return res;
}

int testResizeLarger(bool debug) {
    bool res;
    dict* table = dict_create(3);
    table->debug = debug;

    dict_set(table, "World", "Hello");
    dict_set(table, "Worle", "Hello");

    // "the bucket number should have increased since the table was initialized",
    res = table->max_size > 3;

    dict_free(table);

    return res;
}

int testResizeSmaller(bool debug) {
    bool res;
    int actual;
    dict* table = dict_create(7);
    table->debug = debug;

    // internally we choose the next largest prime than the number specified
    actual = table->max_size;

    dict_set(table, "Hello", "World");

    // "the bucket number should have decreased since the table was initialized",
    res = table->max_size < actual;

    dict_free(table);

    return res;
}

int testContainsKey(bool debug) {
    bool res = TRUE;
    dict* table = dict_create(7);
    table->debug = debug;

    // "An empty hashtable shouldn't contain the key",
    res = res && (!dict_contains_key(table, "world"));

    dict_set(table, "world", "hello");

    // "hashtable should contain a key after it has been put in",
    res = res && dict_contains_key(table, "world");

    dict_remove(table, "world");

    // "hashtable shouldn't contain a key that has been removed",
    res = res && (!dict_contains_key(table, "world"));

    dict_free(table);

    return res;
}

#define test(func, name) \
    printf("%s running\n-----------------------------\n\n", name);\
    assert(func(debug));\
    printf("%s succeeded\n-----------------------------\n\n", name); \

int main(int argc, char const *argv[]) {
    bool debug = (argc > 1) && (strcmp(argv[1], "-d") == 0);

    test(testBasic, "testBasic");
    test(testRemoveValue, "testRemoveValue");
    test(testContainsKey, "testContainsKey");
    test(testResizeLarger, "testResizeLarger");
    test(testResizeSmaller, "testResizeSmaller");

    /* code */
    return 0;
}
