cmake_minimum_required(VERSION 3.4)

set(APP_NAME AppLauncher)
set(PROJECT_NAME Triangle)
set(CMAKE_CXX_STANDARD 17)
set(DEFAULT_CONFIG debug)

project(${PROJECT_NAME})

option(BUILD_TESTS "Building tests" OFF)

if(NOT DEFINED CONFIG OR CONFIG STREQUAL "")
    set(CONFIG ${DEFAULT_CONFIG})
endif()

if(NOT CONFIG STREQUAL release AND NOT CONFIG STREQUAL debug)
    message(WARNING "Incorrect configuration type : ${CONFIG}, ${DEFAULT_CONFIG} will be used")
    set(CONFIG ${DEFAULT_CONFIG})
endif()

message(STATUS "Project configuration : ${CONFIG}")

if(CONFIG STREQUAL debug)
    add_definitions(-D_DEBUG)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wpedantic -g")
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Debug/Bin)
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Debug/Lib)
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Debug/Lib)
endif()

if(CONFIG STREQUAL release)
    add_definitions(-D_RELEASE)
    set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Release/Bin)
    set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Release/Lib)
    set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/Release/Lib)
endif()

set(SOURCES_DIR Sources)
set(HEADERS_DIR Headers)
set(TESTS_DIR   Tests)
set(LIBS_DIR    Libs)

set(SOURCES
    ${SOURCES_DIR}/Main.cpp
)

link_directories(${LIBS_DIR})

add_executable(${APP_NAME} ${SOURCES})

target_include_directories(${APP_NAME} PUBLIC ${HEADERS_DIR})

target_link_libraries(${APP_NAME} glfw3
                                  "-framework Cocoa"
                                  "-framework IOKit"
                                  "-framework CoreFoundation")

if(BUILD_TESTS)
    message(STATUS "Add tests")
    add_subdirectory(${TESTS_DIR})
endif()
