cmake_minimum_required(VERSION 3.28)
project(CMakeSFMLProject LANGUAGES CXX)

# Set output directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Define resource directory 
add_definitions(-DRESOURCE_DIR="${CMAKE_SOURCE_DIR}/resources")

# Fetch SFML
include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.1
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

# Create your drawing library
add_library(draw_lib
    src/Draw.cpp
    src/Human.cpp
    src/TileMap.cpp
)

# Set include directories for the library
target_include_directories(draw_lib PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/header 
)

# Link SFML to your library
target_link_libraries(draw_lib PUBLIC SFML::Graphics)

# Add your executable
add_executable(main src/main.cpp)

# Set C++ standard for all targets
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Link libraries to your executable
target_link_libraries(main PRIVATE 
    draw_lib  # This gives main access to both your library and SFML
)