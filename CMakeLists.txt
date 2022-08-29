cmake_minimum_required(VERSION 3.16.3)  # CMake version check
project(Json_Library)               # Create project "simple_example"

include(FetchContent)

FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG release-1.12.1
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(googletest)

enable_testing()

set(CMAKE_CXX_STANDARD 17)            # Enable c++14 standard
set(CMAKE_CXX_STANDARD_REQUIRED True) 
set(CMAKE_BUILD_TYPE Debug)

include_directories(include)
#link_directories(include)
#target_link_libraries(Json_Library include)

# Add main.cpp file of project root directory as source file
set(SOURCE_FILES src/main.cpp src/json.cpp src/tests.cpp)

# Add executable target with source files listed in SOURCE_FILES variable
add_executable(json_lib src/main.cpp src/json.cpp)
add_executable(json_test src/json.cpp src/tests.cpp)


target_link_libraries(
        json_test
        GTest::gtest_main
)

include(GoogleTest)

gtest_discover_tests(json_test)