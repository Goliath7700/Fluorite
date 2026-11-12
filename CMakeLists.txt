cmake_minimum_required(VERSION 4.4)
include(FetchContent)
project(mygame)
set(CMAKE_C_COMPILER "C:/w64devkit/bin/cc.exe")
set(CMAKE_CXX_COMPILER "C:/w64devkit/bin/c++.exe")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/src/assets"
     DESTINATION "${CMAKE_CURRENT_BINARY_DIR}")

FetchContent_Declare(
  box2d
  GIT_REPOSITORY https://github.com/erincatto/box2d.git
  GIT_TAG v3.2.0 # Replace with a specific version or use "main"
)
FetchContent_MakeAvailable(box2d)

# set the output directory for built objects.
# This makes sure that the dynamic library goes into the build directory automatically.
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")

# This assumes the SDL source is available in vendored/SDL
add_subdirectory(vendored/SDL EXCLUDE_FROM_ALL)

add_executable(${PROJECT_NAME} WIN32 src/main.c)
target_link_libraries(${PROJECT_NAME} PRIVATE SDL3::SDL3 box2d::box2d)
target_compile_options(${PROJECT_NAME} PRIVATE -Wall -Wextra -pedantic)
set_target_properties(${PROJECT_NAME} PROPERTIES
    C_STANDARD 23
    C_STANDARD_REQUIRED ON
    C_EXTENSIONS ON
)
