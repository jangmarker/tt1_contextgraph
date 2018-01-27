cmake_minimum_required(VERSION 3.9)
project(tt1_contextgraph)

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/CMakeModules)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
if (MSVC_VERSION GREATER_EQUAL "1900")
    include(CheckCXXCompilerFlag)
    CHECK_CXX_COMPILER_FLAG("/std:c++latest" _cpp_latest_flag_supported)
    if (_cpp_latest_flag_supported)
        add_compile_options("/std:c++latest")
    endif()

    add_compile_options("/utf-8")
endif()

if (DEFINED ENV{TRAVIS})
    include(CodeCoverage)
    setup_target_for_coverage(${PROJECT_NAME}_coverage tests coverage)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pedantic -pthread -g -O0 -fprofile-arcs -ftest-coverage")
    set(CMAKE_BUILD_TYPE "DEBUG")
endif()

set(SOURCE_FILES database.h database.cpp file_access.cpp file_access.h vector.cpp vector.h search.cpp search.h)
add_library(libtt1_contextgraph ${SOURCE_FILES})

add_executable(tt1_contextgraph main.cpp 3rdparty/CLI11.hpp)
target_link_libraries(tt1_contextgraph libtt1_contextgraph)

if(CMAKE_COMPILER_IS_GNUCXX)
    target_link_libraries(tt1_contextgraph -lstdc++fs)
endif()

set(TEST_FILES 3rdparty/catch.hpp helper_tst.h helper_tst.cpp)
add_library(libtt1_contextgraph_test ${TEST_FILES} main_tst.cpp)

function(create_test NAME)
    add_executable(tst_${NAME} tst_${NAME}.cpp)
    target_link_libraries(tst_${NAME} libtt1_contextgraph_test libtt1_contextgraph)
    if(CMAKE_COMPILER_IS_GNUCXX)
        target_link_libraries(tst_${NAME} -lstdc++fs)
    endif()
    add_test(${NAME} tst_${NAME} --reporter=junit -o tst_${NAME}-junit.xml)
endfunction(create_test)

enable_testing()
create_test(file_access)
create_test(database)
create_test(search)
# NOTE don't forget to add command to .appveyor.yml
