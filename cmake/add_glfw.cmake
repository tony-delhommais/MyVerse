include(FetchContent)

FetchContent_Declare(glfw
	GIT_REPOSITORY https://github.com/glfw/glfw.git
	GIT_TAG 3.3.8
)

FetchContent_GetProperties(glfw)
if(NOT glfw_POPULATED)
	message(STATUS "Populate GLFW")
	FetchContent_Populate(glfw)
	include_directories(${glfw_SOURCE_DIR}/include)
	add_subdirectory(${glfw_SOURCE_DIR} ${glfw_BINARY_DIR})
else()
	message(STATUS "GLFW is already populated")
endif()
