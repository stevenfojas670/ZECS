add_executable(Test Test.cpp)

target_link_libraries(Test PRIVATE ZECS)

add_test(NAME Test COMMAND Test)
