project(Simple-Future-Demo)
set(CMAKE_CXX_STANDARD 11)
add_executable(simple-future future.cpp)
if (UNIX)
    target_link_libraries(simple-future pthread)
endif()


