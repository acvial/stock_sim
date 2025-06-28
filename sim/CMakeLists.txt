cmake_minimum_required(VERSION 3.16)

# Project name and version
project(Stock_Simulator VERSION 1.0 LANGUAGES CXX)

# C++ standard (you can change to 20 or 23 if needed)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Export compile_commands.json (useful for clangd, tools, etc.)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# GCC/Clang compiler warnings
if (CMAKE_CXX_COMPILER_ID MATCHES "GNU|Clang")
    add_compile_options(
        -Wall
        -Wextra
        -Wpedantic
        -Werror
        -Wconversion
        -Wsign-conversion
        -Wshadow
    )
endif()

enable_testing()

# Add subdirectories
add_subdirectory(src)
add_subdirectory(tests)
