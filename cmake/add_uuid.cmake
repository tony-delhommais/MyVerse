include(FetchContent)

FetchContent_Declare(uuid
	GIT_REPOSITORY https://github.com/crashoz/uuid_v4.git
	GIT_TAG v1.0.0
	PATCH_COMMAND git apply ${CMAKE_CURRENT_SOURCE_DIR}/cmake/patches/uuid.patch
)

set(FETCHCONTENT_QUIET OFF)
FetchContent_MakeAvailable(uuid)
include_directories(${uuid_SOURCE_DIR})
