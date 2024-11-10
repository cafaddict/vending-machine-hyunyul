# Gather all source files in src, excluding main.cpp for the library
file(GLOB APP_SOURCES "*.cpp")
list(REMOVE_ITEM APP_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/main.cpp") # Exclude main.cpp

# Create the VendingMachineLib static library
add_library(VendingMachineLib STATIC ${APP_SOURCES})

# Link include directories to the library
target_include_directories(VendingMachineLib PUBLIC ${CMAKE_SOURCE_DIR}/include)

# Create the main application executable
add_executable(VendingMachineProject main.cpp)

# Link the main executable against the library
target_link_libraries(VendingMachineProject PRIVATE VendingMachineLib)
