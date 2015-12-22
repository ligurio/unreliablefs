cmake_minimum_required (VERSION 3.12.4)
project (unreliablefs
         DESCRIPTION "A FUSE-based fault injection filesystem.")

set(UNRELIABLEFS_SRC unreliablefs.c
		unreliablefs_errinj.c
		unreliablefs_ops.c)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -D_FILE_OFFSET_BITS=64")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -D_FILE_OFFSET_BITS=64")

set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake;${CMAKE_MODULE_PATH}")
find_package(FUSE 2.9 REQUIRED)

include_directories(${FUSE_INCLUDE_DIR})
add_executable(${PROJECT_NAME} ${UNRELIABLEFS_SRC})
target_link_libraries(${PROJECT_NAME} ${FUSE_LIBRARIES})
