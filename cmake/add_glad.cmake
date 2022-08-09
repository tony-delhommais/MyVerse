include(FetchContent)

FetchContent_Declare(glad
	GIT_REPOSITORY https://github.com/Dav1dde/glad.git
	GIT_TAG v0.1.36
)

set(GLAD_PROFILE "core" CACHE STRING "OpenGL profile")
set(GLAD_API "gl=3.2" CACHE STRING "API type/version pairs, like \"gl=3.2,gles=\", no version means latest")
set(GLAD_GENERATOR "c" CACHE STRING "Language to generate the binding for")

set(FETCHCONTENT_QUIET OFF)
FetchContent_MakeAvailable(glad)
include_directories(${glad_BINARY_DIR}/include)

#FetchContent_GetProperties(glad)
#if(NOT glad_POPULATED)
#	message(STATUS "Populate GLAD")
#	FetchContent_Populate(glad)
#	set(GLAD_PROFILE "core" CACHE STRING "OpenGL profile")
#	set(GLAD_API "gl=3.2" CACHE STRING "API type/version pairs, like \"gl=3.2,gles=\", no version means latest")
#	set(GLAD_GENERATOR "c" CACHE STRING "Language to generate the binding for")
#	include_directories(${glad_BINARY_DIR}/include)
#	add_subdirectory(${glad_SOURCE_DIR} ${glad_BINARY_DIR})
#else()
#	message(STATUS "GLAD is already populated")
#endif()
