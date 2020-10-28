project(All_about_Constness)

add_executable(all_about_const const.cpp const_objs.h gen_tests.h)

add_test(NAME "All-About-Consness"
        COMMAND const)

