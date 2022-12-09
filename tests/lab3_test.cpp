#include <gtest/gtest.h>

#include <lab3.h>

#include <chrono>

namespace {
    std::vector<int> GenerateArray(int length) {
        std::srand(std::time(nullptr));
        std::vector<int> arr(length);
        for (int i = 0; i < length; i++){
            arr[i] = std::rand() % 100;
        }
        return arr;
    }
    auto ExpectEqCheck(std::vector<int>& v1, std::vector<int>& v2) {
        ASSERT_EQ(v1.size(), v2.size());
        for (long unsigned int i = 0; i < v1.size(); i++){
            EXPECT_EQ(v1[i], v2[i]);
        }
    }
}

TEST(ThirdLabTests, SingleThreadYieldsCorrectResults) {
    std::vector<int> arr1 = {99, 59, 19, 9, 1};
    std::sort(arr1, 1);
    std::vector<int> out1 = {1, 9, 19, 59, 99};
    ExpectEqCheck(arr1, out1);

    std::vector<int> arr2 = {1,2,3,4,5,6,7,8,9,10};
    std::sort(arr2, 1);
    std::vector<int> out2 = {1,2,3,4,5,6,7,8,9,10};
    ExpectEqCheck(arr2, out2);

    std::vector<int> arr3 = {5,38,79,85,2,1,3,2,99,13,11,17,85,62,4};
    std::sort(arr3, 1);
    std::vector<int> out3 = {1,2,2,3,4,5,11,13,17,38,62,79,85,85,99};
    ExpectEqCheck(arr3, out3);
}

TEST(ThirdLabTest, ThreadConfigurations) {
    auto performTestForGivenSize = [](int length, int maxThreadCount) {
        std::vector<int> arr = GenerateArray(length);
        std::vector<int> arr1 = arr;
        std::sort(arr1, 1);

        for(int i = 2; i < maxThreadCount; ++i) {
            std::sort(arr, i);
            ExpectEqCheck(arr, arr1);
        }
    };

    performTestForGivenSize(3, 10);
    performTestForGivenSize(10, 10);
    performTestForGivenSize(100, 15);
    performTestForGivenSize(3000, 4);
}

TEST(ThirdLabTest, PerfomanceTest) {
    auto getAvgTime = [](int threadCount) {
        std::vector<int> arr = GenerateArray(9000);

        constexpr int runsCount = 10;

        double avg = 0;

        for(int i = 0; i < runsCount; ++i) {
            auto begin = std::chrono::high_resolution_clock::now();
            std::sort(arr, threadCount);
            auto end = std::chrono::high_resolution_clock::now();
            avg += std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count();
        }

        return avg / runsCount;
    };

    auto singleThread = getAvgTime(1);
    auto multiThread = getAvgTime(4);

    std::cout << "Avg time for 1 thread: " << singleThread << '\n';
    std::cout << "Avg time for 4 threads: " << multiThread << '\n';

    EXPECT_GE(singleThread, multiThread);
}