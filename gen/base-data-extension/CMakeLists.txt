project(Simple-Base-Class-Extension-With-Copy-Pitfall)
add_executable(base_extension base_extension.cpp)

add_test(NAME Base-data-extension
        COMMAND base_extension)

