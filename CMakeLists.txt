cmake_minimum_required(VERSION 3.28)
project(CMakeSFMLProject LANGUAGES CXX)

# Sets C++ standard 
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Output directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Resource directory 
add_definitions(-DRESOURCE_DIR="${CMAKE_SOURCE_DIR}/resources")

# Enable testing
enable_testing()
include(CTest)

# Fetch SFML
include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.1
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

# Catch2 
FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v3.4.0 
)

FetchContent_MakeAvailable(Catch2)
#truly there is nothing better than copy pasting from github

# Create library
add_library(draw_lib
    src/TileMap.cpp
    src/Building.cpp
    src/Shop.cpp
    src/City.cpp
    src/Entity.cpp
    src/Hospital.cpp 
    src/OfficeBuilding.cpp
    src/Animal.cpp
    src/LiqourShop.cpp
    src/Cat.cpp
    src/Item.cpp
    src/Human.cpp
    src/Dog.cpp
)

target_include_directories(draw_lib PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/header
)

# Link SFML 
target_link_libraries(draw_lib PUBLIC SFML::Graphics)

# Executable
add_executable(main src/main.cpp )

# Links libraries 
target_link_libraries(main PRIVATE 
    draw_lib  
)

# Test executable
add_executable(tests
    tests/test_building.cpp # there is like one method for all of them that isn't another getter
    tests/test_human.cpp # dogs and cats use the same logic
)

# linking librarys to tests
target_link_libraries(tests PRIVATE draw_lib Catch2::Catch2WithMain)
target_include_directories(tests PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/header)

#Tests
include(Catch)
catch_discover_tests(tests)

find_package(Doxygen REQUIRED dot)

# hate it or love it but it works 
# I have no idea why properties are gone but cmake doesn't care so why should I?
if(DOXYGEN_FOUND)
    # Doxygen configuration
    set(DOXYGEN_INPUT_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src ${CMAKE_CURRENT_SOURCE_DIR}/header")
    set(DOXYGEN_OUTPUT_DIR ${CMAKE_CURRENT_BINARY_DIR}/docs)
    set(DOXYGEN_INDEX_FILE ${DOXYGEN_OUTPUT_DIR}/html/index.html)
    set(DOXYGEN_GENERATE_HTML YES)
    set(DOXYGEN_EXTRACT_ALL YES)
    set(DOXYGEN_RECURSIVE YES)
    set(DOXYGEN_USE_DOT YES)
    set(DOXYGEN_CALL_GRAPH YES)
    set(DOXYGEN_CALLER_GRAPH YES)
    
    doxygen_add_docs(
        docs
        ${CMAKE_CURRENT_SOURCE_DIR}/src
        ${CMAKE_CURRENT_SOURCE_DIR}/header
        COMMENT "Generating documentation, please wait for garbage collector"
    )
endif()