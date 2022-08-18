include(FetchContent)

FetchContent_Declare(obj_loader
	GIT_REPOSITORY https://github.com/Bly7/OBJ-Loader.git
	PATCH_COMMAND git apply ${CMAKE_CURRENT_SOURCE_DIR}/cmake/patches/OBJ-Loader.patch
)

set(FETCHCONTENT_QUIET OFF)
FetchContent_MakeAvailable(obj_loader)
include_directories(${obj_loader_SOURCE_DIR}/Source)
