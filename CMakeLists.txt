CMAKE_MINIMUM_REQUIRED(VERSION 3.0)

set(CMAKE_C_COMPILER "/usr/bin/gcc")
set(CMAKE_CXX_COMPILER "/usr/bin/g++")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -Wextra -ansi -pedantic")

include_directories(SYSTEM $ENV{BOOST_INCLUDE})

project(sudoku_solver)
set(VERSION_MAJOR "0")
set(VERSION_MINOR "0")
set(VERSION_PATCH "0")
set(VERSION "${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}")

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/archives)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/libs)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/apps) 

message("\n")
message("---- Project ${PROJECT_NAME} ----")
message("Version		= ${VERSION}")
message("C compiler 	= ${CMAKE_C_COMPILER}")
message("C++ compiler	= ${CMAKE_CXX_COMPILER}")
message("Compiler flags	= ${CMAKE_CXX_FLAGS}")
message("\n")

#ADD SUBDIRECTORIES
add_subdirectory(UtilsLib)
add_subdirectory(UtilsLibTest)
add_subdirectory(ElementLib)
add_subdirectory(ElementLibTest)
