cmake_minimum_required(VERSION 3.31)
project(coollevelcreator)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# CPM
file(
        DOWNLOAD
        https://github.com/cpm-cmake/CPM.cmake/releases/download/v0.41.0/CPM.cmake
        ${CMAKE_CURRENT_BINARY_DIR}/cmake/CPM.cmake
        EXPECTED_HASH SHA256=e570f03806b9aae2082ca5b950a9e6b3b41ad56972a78a876aedcaad16653116
)
include(${CMAKE_CURRENT_BINARY_DIR}/cmake/CPM.cmake)

set(LIBS)
set(SDL_TEST OFF)

## Dependencies
# SDL
CPMAddPackage("gh:libsdl-org/SDL#release-3.2.10")
list(APPEND LIBS SDL3::SDL3)

# Dear ImGui
CPMAddPackage("gh:ocornut/imgui#v1.91.9b-docking")
list(APPEND LIBS imgui)

include_directories(src/include)

## Executables
add_executable(coollevelcreator src/main.cpp)
target_compile_features(coollevelcreator PRIVATE cxx_std_23)
target_link_libraries(coollevelcreator PRIVATE ${LIBS})
