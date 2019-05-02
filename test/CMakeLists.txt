cmake_minimum_required(VERSION 3.13)

set(PROJECT_TEST_NAME ${PROJECT_NAME}Tests)

add_executable(${PROJECT_TEST_NAME} main.cpp ParserTests.cpp AssemblerEngineTests.cpp)
    
target_link_libraries(${PROJECT_TEST_NAME} gtest ${PROJECT_LIB_NAME})
    
# Add tests and pass test-files directory path as an argument to gtest
# Note: Testing directly from the test-explorer in VS Studio 2017 (tested with version 15.9.11) does not seem
#       to take the argument into account, use ctest instead.  
add_test(NAME ${PROJECT_TEST_NAME} COMMAND ${PROJECT_TEST_NAME} "${CMAKE_CURRENT_LIST_DIR}/test-files/")