include(FetchContent)

FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG        release-1.11.0
)

FetchContent_MakeAvailable(googletest)
add_library(GTest::GTest INTERFACE IMPORTED)
target_link_libraries(GTest::GTest INTERFACE gtest_main)


set(CMAKE_CXX_STANDARD 17)

add_executable(lab2_test lab2_test.cpp ../lab4/src/parent.cpp ../lab4/include/parent.h
        ../lab4/src/errorlib.cpp ../lab4/include/errorlib.h)

target_link_libraries(lab2_test PRIVATE GTest::GTest)
target_include_directories(lab2_test PRIVATE ../lab4/include)

add_test(lab2_test lab2_test)

add_executable(lab51_test lab51_test.cpp ../lab5/include/lab5.h ../lab5/src/lib1.c )

target_link_libraries(lab51_test PRIVATE GTest::GTest)
target_include_directories(lab51_test PRIVATE ../lab5/include)

add_test(lab51_test lab51_test)

add_executable(lab52_test lab52_test.cpp ../lab5/include/lab5.h ../lab5/src/lib2.c )

target_link_libraries(lab52_test PRIVATE GTest::GTest)
target_include_directories(lab52_test PRIVATE ../lab5/include)

add_test(lab52_test lab52_test)

add_executable(lab3_test lab3_test.cpp ../lab3/include/lab3.h ../lab3/src/lab3.cpp)

target_link_libraries(lab3_test PRIVATE GTest::GTest)
target_include_directories(lab3_test PRIVATE ../lab3/include)

add_test(lab3_test lab3_test)

add_executable(lab4_test lab4_test.cpp ../lab4/src/parent.cpp ../lab4/include/parent.h
        ../lab4/src/errorlib.cpp ../lab4/include/errorlib.h)
target_link_libraries(lab4_test PRIVATE GTest::GTest)
target_include_directories(lab4_test PRIVATE ../lab4/include)
add_test(lab4_test lab4_test)

