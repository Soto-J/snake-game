cmake_minimum_required(VERSION 3.5.0)
project(snake VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 17)        # Use C++17
set(CMAKE_CXX_STANDARD_REQUIRED ON)  # Enforce the standard
set(CMAKE_CXX_EXTENSIONS OFF)     # Disable compiler-specific extensions

include(CTest)
enable_testing()

include(FetchContent)
FetchContent_Declare(
  raylib
  GIT_REPOSITORY https://github.com/raysan5/raylib.git
  GIT_TAG 4.5.0
)

FetchContent_MakeAvailable(raylib)

add_executable(snake main.cpp)

target_link_libraries(snake PRIVATE raylib)