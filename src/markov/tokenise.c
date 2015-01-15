#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "tokenise.h"
#include "arr.h"


void record(dict* d, char* key, char* value) {
    LengthedArray* existing = dict_get(d, key);

    if (existing == NULL) {
        existing = arr_create();
        dict_set(d, key, existing);
    }

    dict_set(
        d,
        key,
        arr_append(existing, value)
    );
}


dict* tokenise_file(dict* lookup_table, char* filename) {
    FILE* input_file;
    char* previous_word = NULL, *cur_word;

    input_file = fopen(filename, "r");
    if (input_file == NULL) return NULL;

    previous_word = calloc(100, sizeof(char));
    cur_word = calloc(100, sizeof(char));
    assert(fscanf(input_file, "%s", previous_word) == 1);

    while (feof(input_file) == 0) {
        assert(cur_word != NULL);
        if(fscanf(input_file, "%s", cur_word) != 1) break;
        if (cur_word == NULL) break;

        record(lookup_table, strdup(previous_word), strdup(cur_word));

        free(previous_word);
        previous_word = strdup(cur_word);
    }

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
        if (temp == NULL) return NULL;
    }

    return lookup_table;
}
