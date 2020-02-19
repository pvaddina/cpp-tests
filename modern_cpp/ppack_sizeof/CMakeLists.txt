project(Sizeof-with-Variadic-Templates)
set(CMAKE_CXX_STANDARD 11)

add_executable(ppacksizeof test.cpp)

add_test(NAME Parameter-pack-sizeof-examples
      COMMAND ppacksizeof)
