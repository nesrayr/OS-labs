#include <gtest/gtest.h>
#include <vector>

extern "C" {
    #include <lab5.h>
}

auto ExpectEqCheck(int* arr, std::vector<int>& v) {
    for (long unsigned int i = 0; i < v.size(); i++){
        EXPECT_EQ(arr[i], v[i]);
    }
}

TEST(FiveLabTests, Translationfirst) { 

    const float E1 = 2.48832;
    const int X1 = 5;
    EXPECT_FLOAT_EQ(E(X1), E1);

    const float E2 = 2.66145;
    const int X2 = 23;
    EXPECT_FLOAT_EQ(E(X2), E2);

    const float E3 = 2.71557;
    const int X3 = 500;
    EXPECT_FLOAT_EQ(E(X3), E3);

    const float E4 = 2.718144;
    const int X4 = 9999;
    EXPECT_FLOAT_EQ(E(X4), E4);

    const float E5 = 2.0;
    const int X5 = 1;
    EXPECT_FLOAT_EQ(E(X5), E5);

}

TEST(FiveLabTests, SortOfArray) { 
    std::vector<int> v1 = {99, 59, 19, 9, 1};
    int* arr1 = &v1[0];
    const int LEN1 = 5;
    Sort(arr1, LEN1);
    std::vector<int> out1 = {1, 9, 19, 59, 99};
    ExpectEqCheck(arr1, out1);

    std::vector<int> v2 = {1,2,3,4,5,6,7,8,9,10};
    int* arr2 = &v2[0];
    const int LEN2 = 10;
    Sort(arr2, LEN2);
    std::vector<int> out2 = {1,2,3,4,5,6,7,8,9,10};
    ExpectEqCheck(arr2, out2);

    std::vector<int> v3 = {5,38,79,85,2,1,3,2,99,13,11,17,85,62,4};
    int* arr3 = &v3[0];
    const int LEN3 = 15;
    Sort(arr3, LEN3);
    std::vector<int> out3 = {1,2,2,3,4,5,11,13,17,38,62,79,85,85,99};
    ExpectEqCheck(arr3, out3);;
}