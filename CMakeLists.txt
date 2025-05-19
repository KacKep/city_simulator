cmake_minimum_required(VERSION 3.28)
project(CMakeSFMLProject LANGUAGES CXX)

# Output directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Resource directory 
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

# Create library
add_library(draw_lib
    
    
    src/TileMap.cpp
    src/Building.cpp
    src/Shop.cpp
    src/City.cpp
    src/Entity.cpp
    
    src/Hospital.cpp 
    src/OfficeBuilding.cpp
    src/Dog.cpp
    src/LiqourShop.cpp
    src/Cat.cpp
    src/Item.cpp
    src/Human.cpp
)

# Include directories for the library
target_include_directories(draw_lib PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/header 
)

# Link SFML 
target_link_libraries(draw_lib PUBLIC SFML::Graphics)

# Executable
add_executable(main src/main.cpp )

# Sets C++ standard 
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Links libraries 
target_link_libraries(main PRIVATE 
    draw_lib  
)