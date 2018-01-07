project(ElementLib)

include_directories(${CMAKE_SOURCE_DIR}/${PROJECT_NAME}/include)
include_directories(${CMAKE_SOURCE_DIR}/UtilsLib/include)

file(GLOB ${PROJECT_NAME}_headers ${CMAKE_SOURCE_DIR}/${PROJECT_NAME}/include/*.h)
file(GLOB ${PROJECT_NAME}_sources ${CMAKE_SOURCE_DIR}/${PROJECT_NAME}/source/*.cpp)

add_library(${PROJECT_NAME} STATIC ${${PROJECT_NAME}_sources} ${${PROJECT_NAME}_headers})

target_link_libraries(${PROJECT_NAME} UtilsLib)
