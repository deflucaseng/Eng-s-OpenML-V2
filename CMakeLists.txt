cmake_minimum_required(VERSION 3.10)
project(MyProject)

set(CMAKE_CXX_STANDARD 11)

# Add Google Test
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

# Add test_utils directory
include_directories(${CMAKE_SOURCE_DIR}/src/include)

# Add the source files
file(GLOB_RECURSE SOURCES "src/operations/**/*.cpp")

# Add the test files
file(GLOB_RECURSE TEST_SOURCES "testing/tests/**/*.cpp")

# Create the main test executable
add_executable(RunAllTests ${SOURCES} ${TEST_SOURCES} testing/runtests.cpp)

# Link Google Test and pthread
target_link_libraries(RunAllTests ${GTEST_LIBRARIES} pthread)