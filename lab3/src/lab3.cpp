#include "lab3.h"
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <pthread.h>
#include <vector>

struct TArg {
    std::vector<int> &a;
    long int i;
    int numbersPerThread;
    int offset;
    int threadCount;
};

void MergeSortArr(std::vector<int> &array, int threadCount) {
    
    int numbersPerThread = array.size() / threadCount;
    int offset = array.size() % threadCount;

    if (threadCount > 1) {
        std::vector<pthread_t> threads(threadCount);
        std::vector<TArg> arglist;
        arglist.reserve(threadCount);

        for (long i = 0; i < threadCount; i ++) {

            arglist.push_back({array, i, numbersPerThread, offset, threadCount});
            int rc = pthread_create(&threads[i], NULL, ThreadMergeSort, &arglist[i]);
            if (rc) {
                std::cerr << "Thread create error";
            }
        }
        
        for(long i = 0; i < threadCount; i++) {
            pthread_join(threads[i], NULL);
        }
        int low = numbersPerThread;
        int high;
        for (int i = 1; i < threadCount; i++) {
            high = low + numbersPerThread - 1;
            if (i == (threadCount -1)) {
                high = array.size() - 1;
            } 
            Merge(array, 0, low - 1, high);
            low += numbersPerThread;
        }
    }
    else {
        MergeSort(array, 0, array.size()-1);
    }
}

void *ThreadMergeSort(void* arg) {
    TArg* argum = (TArg*)arg;
    int thread_id = (long)argum->i;
    int left = thread_id * (argum->numbersPerThread);
    int right = (thread_id + 1) * (argum->numbersPerThread) - 1;
    if (thread_id == argum->threadCount - 1) {
        right += argum->offset;
    }
    int middle = left + (right - left) / 2;
    if (left < right) {

        MergeSort(arr, left, middle);
        MergeSort(arr, middle + 1, right);
        Merge(argum->a, left, middle, right);

    }
    return NULL;
}

// merge sort 
void MergeSort(std::vector<int> &arr, int left, int right) {
    if (left < right) {
        int middle = left + (right - left) / 2;
        MergeSort(arr, left, middle);
        MergeSort(arr, middle + 1, right);
        Merge(arr, left, middle, right);
    }
}


void Merge(std::vector<int> &arr, int left, int middle, int right) {
    int i = 0;
    int j = 0;
    int k = 0;
    int left_length = middle - left + 1;
    int right_length = right - middle;
    std::vector<int> left_array(left_length);
    std::vector<int> right_array(right_length);
    
    for (int i = 0; i < left_length; i ++) {
        left_array[i] = arr[left + i];
    }
    
    for (int j = 0; j < right_length; j ++) {
        right_array[j] = arr[middle + 1 + j];
    }
    
    i = 0;
    j = 0;
    while (i < left_length && j < right_length) {
        if (left_array[i] <= right_array[j]) {
            arr[left + k] = left_array[i];
            i ++;
        } else {
            arr[left + k] = right_array[j];
            j ++;
        }
        k ++;
    }
    
    while (i < left_length) {
        arr[left + k] = left_array[i];
        k ++;
        i ++;
    }
    while (j < right_length) {
        arr[left + k] = right_array[j];
        k ++;
        j ++;
    }
}