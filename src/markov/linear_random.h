#include <stdio.h>

/* always assuming int is at least 32 bits */
int rand();
int rseed = 0;

void srand(int x) {
    rseed = x;
}

#ifndef MS_RAND
#define RAND_MAX ((1U << 31) - 1)

int rand()
{
    return rseed = (rseed * 1103515245 + 12345) & RAND_MAX;
}

#else /* MS rand */

#define RAND_MAX_32 ((1U << 31) - 1)
#define RAND_MAX ((1U << 15) - 1)

int rand()
{
    return (rseed = (rseed * 214013 + 2531011) & RAND_MAX_32) >> 16;
}

#endif/* MS_RAND */
