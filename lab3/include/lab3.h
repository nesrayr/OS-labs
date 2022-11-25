#ifndef OS_LABS_LAB3_H
#define OS_LABS_LAB3_H

#include <vector>

void MergeSortArr(std::vector<int> &arr, int threadCount);
void MergeSort(std::vector<int> &arr, int left, int right);
void Merge(std::vector<int> &arr, int left, int middle, int right);
void* ThreadMergeSort(void* arg);


#endif //OS_LABS_LAB3_H
