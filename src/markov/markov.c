#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "../dict.h"

#include "arr.h"
#include "linear_random.h"
#include "options.h"


int rand_in_range(int max) {
    assert(max != 0);

    return (rand() % max) + 1;
}


char* get_starting(dict* lookup_table) {
    char *starting_word, **keys;

    keys = dict_keys(lookup_table);
    starting_word = strdup(keys[rand_in_range(lookup_table->count)]);
    free(keys);

    return starting_word;
}


bool ispunc(char c) {
    return (
        (c == ')') ||
        (c == '.')
    );
}


char* build_markov_string(dict* lookup_table) {
    int num;
    char *str, *starting_word, start, end, *previous_word;

    // allow sentences up to 4096 chars in length
    str = calloc(1 << 12, sizeof(char));

    do {
        starting_word = get_starting(lookup_table);

        start = starting_word[0];
        end = starting_word[strlen(starting_word)-1];
    } while (ispunc(start) || ispunc(end));

    strcat(str, starting_word);

    previous_word = starting_word;
    do {
        int selected;
        LengthedArray* arr;

        arr = dict_get(lookup_table, previous_word);
        assert(arr != NULL);

        selected = rand_in_range(arr->len);
        previous_word = arr->array[selected % arr->len];
        strcat(str, " ");
        strcat(str, previous_word);

        // do while we've not encountered a word ending in a full-stop
    } while (previous_word[strlen(previous_word)-1] != '.');

    // capitalise the first character of the sentence
    if (str[0] >= 'a' && str[0] <= 'z') {
        str[0] -= 'a' - 'A';
    }

    return str;
}


int main(int argc, char const *argv[]) {
    dict* lookup_table;
    options* ops;
    char *str;
    int i;

    if (argc == 1) {
        fprintf(stderr, "Not enough args\n");
        return -1;
    }

    ops = parse_options(argc, argv);
    if (ops->files->len == 0) {
        fprintf(stderr, "You must supply at least one source file\n");
        return -1;
    }

    lookup_table = tokenise_files(ops);
    assert(lookup_table->count != 0);

    if (lookup_table == NULL) {
        fprintf(stderr, "Couldn't build lookup table\n");
        return;
    }

    // seed the random number generator; we want random sentences!
    srand(time(NULL));

    for (i=0; i<ops->num_sentences; i++) {
        str = build_markov_string(lookup_table);
        printf("%s\n", str);
        free(str);
    }

    if (ops->debug) {
        printf("\n");
        printf("%d words in lookup table\n", lookup_table->count);
    }

    dict_free(lookup_table);

    return 0;
}
