project(Thread-waiting-on-Condition)
set(CMAKE_CXX_STANDARD 11)
add_executable(condition-thread th_no_class.cpp)
target_link_libraries(condition-thread pthread)


