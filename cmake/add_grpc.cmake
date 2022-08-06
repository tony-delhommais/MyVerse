include(FetchContent)

FetchContent_Declare(grpc
	GIT_REPOSITORY https://github.com/grpc/grpc.git
	GIT_TAG v1.45.2
)

set(FETCHCONTENT_QUIET OFF)
FetchContent_MakeAvailable(grpc)

#FetchContent_GetProperties(grpc)
#if(NOT grpc_POPULATED)
#	message(STATUS "Populate gRPC")
#	FetchContent_Populate(grpc)
#	set(gRPC_BUILD_CSHARP_EXT OFF CACHE BOOL "")
#	include_directories(${grpc_SOURCE_DIR}/include)
#	add_subdirectory(${grpc_SOURCE_DIR} ${grpc_BINARY_DIR})
#else()
#	message(STATUS "gRPC is already populated")
#endif()