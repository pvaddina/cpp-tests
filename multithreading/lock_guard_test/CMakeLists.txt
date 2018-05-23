project(LockGuard_Tests)
set(CMAKE_CXX_STANDARD 11)
add_executable(lock-guard lockguard.cpp)
if (UNIX)
    target_link_libraries(lock-guard pthread)
endif()


