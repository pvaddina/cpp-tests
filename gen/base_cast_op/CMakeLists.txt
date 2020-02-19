project(Cast-Operation-on-Object-to-Access-Base-type)

add_executable(castonbase cast.cpp)

add_test(NAME Cast-Operation
        COMMAND castonbase)
