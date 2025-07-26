cmake_minimum_required(VERSION 4.0)
project(SpaceInvaders CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Set output directory for executables
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# ----------------------------------------------------------------------------
# Fetch SFML from GitHub using FetchContent
# ----------------------------------------------------------------------------
include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.1
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

# ----------------------------------------------------------------------------
# Collect all source files and header files
# Use CONFIGURE_DEPENDS to let CMake re-run automatically
# if new files are added to these folders (supported in newer CMake versions)
# ----------------------------------------------------------------------------
file(GLOB_RECURSE SOURCE_FILES CONFIGURE_DEPENDS "src/*.cpp" "src/*.c")
file(GLOB_RECURSE HEADER_FILES CONFIGURE_DEPENDS "include/*.h" "include/*.hpp")

# ----------------------------------------------------------------------------
# Create the executable from all source and header files
# ----------------------------------------------------------------------------
add_executable(SpaceInvaders ${SOURCE_FILES} ${HEADER_FILES})

# ----------------------------------------------------------------------------
# Copy assets to build directory after building
# ----------------------------------------------------------------------------
add_custom_command(TARGET SpaceInvaders POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/assets
    ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/assets
)

# ----------------------------------------------------------------------------
# Add the include directory so headers can be found with #include "..."
# ----------------------------------------------------------------------------
target_include_directories(SpaceInvaders PRIVATE ${CMAKE_SOURCE_DIR}/include)

# ----------------------------------------------------------------------------
# Use C++20 standard (or change to cxx_std_23 if you prefer)
# ----------------------------------------------------------------------------
target_compile_features(SpaceInvaders PRIVATE cxx_std_20)

# ----------------------------------------------------------------------------
# Link the SFML graphics module (includes Window, System, etc.)
# ----------------------------------------------------------------------------
target_link_libraries(SpaceInvaders PRIVATE SFML::Graphics)