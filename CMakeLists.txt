cmake_minimum_required(VERSION 3.14)

project(JSON_PROJECT)

include(FetchContent)

FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG release-1.12.1
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(googletest)

enable_testing()

include_directories(include)

set(CXX_STANDARD_REQUIRED 17)

add_executable(jsonProject src/JsonProject.cpp src/main.cpp)

add_executable(jsonTest src/JsonProject.cpp tests/Json_Tests.cpp)

target_link_libraries(
        jsonTest
        GTest::gtest_main
)

include(GoogleTest)

gtest_discover_tests(jsonTest)