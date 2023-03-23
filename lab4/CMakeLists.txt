add_executable(lab4 
		main.cpp
		src/parent.cpp
		src/errorlib.cpp)

target_include_directories(lab4 PRIVATE include)

target_link_libraries(lab4 PRIVATE Threads::Threads)
