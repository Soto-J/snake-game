cmake_minimum_required(VERSION 3.5.0)
project(snake VERSION 0.1.0 LANGUAGES C CXX)

include(CTest)
enable_testing()

add_executable(snake  main.cpp)

set_property(TARGET snake PROPERTY CXX_STANDARD 17)

# 1. Create CMakeLists.txt
# 2. Create CMakePresets.json
# 3. cmake --preset default
# 4. cmake --build --preset default