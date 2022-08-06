include(FetchContent)

FetchContent_Declare(uuid
	GIT_REPOSITORY https://github.com/crashoz/uuid_v4.git
	GIT_TAG v1.0.0
)

FetchContent_GetProperties(uuid)
if(NOT uuid_POPULATED)
	message(STATUS "Populate UUIDv4")
	FetchContent_Populate(uuid)
	include_directories(${uuid_SOURCE_DIR})
else()
	message(STATUS "UUIDv4 is already populated")
endif()
