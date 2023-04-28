enable_testing()

# make googletest available
include(FetchContent)
FetchContent_Declare(
  googletest
  # Specify the commit you depend on and update it regularly.
  URL https://github.com/google/googletest/archive/e2239ee6043f73722e7aa812a459f54a28552929.zip
)
FetchContent_MakeAvailable(googletest)

# --- test_SimpleMockHelper ---

# add executable for SimpleMockHelper Plugin
add_executable(test_SimpleMockHelper test_SimpleMockHelper.cpp)

target_include_directories(test_SimpleMockHelper
    PUBLIC
    ${PROJECT_SOURCE_DIR/SimpleMockHelperPlugin/}
)

# link libraries needed for the test_SimpleMockHelper
target_link_libraries(test_SimpleMockHelper
    PRIVATE
        SimpleMockHelper
    PRIVATE
        gtest
    PRIVATE
        gtest_main
    )
  
add_dependencies(test_SimpleMockHelper SimpleMockHelper)

add_test(NAME run_test_SimpleMockHelper COMMAND test_SimpleMockHelper)
# --------------------------