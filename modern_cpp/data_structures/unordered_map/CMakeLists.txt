project(UnorderedMap_Project)

set(CMAKE_CXX_STANDARD 17)

add_executable(unordered_map test.cpp)

add_test(NAME UnorderedMapTest
      COMMAND unordered_map)
