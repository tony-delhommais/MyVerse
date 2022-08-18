include(FetchContent)

FetchContent_Declare(glm
	GIT_REPOSITORY https://github.com/g-truc/glm.git
	GIT_TAG 0.9.9.8
)

set(FETCHCONTENT_QUIET OFF)
FetchContent_MakeAvailable(glm)
include_directories(${glm_SOURCE_DIR}/glm)
