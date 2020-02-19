project(Message-Properties-with-Flags)
set(CMAKE_CXX_STANDARD 11)

add_executable(ppack ppack.cpp)

add_test(NAME Parameter-pack-functions
      COMMAND ppack)
