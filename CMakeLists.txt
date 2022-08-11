cmake_minimum_required(VERSION 3.22)
project(MyVerse)

set(CMAKE_CXX_STANDARD 20)

if(NOT WIN32)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -march=native")
endif()

set(FETCHCONTENT_UPDATES_DISCONNECTED ON)

include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/add_glad.cmake)
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/add_glfw.cmake)
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/add_glm.cmake)
#include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/add_grpc.cmake)
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/add_json.cmake)
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/add_obj_loader.cmake)
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/add_stb.cmake)
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/add_uuid.cmake)

add_subdirectory(src)
include_directories(src)
