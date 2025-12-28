# CMakeLists.txt for Mavlink Fallback Logger

# Minimum CMake version required
cmake_minimum_required(VERSION 3.10)

# Project name and version
project(MavlinkFallbackLogger VERSION 1.0 LANGUAGES C CXX)

# Set C++ standard to C++11 or higher
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include directories
include_directories(include)

# Source files
set(SOURCES
    src/mavlink_logger.cpp
    src/fallback_logger.cpp
)

# Create the executable
add_executable(mavlink_logger ${SOURCES})

# Enable testing
enable_testing()

# Add a test executable
add_executable(test_mavlink_logger tests/test_mavlink_logger.cpp)

# Link test executable with the main target
target_link_libraries(test_mavlink_logger mavlink_logger)

# Add tests
add_test(NAME TestMavlinkLogger COMMAND test_mavlink_logger)

# Add installation rules (optional)
install(TARGETS mavlink_logger DESTINATION bin)
install(FILES include/mavlink_logger.hpp include/fallback_logger.hpp DESTINATION include)
