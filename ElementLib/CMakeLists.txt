project(ElementLib)

#INCLUDE DIRECTORIES
include_directories(${CMAKE_SOURCE_DIR}/${PROJECT_NAME}/include)
include_directories(${CMAKE_SOURCE_DIR}/UtilsLib/include)

#LINK THE DIRECTORIES

#SEARCH FOR .CPP AND .H FILES
file(GLOB ${PROJECT_NAME}_headers ${CMAKE_SOURCE_DIR}/${PROJECT_NAME}/include/*.h)
file(GLOB ${PROJECT_NAME}_sources ${CMAKE_SOURCE_DIR}/${PROJECT_NAME}/source/*.cpp)

#ADD LIBRARY
add_library(${PROJECT_NAME} STATIC ${${PROJECT_NAME}_sources} ${${PROJECT_NAME}_headers})

#LINK LIBRARIES
#target_link_libraries(${PROJECT_NAME} UtilsLib)

#DEFINE OUTPUT LOCATION
install(
	TARGETS ${PROJECT_NAME}
	LIBRARY DESTINATION libs
	ARCHIVE DESTINATION archives
)