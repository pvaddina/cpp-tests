project(StdList_Project)

set(CMAKE_CXX_STANDARD 17)

add_executable(stdlist list.cpp)

add_test(NAME StdList-use-cases
      COMMAND stdlist)

