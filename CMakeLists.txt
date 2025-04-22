cmake_minimum_required(VERSION 3.26)
project(kagebunshin)

set(CMAKE_CXX_STANDARD 23)

add_executable(kagebunshin
        src/main.cpp
        src/TextFinder.cpp
        src/TextFinder.h
        src/ThreadPool.cpp
        src/ThreadPool.h
        src/ConcurrentQueue.h
)

option(BUILD_COVERAGE "Enable coverage reporting" OFF)
if (BUILD_COVERAGE)
    set(CMAKE_CXX_FLAGS " ${CMAKE_CXX_FLAGS} --coverage")
endif ()

include(FetchContent)

FetchContent_Declare(
        LOGorithm
        GIT_REPOSITORY https://github.com/adrianovaladar/LOGorithm.git
        GIT_TAG 1.0
)
FetchContent_MakeAvailable(LOGorithm)
target_link_libraries(kagebunshin PRIVATE LOGorithm)

# Add tests - Only if BUILD_TESTS is enabled
option(BUILD_TESTS "Build tests" OFF)
if (BUILD_TESTS)
    add_subdirectory(tests)
endif ()
