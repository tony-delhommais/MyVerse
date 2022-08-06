include(FetchContent)

FetchContent_Declare(obj_loader
	GIT_REPOSITORY https://github.com/Bly7/OBJ-Loader.git
	PATCH_COMMAND git apply ${CMAKE_CURRENT_SOURCE_DIR}/cmake/patches/OBJ-Loader.patch
)

FetchContent_GetProperties(obj_loader)
if(NOT obj_loader_POPULATED)
	message(STATUS "Populate OBJ-Loader")
	FetchContent_Populate(obj_loader)
	include_directories(${obj_loader_SOURCE_DIR}/Source)
else()
	message(STATUS "OBJ-Loader is already populated")
endif()
