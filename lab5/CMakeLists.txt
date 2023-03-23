add_library(First SHARED src/lib1.c)
add_library(Second SHARED src/lib2.c)

target_include_directories(First PRIVATE include)
target_include_directories(Second PRIVATE include)

add_executable(prog1L1 src/prog1.c include/lab5.h)
add_executable(prog1L2 src/prog1.c include/lab5.h)

target_include_directories(prog1L1 PRIVATE include)
target_include_directories(prog1L2 PRIVATE include)

target_link_libraries(prog1L1 PRIVATE First)
target_link_libraries(prog1L2 PRIVATE Second)

add_executable(prog2 src/prog2.c)

target_link_libraries(prog2 PRIVATE ${CMAKE_DL_LIBS})
target_include_directories(prog2 PRIVATE include)
