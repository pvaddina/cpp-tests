project(Simple-Thread-Example)
set(CMAKE_CXX_STANDARD 11)
add_executable(simple-thread simple.cpp)
if (UNIX)
    target_link_libraries(simple-thread pthread)
endif()


