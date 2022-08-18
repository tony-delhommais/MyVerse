include(FetchContent)

FetchContent_Declare(glfw
	GIT_REPOSITORY https://github.com/glfw/glfw.git
	GIT_TAG 3.3.8
)

set(FETCHCONTENT_QUIET OFF)
FetchContent_MakeAvailable(glfw)
include_directories(${glfw_SOURCE_DIR}/include)
