cmake_minimum_required(VERSION 3.14)

project(university-db)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(FLAGS  -Wall -Wextra -pedantic  -Werror)

# GoogleTest
########
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)
##########


set(SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/inc)
set(TEST_DIR ${CMAKE_CURRENT_SOURCE_DIR}/test)


file(GLOB_RECURSE SOURCES ${SOURCE_DIR}/*.cpp)
include_directories(${INCLUDE_DIR})
add_executable(${PROJECT_NAME} ${SOURCES})


# Creating test
enable_testing()
add_executable(${PROJECT_NAME}-test ${TEST_DIR}/test.cpp)
target_link_libraries( ${PROJECT_NAME}-test
                       GTest::gtest_main)


include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME}-test )
