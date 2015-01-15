#include <stdlib.h>
#include <string.h>

#include "options.h"
#include "arr.h"

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
            ops->num_sentences = atoi(argv[++i]);

        } else {
            ops->files = arr_append(ops->files, strdup(argv[i]));
        }
    }

    return ops;
}
