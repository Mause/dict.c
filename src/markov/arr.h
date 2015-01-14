#ifndef ARR_H
#define ARR_H

typedef struct {
    char** array;
    int len;
    int size;
} LengthedArray;

LengthedArray* arr_create();

/* may return pointer to new array if we had to resize */
LengthedArray* arr_append(LengthedArray* arr, char* value);

#endif
