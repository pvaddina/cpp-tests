project(All-about-dynamic-casting)

add_executable(all_about_dyn_casting main.cpp empty_derived_classes.h)

add_test(NAME "All-about-dyn-casting"
        COMMAND all_about_dyn_casting)
