project(LockGuard_Tests)
set(CMAKE_CXX_STANDARD 11)
add_executable(lockhandler lockhandler.cpp)
if (UNIX)
    target_link_libraries(lockhandler pthread)
endif()


