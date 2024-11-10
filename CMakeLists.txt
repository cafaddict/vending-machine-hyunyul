cmake_minimum_required(VERSION 3.11)
project(VendingMachineProject)

# Specify C++ standard
set(CMAKE_CXX_STANDARD 17)

# Include directories for header files
include_directories(include)

# Set the output directory for the binaries
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Add the src directory
add_subdirectory(src)

# Enable testing
enable_testing()

# Include FetchContent module for Google Test
include(FetchContent)

# Download GoogleTest
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/release-1.11.0.zip
)

# Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# Download and add gtest
FetchContent_MakeAvailable(googletest)

# Collect all test sources
file(GLOB TEST_SOURCES "tests/*.cpp")

# Create the test executable
add_executable(VendingMachineTests ${TEST_SOURCES})

# Link the test executable against the library and gtest
target_link_libraries(VendingMachineTests PRIVATE VendingMachineLib gtest_main)

# Add include directories for the tests
target_include_directories(VendingMachineTests PRIVATE include)

# Register the test executable with CTest
add_test(NAME VendingMachineTest COMMAND VendingMachineTests)
set_tests_properties(VendingMachineTest PROPERTIES WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
