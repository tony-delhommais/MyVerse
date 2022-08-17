include(FetchContent)

FetchContent_Declare(glm
	GIT_REPOSITORY https://github.com/g-truc/glm.git
	GIT_TAG 0.9.9.8
)

set(FETCHCONTENT_QUIET OFF)
FetchContent_MakeAvailable(glm)
include_directories(${glm_SOURCE_DIR}/glm)

#FetchContent_GetProperties(glm)
#if(NOT glm_POPULATED)
#	message(STATUS "Populate GLM")
#	FetchContent_Populate(glm)
#	include_directories(${glm_SOURCE_DIR}/glm)
#else()
#	message(STATUS "GLM is already populated")
#endif()
