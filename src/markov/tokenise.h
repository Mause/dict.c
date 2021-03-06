#ifndef TOKENISE_H
#define TOKENISE_H

#include "../../dict.h"
#include "arr.h"

void record(dict* d, char* key, char* value);
dict* tokenise_file(dict* lookup_table, char* filename);
dict* tokenise_files(LengthedArray* files, bool debug);

#endif
