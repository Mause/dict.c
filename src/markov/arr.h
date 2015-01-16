#ifndef ARR_H
#define ARR_H

#define GROW_FACTOR 1.25

typedef struct {
    char** array;
    int len;
    int size;
} LengthedArray;

LengthedArray* arr_create(void);
void arr_free(LengthedArray* arr);

/* may return pointer to new array if we had to resize */
LengthedArray* arr_append(LengthedArray* arr, char* value);

#endif
