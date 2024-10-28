cmake_minimum_required(VERSION 3.5.0)
project(snake VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)           # Use C++17
set(CMAKE_CXX_STANDARD_REQUIRED ON)  # Enforce the standard
set(CMAKE_CXX_EXTENSIONS OFF)        # Disable compiler-specific extensions

include(CTest)
enable_testing()

# Include the FetchContent module to easily retrieve external dependencies
include(FetchContent) 

# Declare the `raylib` dependency using FetchContent
FetchContent_Declare(
  raylib                                                # Name of the dependency
  GIT_REPOSITORY https://github.com/raysan5/raylib.git  # Git repository URL for raylib
  GIT_TAG 4.5.0                                         # Specific tag or version of raylib to fetch
)

# Make the `raylib` content available to this project, so it can be linked later
FetchContent_MakeAvailable(raylib)

# Enable verbose output to provide more detailed information during the build process (useful for debugging)
set(CMAKE_VERBOSE_MAKEFILE ON)

# Define a list of source files for the project
set(
  SOURCE_FILES
    main.cpp
    snake/snake.cpp
    food/food.cpp
    constants.hpp
)
  
# Add an executable target named "snake" using the specified source files
add_executable(snake ${SOURCE_FILES})

# Link the "snake" target with raylib
target_link_libraries(snake PRIVATE raylib)

# Specify include directories for the "snake" target
target_include_directories(snake 
  PRIVATE                      # Scope is private, only this target will see these directories
    ${CMAKE_SOURCE_DIR}        # Root directory for constants.hpp
    ${CMAKE_SOURCE_DIR}/snake  # For headers in the snake folder
    ${CMAKE_SOURCE_DIR}/food   # For headers in the food folder
)
  
# Define an absolute path to the graphics folder
target_compile_definitions(snake 
  PRIVATE 
    GRAPHICS_PATH="${CMAKE_SOURCE_DIR}/graphics"
)