cmake_minimum_required(VERSION 3.11)
project(VendingMachineProject)

# Specify C++ standard
set(CMAKE_CXX_STANDARD 17)

# Include directories
include_directories(include)

# Define application sources, excluding main.cpp for the library
file(GLOB APP_SOURCES "src/*.cpp")
list(REMOVE_ITEM APP_SOURCES "${CMAKE_SOURCE_DIR}/src/main.cpp") # Exclude main.cpp

# Set output directories for all configurations
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELWITHDEBINFO ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_MINSIZEREL ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

# Create a static library from the application source files
add_library(VendingMachineLib STATIC ${APP_SOURCES})

# Create main executable
add_executable(VendingMachineProject src/main.cpp)

# Link the executable against the library
target_link_libraries(VendingMachineProject PRIVATE VendingMachineLib)

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

# Add test source files
set(TEST_SOURCES
    tests/VendingMachineBasicTests.cpp
    tests/VendingMachineTransactionTests.cpp
    tests/VendingMachineAdminTests.cpp
    tests/VendingMachineEdgeCaseTests.cpp
)

# Create test executable
add_executable(VendingMachineTests ${TEST_SOURCES})

# Link the test executable against the library and gtest
target_link_libraries(VendingMachineTests PRIVATE VendingMachineLib gtest_main)

# Add include directories for the tests
target_include_directories(VendingMachineTests PRIVATE include)

# Add tests
add_test(NAME VendingMachineTest COMMAND VendingMachineTests)
set_tests_properties(VendingMachineTest PROPERTIES WORKING_DIRECTORY ${CMAKE_RUNTIME_OUTPUT_DIRECTORY})

