#ifndef DICT_H
#define DICT_H

#include "dict_entry.h"
#include "bool.h"

#define MAX_STEP 3
#define GLASS_HALF_FULL 60
#define GLASS_HALF_EMPTY 30

typedef struct {
    int count;
    int max_size;
    dict_entry** entries;
    bool debug;
} dict;

dict*       dict_create(int max_size);
dict_entry* dict_set         (dict* d, char* key, void* value);
void*       dict_get         (dict* d, char* key);
void*       dict_remove      (dict* d, char* key);
bool        dict_contains_key(dict* d, char* key);
bool        dict_valid_entry (dict* d, int i);
void        dict_repr        (dict* d);
char**      dict_keys        (dict* d);
void        dict_free        (dict* d);

#endif
