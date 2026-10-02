cmake_minimum_required(VERSION 4.4)
project(mygame)
set(CMAKE_C_COMPILER "C:/w64devkit/bin/gcc.exe")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(SDL3_DIR "C:/Dev/.Libraries/SDL-release-3.4.16/lib/cmake/SDL3")

# Create an option to switch between a system sdl library and a vendored SDL library
#option(MYGAME_VENDORED "Use vendored libraries" OFF)

if(MYGAME_VENDORED)
    # This assumes you have added SDL as a submodule in vendored/SDL
    add_subdirectory(vendored/SDL EXCLUDE_FROM_ALL)
else()
    # 1. Look for a SDL3 package,
    # 2. look for the SDL3-shared component, and
    # 3. fail if the shared component cannot be found.
    find_package(SDL3 REQUIRED CONFIG REQUIRED COMPONENTS SDL3-shared)
endif()

# Create your game executable target as usual
add_executable(${PROJECT_NAME} WIN32 main.c)

# Error flags
target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -pedantic)

set_target_properties(${PROJECT_NAME} PROPERTIES
    C_STANDARD 23              # Or 99, 17, etc.
    C_STANDARD_REQUIRED ON     # Fail if the compiler can't do it
    C_EXTENSIONS ON           # Use -std=c11 instead of -std=gnu11
)

# Link to the actual SDL3 library.
target_link_libraries(${PROJECT_NAME} PRIVATE SDL3::SDL3)
