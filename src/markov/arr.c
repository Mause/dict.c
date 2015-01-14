#include "arr.h"

LengthedArray* arr_create() {
    LengthedArray* arr;

    arr = malloc(sizeof(LengthedArray));
    arr->array = calloc(100, sizeof(char*));
    arr->size = 100;
    arr->len = 0;

    return arr;
}

/* may return pointer to new array if we had to resize */
LengthedArray* arr_append(LengthedArray* arr, char* value) {
    if (arr->len == arr->size) {
        // is full, we reallocate
        arr->array = realloc(
            arr->array,
            (arr->size * 1.25) *  sizeof(char*)
        );
        arr->size *= 1.25;
    }
    arr->array[arr->len++] = value;

    return arr;
}