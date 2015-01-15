#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "../dict.h"

#include "arr.h"
#include "linear_random.h"
#include "options.h"
#include "tokenise.h"


int rand_in_range(int max) {
    assert(max != 0);

    return (rand() % max) + 1;
}


char* get_starting(dict* lookup_table) {
    char *starting_word, **keys;

    keys = dict_keys(lookup_table);
    starting_word = keys[rand_in_range(lookup_table->count)-1];
    free(keys);

    return starting_word;
}


bool ispunc(char c) {
    return (
        (c == ')') ||
        (c == '.')
    );
}


char* coalesce_word_array(LengthedArray* arr, int length) {
    int i;
    char *start_of_str = calloc((length + 1), sizeof(char)),
         *str = start_of_str;

    for (i=0; i<arr->len; i++) {
        if (i != 0) {
            str = strcat(str, " ");
        }
        str = strcat(str, arr->array[i]);
    }

    return start_of_str;
}


bool is_ending(char c) {
    switch(c) {
    case '.': case '?': case '!': return TRUE;
    default:                      return FALSE;
    }
}


char* build_markov_string(dict* lookup_table) {
    int num, length;
    LengthedArray* word_arr;
    char *str, start, end, *previous_word;

    // allow sentences up to 4096 chars in length
    word_arr = arr_create();

    do {
        previous_word = get_starting(lookup_table);

        start = previous_word[0];
        end = previous_word[strlen(previous_word)-1];
    } while (ispunc(start) || ispunc(end));

    length = strlen(previous_word);
    arr_append(word_arr, strdup(previous_word));

    do {
        int selected;
        LengthedArray* arr;

        if (lookup_table->debug) {
            printf("Word: %s\n", previous_word);
        }

        arr = dict_get(lookup_table, previous_word);
        assert(arr != NULL);

        selected = rand_in_range(arr->len);
        previous_word = arr->array[selected % arr->len];

        arr_append(word_arr, strdup(previous_word));
        length += 1 + strlen(previous_word);

        // do while we've not encountered a word ending in a full-stop
    } while (!is_ending(previous_word[strlen(previous_word)-1]));

    str = coalesce_word_array(word_arr, length);
    arr_free(word_arr);

    // capitalise the first character of the sentence
    if (str[0] >= 'a' && str[0] <= 'z') {
        str[0] -= 'a' - 'A';
    }

    return str;
}


void lookup_table_free(dict* lookup_table) {
    int i;

    for (i=0; i<lookup_table->max_size; i++) {
        if (dict_valid_entry(lookup_table, i)) {
            dict_entry* entry = lookup_table->entries[i];
            free(entry->key);
            arr_free(entry->value);
        }
    }
    dict_free(lookup_table);
}


void printHelp(char const *argv[]) {
    fprintf(stderr, "%s [-d] [-n number of sentences] input_file.txt [...] \n", argv[0]);
}


int main(int argc, char const *argv[]) {
    dict* lookup_table;
    options* ops;
    char *str;
    int i;

    ops = parse_options(argc, argv);
    if (ops->files->len == 0) {
        printHelp(argv);
        fprintf(stderr, "You must supply at least one source file\n");
        return -1;
    }

    lookup_table = tokenise_files(ops);
    if (lookup_table == NULL) {
        fprintf(stderr, "Failed to load files\n");
        return -1;
    }
    assert(lookup_table->count != 0);

    if (ops->debug) printf("Done tokenising files\n");

    if (lookup_table == NULL) {
        fprintf(stderr, "Couldn't build lookup table\n");
        return;
    }

    // seed the random number generator; we want random sentences!
    srand(time(NULL));

    for (i=0; i<ops->num_sentences; i++) {
        if (ops->debug) printf("Building sentence number %d\n", i);
        str = build_markov_string(lookup_table);
        printf("%s\n", str);
        free(str);
    }

    if (ops->debug) {
        printf("\n");
        printf("%d words in lookup table\n", lookup_table->count);
    }

    arr_free(ops->files);
    free(ops);

    lookup_table_free(lookup_table);

    return 0;
}
