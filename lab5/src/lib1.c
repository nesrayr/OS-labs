#include "lab5.h"

float power(int x)
{
    float result = 1;
    for (int i = 1; i <= x; i++){
        result *= (1+1.0/x);
    }
    return result;
}
float E(int x)
{
    return power(x);
}

void Sort(int* array, unsigned long size) {

    for (unsigned long i = 0; i < size; ++i) {
        for (unsigned long j = 0; j < size - 1; ++j) {
            if (array[j] > array[j + 1]) 
            {
                int temp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = temp;
            }
        }
    }
}