CMAKE_MINIMUM_REQUIRED(VERSION 3.0)

set(CMAKE_C_COMPILER "$ENV{CC}")
set(CMAKE_CXX_COMPILER "$ENV{CXX}")
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall -Wextra -ansi -pedantic")

project(sudoku_solver)
set(VERSION_MAJOR "1")
set(VERSION_MINOR "1")
set(VERSION_PATCH "0")
set(VERSION "${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}")

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin) 

find_package (HDF5 REQUIRED)
if (HDF5_FOUND)
	include_directories (SYSTEM ${HDF5_INCLUDE_DIR})
endif ()

macro (add_executable _target)
    _add_executable (${_target} ${ARGN})
    target_link_libraries (${_target} ${HDF5_LIBRARIES})
endmacro ()

macro (add_library _target)
    _add_library (${_target} ${ARGN})
    target_link_libraries (${_target} ${HDF5_LIBRARIES})
endmacro ()

enable_testing()

message("\n")
message("---- Project ${PROJECT_NAME} ----")
message("Version		= ${VERSION}")
message("C compiler 	= ${CMAKE_C_COMPILER}")
message("C++ compiler	= ${CMAKE_CXX_COMPILER}")
message("Compiler flags	= ${CMAKE_CXX_FLAGS}")
message("\n")

add_subdirectory(UtilsLib)
add_subdirectory(UtilsLibTest)
add_subdirectory(ElementLib)
add_subdirectory(ElementLibTest)
add_subdirectory(AppLib)
add_subdirectory(AppLibTest)
add_subdirectory(sudoku)
