project(Simple-Promise-Demo)
set(CMAKE_CXX_STANDARD 17)
add_executable(simple_promise promise.cpp)
if (UNIX)
    target_link_libraries(simple_promise pthread)
endif()

add_test(NAME promise-use-cases
      COMMAND simple_promise)



