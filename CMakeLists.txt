cmake_minimum_required(VERSION 3.26)
project(kagebunshin)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_FLAGS " ${CMAKE_CXX_FLAGS} --coverage")

add_executable(kagebunshin
        src/main.cpp
        src/TextFinder.cpp
        src/TextFinder.h
        src/ThreadPool.cpp
        src/ThreadPool.h
        src/ConcurrentQueue.h
)

include(FetchContent)

FetchContent_Declare(
        LOGorithm
        GIT_REPOSITORY https://github.com/adrianovaladar/LOGorithm.git
        GIT_TAG main
)
FetchContent_MakeAvailable(LOGorithm)
target_link_libraries(kagebunshin PRIVATE LOGorithm)

# Add tests
add_subdirectory(tests)
