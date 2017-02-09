CMAKE_MINIMUM_REQUIRED(VERSION 3.4)

if(UNIX)
	#SET THE DESIRED COMPILER
	set(CMAKE_C_COMPILER "/usr/bin/gcc")
	set(CMAKE_CXX_COMPILER "/usr/bin/g++")
	
	#SET DEBUG COMPILATION FLAGS
	set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -std=c++11 -m32 -Wall -Wextra -ansi -pedantic")

	#SET RELEASE COMPILATION FLAGS
	set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -std=c++11 -Wall -Wextra -ansi -pedantic")
endif()

# BOOST
set(BOOST_PATH CACHE PATH "Path to Boost folder")
include_directories(${BOOST_PATH})

#ABOUT THE PROJECT
project(sudoku_solver)
set(VERSION_MAJOR "1")
set(VERSION_MINOR "0")
set(VERSION_PATCH "0")
set(VERSION "${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}")

#SET WHERE THE FILES WILL BE CREATED
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/archives)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/libs)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/apps) 

message("\n")
message("---- Project ${PROJECT_NAME} ----")
message("Version		= ${VERSION}")
message("C compiler 	= ${CMAKE_C_COMPILER}")
message("C++ compiler	= ${CMAKE_CXX_COMPILER}")
message("Debug flags	= ${CMAKE_CXX_FLAGS_DEBUG}")
message("Release flags	= ${CMAKE_CXX_FLAGS_RELEASE}")
message("\n")

#ADD SUBDIRECTORIES
add_subdirectory(UtilsLib)
add_subdirectory(UtilsLibTest)
add_subdirectory(ElementLib)
add_subdirectory(ElementLibTest)
