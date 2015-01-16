#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "options.h"
#include "arr.h"


void printHelp(char const *argv[]) {
    fprintf(stderr, "%s [-d] [-n number of sentences] input_file.txt [...] \n", argv[0]);
}


options* parse_options(int argc, char const *argv[]) {
    int i;
    options* ops = calloc(sizeof(options), 1);
    ops->debug = FALSE;
    ops->files = arr_create();
    ops->num_sentences = 1;

    for (i=1; i<argc; i++) {
               if (strcmp(argv[i], "-d") == 0) {
            ops->debug = TRUE;

        } else if (strcmp(argv[i], "-n") == 0) {
            if (i == argc-1) {
                printHelp(argv);
                fprintf(stderr, "No argument provided for -n\n");
                return NULL;
            }
            ops->num_sentences = atoi(argv[++i]);

        } else {
            ops->files = arr_append(ops->files, strdup(argv[i]));
        }
    }

    if (ops->files->len == 0) {
        printHelp(argv);
        fprintf(stderr, "You must supply at least one source file\n");
        return NULL;
    }

    return ops;
}
