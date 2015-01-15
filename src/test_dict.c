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


int testStress(bool debug) {
    dict* d = dict_create(20);
    d->debug = debug;

    dict_set(d, "Depending", "on");
    dict_set(d, "on", "the");
    dict_set(d, "the", "format");
    dict_set(d, "format", "string,");
    dict_set(d, "string,", "the");
    dict_set(d, "the", "function");
    dict_set(d, "function", "may");
    dict_set(d, "may", "expect");
    dict_set(d, "expect", "a");
    dict_set(d, "a", "sequence");
    dict_set(d, "sequence", "of");
    dict_set(d, "of", "additional");
    dict_set(d, "additional", "arguments,");
    dict_set(d, "arguments,", "each");
    dict_set(d, "each", "containing");
    dict_set(d, "containing", "a");
    dict_set(d, "a", "pointer");
    dict_set(d, "pointer", "to");
    dict_set(d, "to", "allocated");
    dict_set(d, "allocated", "storage");
    dict_set(d, "storage", "where");
    dict_set(d, "where", "the");
    dict_set(d, "the", "interpretation");
    dict_set(d, "interpretation", "of");
    dict_set(d, "of", "the");
    dict_set(d, "the", "extracted");
    dict_set(d, "extracted", "characters");
    dict_set(d, "characters", "is");
    dict_set(d, "is", "stored");
    dict_set(d, "stored", "with");
    dict_set(d, "with", "the");

    dict_free(d);

    return TRUE;
}


int testOverwritingKeys(bool debug) {
    dict* table = dict_create(5);

    dict_set(table, "key", "value1");
    dict_set(table, "key", "value2");

    return strcmp(dict_get(table, "key"), "value2") == 0;
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
    test(testOverwritingKeys, "testOverwritingKeys");
    test(testStress, "testStress");

    /* code */
    return 0;
}
