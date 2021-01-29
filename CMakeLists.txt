cmake_minimum_required (VERSION 3.10.2)
project (unreliablefs
         DESCRIPTION "A FUSE-based fault injection filesystem.")

set(UNRELIABLEFS_SRC unreliablefs.c
		unreliablefs_errinj.c
		unreliablefs_ops.c)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -D_FILE_OFFSET_BITS=64")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -D_FILE_OFFSET_BITS=64")

set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake;${CMAKE_MODULE_PATH}")
find_package(FUSE 2.9 REQUIRED)

add_definitions(${FUSE_DEFINITIONS})
add_executable(${PROJECT_NAME} ${UNRELIABLEFS_SRC})
target_include_directories(${PROJECT_NAME} PRIVATE ${FUSE_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${FUSE_LIBRARIES})

set(MANUAL_PAGES "unreliablefs.1")
add_custom_target(check DEPENDS check-mandoc)
add_custom_target(check-mandoc DEPENDS ${MANUAL_PAGES})
add_custom_command(TARGET check-mandoc
                   COMMAND mandoc -T lint -W warning,stop ${MANUAL_PAGES}
                   WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
                   COMMENT "Run mandoc static analysis")
