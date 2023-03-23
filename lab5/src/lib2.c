#include "lab5.h"
#include <stdlib.h>

int Compare(const void* a, const void* b) {
    return (*(int*)a - *(int*)b);
}

float E(int x)
{
    float e = 1.0;
    int factorial = 1;
    for (int i = 1; i <= x; i++)
    {
        factorial *= i;       
        e += 1.0/factorial;
    }
    return e;
}

void Sort(int* array, unsigned long size) {
    qsort(array, size, sizeof(int), Compare);
}