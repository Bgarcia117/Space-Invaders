# CMakeList.txt CMake project for Space Invaders
cmake_minimum_required(VERSION 3.8)

# Enable Hot Reload for MSVC compilers if supported.
# Allows for code changes without full rebuilds in Visual Studio
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

# Project Name and Language Specification
project("Space Invaders" LANGUAGES CXX)

# Set ouput directory for executable
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Fetch and build SFML
include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.1
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

# Find all source files (.cpp) in src/ and all subdirectories recursively
file(GLOB_RECURSE SOURCES "src/*.cpp")

# Create executable with all found source files
add_executable(SpaceInvaders ${SOURCES})

# Set C++20 Standard
set_property(TARGET SpaceInvaders PROPERTY CXX_STANDARD 20)

# Link SFML libraries to executable
target_link_libraries(SpaceInvaders PRIVATE SFML::Graphics)