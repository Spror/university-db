cmake_minimum_required(VERSION 3.10)

project(university-db)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(FLAGS  -Wall -Wextra -pedantic  -Werror)


set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/inc)

file(GLOB_RECURSE SOURCES ${SOURCE_DIR}/*.cpp)
include_directories(${INCLUDE_DIR})

add_executable(${PROJECT_NAME} ${SOURCES})
