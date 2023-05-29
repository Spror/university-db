cmake_minimum_required(VERSION 3.14)

project(university-db)

set(CMAKE_CXX_STANDARD 20)
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


set(SRC 
            src/Database.cpp
            src/Student.cpp)



set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/inc)
include_directories(${INCLUDE_DIR})




add_library(${PROJECT_NAME}-lib STATIC ${SRC} )

add_executable(${PROJECT_NAME} src/main.cpp ${INC})
target_link_libraries(${PROJECT_NAME} ${PROJECT_NAME}-lib)


# Creating test
enable_testing()
add_executable(${PROJECT_NAME}-test test/test.cpp )
target_link_libraries( ${PROJECT_NAME}-test
                       GTest::gtest_main  ${PROJECT_NAME}-lib)


include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME}-test )
