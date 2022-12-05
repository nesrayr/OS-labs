#include "lab3.h"

#include <iostream>

int main() {
    int length, threadCount;
    std::cin >> length >> threadCount;
    std::vector<int> arr(length);

    for (int i = 0; i < length; i++) {
        std::cin >> arr[i];
    }

    MergeSortArr(arr, threadCount);

    std::cout << "result ";
    for (int i = 0; i < length; i++) {
        std::cout << arr[i] << ' ';
    }
}