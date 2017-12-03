project(Simple-Thread-Example)
set(CMAKE_CXX_STANDARD 11)
add_executable(simple-thread simple.cpp)
target_link_libraries(simple-thread pthread)


