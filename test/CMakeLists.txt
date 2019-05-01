cmake_minimum_required(VERSION 3.13)

set(PROJECT_TEST_NAME ${PROJECT_NAME}Tests)

add_executable(${PROJECT_TEST_NAME} main.cpp ParserTests.cpp)
    
target_link_libraries(${PROJECT_TEST_NAME} gtest ${PROJECT_LIB_NAME})
    
add_test(NAME ${PROJECT_TEST_NAME} COMMAND ${PROJECT_TEST_NAME})