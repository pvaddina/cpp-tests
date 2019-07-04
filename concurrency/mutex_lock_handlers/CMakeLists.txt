cmake_minimum_required(VERSION 3.5.1)
 
project(LockGuard_Tests)
set(CMAKE_CXX_STANDARD 11)

# Note that the following examples are only supposed to be used with GNU
# Visual studio compiler does not support RVO/NRVO.
# And because the code uses a function to initialize the lock objects, 
# in case of visual studio the object is created and a copy of it is 
# returned. And since the copy of the lock handlers are explicitly disabled
# you would get a compiler error when compiling in windows.
if ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
  add_executable(lockguard lockhandler.cpp)
  add_executable(uniquelock_no_defer lockhandler.cpp)
  add_executable(uniquelock_deferred lockhandler.cpp)

  if (UNIX)
    target_link_libraries(lockguard pthread)
    target_link_libraries(uniquelock_no_defer pthread)
    target_link_libraries(uniquelock_deferred pthread)
  endif()

  set_target_properties(lockguard PROPERTIES COMPILE_DEFINITIONS "LOCK_GUARD_ONLY")
  set_target_properties(uniquelock_no_defer PROPERTIES COMPILE_DEFINITIONS "UNIQUE_LOCK_WITHOUT_DEFERRING")
  set_target_properties(uniquelock_deferred PROPERTIES COMPILE_DEFINITIONS "UNIQUE_LOCK_WITH_DEFERRING")
endif()

