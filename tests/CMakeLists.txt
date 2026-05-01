include(FetchContent)

FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_executable(test_sha256 test_sha256.cpp)
target_link_libraries(test_sha256 GTest::gtest_main sha256)

include(GoogleTest)
gtest_discover_tests(test_sha256)

add_custom_target(run_tests
        COMMAND test_sha256
        DEPENDS test_sha256
        COMMENT "Running Tests..."
        USES_TERMINAL
)