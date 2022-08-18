include(FetchContent)

FetchContent_Declare(grpc
	GIT_REPOSITORY https://github.com/grpc/grpc.git
	GIT_TAG v1.45.2
)

set(FETCHCONTENT_QUIET OFF)
set(ABSL_PROPAGATE_CXX_STD ON)
FetchContent_MakeAvailable(grpc)
include_directories(${grpc_SOURCE_DIR}/include)
