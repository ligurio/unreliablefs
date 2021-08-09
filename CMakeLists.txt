cmake_minimum_required (VERSION 3.10.2)

include(CheckFunctionExists)

project (unreliablefs
         DESCRIPTION "A FUSE-based fault injection filesystem.")

if(${CMAKE_VERSION} VERSION_GREATER "3.12.0")
    find_package(Python3 COMPONENTS Interpreter)
    find_package(Python COMPONENTS Interpreter)
endif()

set(PYTHON_PATH "/usr/bin/python3.6")
if(${Python3_FOUND})
    set(PYTHON_PATH ${Python3_EXECUTABLE})
elseif(${Python_FOUND})
    set(PYTHON_PATH ${Python_EXECUTABLE})
endif()

set(UNRELIABLEFS_SRC conf.c
		unreliablefs.c
		unreliablefs_errinj.c
		unreliablefs_ops.c)

set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake;${CMAKE_MODULE_PATH}")
find_package(FUSE 2.9 REQUIRED)

add_definitions(${FUSE_DEFINITIONS})
add_executable(${PROJECT_NAME} ${UNRELIABLEFS_SRC})
target_include_directories(${PROJECT_NAME} PRIVATE ${FUSE_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} ${FUSE_LIBRARIES})

target_compile_options(${PROJECT_NAME} PUBLIC -D_FILE_OFFSET_BITS=64 -Wall -Wextra -Wno-unused-parameter)
target_compile_options(${PROJECT_NAME} PUBLIC $<$<COMPILE_LANGUAGE:CXX>:-std=c++11 -D_FILE_OFFSET_BITS=64>)

check_function_exists(fallocate HAVE_FALLOCATE)
check_function_exists(fallocate HAVE_FLOCK)
check_function_exists(utimensat HAVE_UTIMENSAT)
check_function_exists(setxattr HAVE_XATTR)
if (${HAVE_FALLOCATE})
    target_compile_definitions(${PROJECT_NAME} PUBLIC HAVE_FALLOCATE)
endif ()
if (${HAVE_FLOCK})
    target_compile_definitions(${PROJECT_NAME} PUBLIC HAVE_FLOCK)
endif ()
if (${HAVE_UTIMENSAT})
    target_compile_definitions(${PROJECT_NAME} PUBLIC HAVE_UTIMENSAT)
endif ()
if (${HAVE_XATTR})
    target_compile_definitions(${PROJECT_NAME} PUBLIC HAVE_XATTR)
endif ()

option(ENABLE_ASAN "Enable AddressSanitizer, a fast memory error detector
                    based on compiler instrumentation" OFF)
if(ENABLE_ASAN)
    target_compile_options(${PROJECT_NAME} PUBLIC -fsanitize=address)
    target_link_options(${PROJECT_NAME} PUBLIC -fsanitize=address)
endif()

option(ENABLE_UBSAN "Enable UBSanitizer, undefined behaviour
                     detector based on compiler instrumentation" OFF)
if(ENABLE_UBSAN)
    target_compile_options(${PROJECT_NAME} PUBLIC -fsanitize=undefined)
    target_link_options(${PROJECT_NAME} PUBLIC -fsanitize=undefined)
endif()

add_subdirectory(tests)
add_custom_target(pytest
    COMMAND ${PYTHON_PATH} -m pytest -c ${PROJECT_SOURCE_DIR}/tests/pytest.ini ${PROJECT_SOURCE_DIR}/tests/
    WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
    COMMENT "Run regression test suite")

set(MANUAL_PAGES "unreliablefs.1;unreliablefs.conf.5")
add_custom_target(check DEPENDS check-mandoc check-rockspec)
add_custom_target(check-mandoc DEPENDS ${MANUAL_PAGES})
add_custom_command(TARGET check-mandoc
                   COMMAND mandoc -T lint -W warning,stop ${MANUAL_PAGES}
                   WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
                   COMMENT "Run mandoc static analysis")

set(ROCKSPEC "unreliablefs-scm-1.rockspec")
add_custom_target(check-rockspec DEPENDS ${ROCKSPEC})
add_custom_command(TARGET check-rockspec
                   COMMAND luarocks --local build ${PROJECT_SOURCE_DIR}/${ROCKSPEC}
                   WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
                   COMMENT "Build Lua rockspec")

install(TARGETS unreliablefs DESTINATION ${CMAKE_INSTALL_PREFIX}/bin)
install(FILES "unreliablefs.1" DESTINATION ${CMAKE_INSTALL_PREFIX}/share/man/man1)
install(FILES "unreliablefs.conf.5" DESTINATION ${CMAKE_INSTALL_PREFIX}/share/man/man5)
