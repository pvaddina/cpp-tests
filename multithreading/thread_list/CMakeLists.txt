project(Multiple-Threads-in-Vector-Example)
set(CMAKE_CXX_STANDARD 11)
add_executable(thread-in-vec thread_vec.cpp)
if (UNIX)
    target_link_libraries(thread-in-vec pthread)
endif()


