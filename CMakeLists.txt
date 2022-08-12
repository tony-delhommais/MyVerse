cmake_minimum_required(VERSION 3.8)

project(MyVerse)

if(NOT WIN32)
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -march=native")
else()
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} /MP")
endif()

set(FETCHCONTENT_UPDATES_DISCONNECTED ON)

include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/add_grpc.cmake)
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/add_glad.cmake)
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/add_glfw.cmake)
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/add_glm.cmake)
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/add_json.cmake)
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/add_obj_loader.cmake)
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/add_stb.cmake)
include(${CMAKE_CURRENT_SOURCE_DIR}/cmake/add_uuid.cmake)

add_subdirectory(src)
