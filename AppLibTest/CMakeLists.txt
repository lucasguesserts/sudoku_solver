project(AppLibTest)

include_directories(${CMAKE_SOURCE_DIR}/UtilsLib/include)
include_directories(${CMAKE_SOURCE_DIR}/ElementLib/include)
include_directories(${CMAKE_SOURCE_DIR}/AppLib/include)

file(GLOB ${PROJECT_NAME}_sources ${CMAKE_SOURCE_DIR}/${PROJECT_NAME}/source/*.cpp)

add_executable(${PROJECT_NAME} ${${PROJECT_NAME}_sources})

target_link_libraries(${PROJECT_NAME} UtilsLib)
target_link_libraries(${PROJECT_NAME} ElementLib)
target_link_libraries(${PROJECT_NAME} AppLib)
