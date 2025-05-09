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
include_directories(build/debug/_deps/imgui-src)
include_directories(build/debug/_deps/imgui-src/backends)
file(GLOB IMGUI_SOURCES "build/debug/_deps/imgui-src/*.cpp")
list(APPEND IMGUI_SOURCES build/debug/_deps/imgui-src/backends/imgui_impl_sdl3.cpp)
list(APPEND IMGUI_SOURCES build/debug/_deps/imgui-src/backends/imgui_impl_sdlrenderer3.cpp)

include_directories(src/include)
file(GLOB PROJECT_SOURCES "src/*.cpp")

## Executables
add_executable(coollevelcreator ${PROJECT_SOURCES} ${IMGUI_SOURCES})
target_compile_features(coollevelcreator PRIVATE cxx_std_23)
target_link_libraries(coollevelcreator PRIVATE ${LIBS})
