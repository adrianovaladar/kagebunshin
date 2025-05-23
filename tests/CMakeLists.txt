add_executable(AllTests
        ConcurrentQueueTests.cpp
        ConcurrentQueueTests.h
        ../src/ConcurrentQueue.h
        main.cpp
        ThreadPoolTests.cpp
        ThreadPoolTests.h
        ../src/ThreadPool.cpp
        ../src/ThreadPool.h
        TextFinderTests.cpp
        TextFinderTests.h
        ../src/TextFinder.cpp
        ../src/TextFinder.h)
include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_Declare(
        LOGorithm
        GIT_REPOSITORY https://github.com/adrianovaladar/LOGorithm.git
        GIT_TAG main
)
FetchContent_MakeAvailable(LOGorithm)
FetchContent_MakeAvailable(googletest)
target_link_libraries(AllTests gtest gtest_main gmock_main LOGorithm)
