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

add_executable(fsx "fsx.c")
add_custom_target(pytest
    COMMAND ${PYTHON_PATH} -m pytest -c ${PROJECT_SOURCE_DIR}/unreliablefs/tests/pytest.ini ${PROJECT_SOURCE_DIR}/unreliablefs/tests/
    WORKING_DIRECTORY ${PROJECT_SOURCE_DIR}
    COMMENT "Run regression test suite")
