#ifndef OPTIONS_H
#define OPTIONS_H

#include "../dict.h"

#include "arr.h"

typedef struct {
    LengthedArray* files;
    bool debug;
    int num_sentences;
} options;

options* parse_options(int argc, char const *argv[]);

#endif
