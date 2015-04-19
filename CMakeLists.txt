cmake_minimum_required(VERSION 2.6)

project(2048)
ADD_DEFINITIONS(-g -Wall)


include_directories(${2048_SOURCE_DIR}/src/grid/ 
	${2048_SOURCE_DIR}/src/2048/ 
	${2048_SOURCE_DIR}/src/strategy/)

add_definitions(-std=c99)

enable_testing()  

add_subdirectory(src)
