include(FetchContent)

FetchContent_Declare(stb
	GIT_REPOSITORY https://github.com/nothings/stb.git
	GIT_TAG master
)

set(FETCHCONTENT_QUIET OFF)
FetchContent_MakeAvailable(stb)
include_directories(${stb_SOURCE_DIR})

#FetchContent_GetProperties(stb)
#if(NOT stb_POPULATED)
#	message(STATUS "Populate Stb")
#	FetchContent_Populate(stb)
#	include_directories(${stb_SOURCE_DIR})
#else()
#	message(STATUS "Stb is already populated")
#endif()
