project(All-about-copying)

add_executable(all_about_copying copy.cpp copy_elision.h copyconstructor_inheritence.h struct_init.h)

add_test(NAME "All-about-Copying"
        COMMAND all_about_copying)
