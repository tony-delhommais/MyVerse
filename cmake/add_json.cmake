include(FetchContent)

FetchContent_Declare(json
	GIT_REPOSITORY https://github.com/nlohmann/json.git
	GIT_TAG v3.11.2
)

set(JSON_BuildTests OFF CACHE BOOL "")
set(JSON_Install ON CACHE BOOL "")
set(JSON_MultipleHeaders OFF CACHE BOOL "")

set(FETCHCONTENT_QUIET OFF)
FetchContent_MakeAvailable(json)
include_directories(${json_SOURCE_DIR}/include)

#FetchContent_GetProperties(json)
#if(NOT json_POPULATED)
#	message(STATUS "Populate Nlohmann Json")
#	set(JSON_BuildTests OFF CACHE BOOL "")
#	set(JSON_Install ON CACHE BOOL "")
#	set(JSON_MultipleHeaders OFF CACHE BOOL "")
#	FetchContent_Populate(json)
#	include_directories(${json_SOURCE_DIR}/include)
#else()
#	message(STATUS "Nlohmann Json is already populated")
#endif()
