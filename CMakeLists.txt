cmake_minimum_required(VERSION 3.12)

project(HackAssembler VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

option(BUILD_TESTS "Build the tests" OFF)

set(SOURCES src/AssemblerEngine.cpp 
            src/HackAssembler.cpp
            src/Code.cpp 
            src/Parser.cpp 
            src/SymbolTable.cpp
)

set(HEADERS include/AssemblerEngine.h
            include/HackAssembler.h 
            include/Code.h 
            include/Parser.h 
            include/SymbolTable.h
)

set(PROJECT_LIB_NAME ${PROJECT_NAME}Lib)

add_library(${PROJECT_LIB_NAME} STATIC ${SOURCES} ${HEADERS})

target_include_directories(${PROJECT_LIB_NAME} PUBLIC include)

add_executable(${PROJECT_NAME} src/main.cpp)

target_link_libraries(${PROJECT_NAME} ${PROJECT_LIB_NAME})

if("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
	target_link_libraries(${PROJECT_NAME} stdc++fs)
endif()

if (BUILD_TESTS)
    ## Source: https://github.com/google/googletest/blob/master/googletest/README.md#incorporating-into-an-existing-cmake-project
    # Download and unpack googletest at configure time
    set(INSTALL_GTEST OFF CACHE BOOL "Do not install gtest" FORCE)
    set(INSTALL_GMOCK OFF CACHE BOOL "Do not install gmock" FORCE)

    # Gmock is not used in this project
    set(BUILD_GMOCK OFF CACHE BOOL "Do not build gmock" FORCE)      

    configure_file(CMakeLists.txt.in googletest-download/CMakeLists.txt)
    execute_process(COMMAND ${CMAKE_COMMAND} -G "${CMAKE_GENERATOR}" .
            WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download)
    execute_process(COMMAND ${CMAKE_COMMAND} --build .
            WORKING_DIRECTORY ${CMAKE_BINARY_DIR}/googletest-download)

    # Prevent GoogleTest from overriding our compiler/linker options
    # when building with Visual Studio
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

    # Add googletest directly to our build. This adds
    # the following targets: gtest, gtest_main, gmock
    # and gmock_main
    add_subdirectory(${CMAKE_BINARY_DIR}/googletest-src
            ${CMAKE_BINARY_DIR}/googletest-build)

    enable_testing()

    add_subdirectory(test)
endif ()
