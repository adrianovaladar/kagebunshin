cmake_minimum_required(VERSION 3.26)
project(kagebunshin)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_FLAGS " ${CMAKE_CXX_FLAGS} --coverage")

add_executable(kagebunshin
        src/main.cpp
        src/Logger.cpp
        src/Logger.h
        src/TextFinder.cpp
        src/TextFinder.h
        src/ThreadPool.cpp
        src/ThreadPool.h
        src/ConcurrentQueue.h
)

# Add tests
add_subdirectory(tests)
