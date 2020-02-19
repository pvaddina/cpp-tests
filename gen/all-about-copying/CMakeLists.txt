project(All-about-copying)

include_directories("../../inc")

add_executable(all_about_copying copy.cpp)

add_test(NAME "All-about-Copying"
        COMMAND all_about_copying)
