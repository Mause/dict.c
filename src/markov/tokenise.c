#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "tokenise.h"
#include "arr.h"


void record(dict* d, char* key, char* value) {
    dict_entry* old_entry;
    LengthedArray* existing = dict_get(d, key);

    if (existing == NULL) {
        existing = arr_create();
    }

    old_entry = dict_set(
        d,
        key,
        arr_append(existing, value)
    );
    if (old_entry != NULL) {
        free(old_entry->key);
        free(old_entry);
    }
}


bool is_lower(char c) {
    return c >= 'A' && c <= 'Z';
}


char* lowercase(char* str) {
    int i, len=strlen(str);

    for (i=0; i<len; i++) {
        if (is_lower(str[i])) {
            str[i] += 'a' - 'A';
        }
    }

    return str;
}


char* get_word(FILE* in_file) {
    char* word = calloc(100, sizeof(char));

    assert(fscanf(in_file, "%s", word) == 1);

    return word == NULL ? NULL : lowercase(word);
}


dict* tokenise_file(dict* lookup_table, char* filename) {
    FILE* input_file;
    char* previous_word = NULL, *cur_word;

    input_file = fopen(filename, "r");
    if (input_file == NULL) return NULL;

    previous_word = get_word(input_file);

    while (feof(input_file) == 0) {
        cur_word = get_word(input_file);
        if (cur_word == NULL) {
            // no more words
            break;
        }

        record(lookup_table, strdup(previous_word), strdup(cur_word));

        free(previous_word);
        previous_word = strdup(cur_word);
    }

    fclose(input_file);
    free(previous_word);
    free(cur_word);

    return lookup_table;
}


dict* tokenise_files(options* ops) {
    int i;
    dict *lookup_table, *temp;

    lookup_table = dict_create(10);
    lookup_table->debug = ops->debug;

    for (i=0; i<ops->files->len; i++) {
        char* filename = ops->files->array[i];

        temp = tokenise_file(lookup_table, filename);
        if (temp == NULL) {
            lookup_table_free(lookup_table);
            return NULL;
        }

        if (ops->debug) printf("done tokenising %s\n", filename);
    }

    return lookup_table;
}
