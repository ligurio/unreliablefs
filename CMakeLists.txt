cmake_minimum_required (VERSION 3.10.2)

include(CheckFunctionExists)

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

check_function_exists(utimensat HAVE_UTIMENSAT)
if (${HAVE_UTIMENSAT})
    target_compile_definitions(${PROJECT_NAME} PUBLIC HAVE_UTIMENSAT)
endif ()

enable_testing()
add_test(NAME pytest COMMAND pytest -c ${PROJECT_SOURCE_DIR}/tests/pytest.ini ${PROJECT_SOURCE_DIR}/tests/
         WORKING_DIRECTORY ${PROJECT_SOURCE_DIR})

set(MANUAL_PAGES "unreliablefs.1")
add_custom_target(check DEPENDS check-mandoc)
add_custom_target(check-mandoc DEPENDS ${MANUAL_PAGES})
add_custom_command(TARGET check-mandoc
                   COMMAND mandoc -T lint -W warning,stop ${MANUAL_PAGES}
                   WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
                   COMMENT "Run mandoc static analysis")
