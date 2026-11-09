# project name
set(PROJECT_NAME NullzGlfwTemplate)

# CMake version check and project initialization
cmake_minimum_required(VERSION 3.20)
project(${PROJECT_NAME})

# settings
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# required packages
find_package(OpenGL REQUIRED)
find_package(glfw3 3.3 REQUIRED)
find_package(glm REQUIRED)

# get imgui
include(FetchContent)
set(FETCHCONTENT_UPDATES_DISCONNECTED ON)
FetchContent_Declare( imgui GIT_REPOSITORY https://github.com/ocornut/imgui.git GIT_TAG v1.91.9b
        GIT_SHALLOW TRUE
        GIT_PROGRESS TRUE)
FetchContent_MakeAvailable(imgui)

# embed shaders
set(SHADER_HEADER ${CMAKE_CURRENT_BINARY_DIR}/generated/shaders.hpp)
file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/generated)
file(WRITE ${SHADER_HEADER} "#pragma once\nnamespace Shaders {\n")
file(GLOB SHADER_FILES CONFIGURE_DEPENDS ${CMAKE_SOURCE_DIR}/shaders/*.glsl)

foreach(FILE ${SHADER_FILES})
    get_filename_component(NAME ${FILE} NAME_WE)
    file(READ ${FILE} SOURCE)
    file(APPEND ${SHADER_HEADER} "inline constexpr const char* ${NAME} = R\"NULLZ(\n${SOURCE}\n)NULLZ\";\n")
endforeach()

# add executables
add_executable(${PROJECT_NAME}
        # glad
        external/glad/src/gl.c
        # globals
        include/globals/globalSettings.h
        src/globals/globalSettings.cpp
        include/globals/globalStuff.h
        src/globals/globalStuff.cpp
        # files management
        include/files_management/files.h
        src/files_management/files.cpp
        # audio management
        include/audio/audio.h
        src/audio/audio.cpp
        # engine
        include/engine/winSettings.h
        src/engine/winSettings.cpp
        include/engine/input.h
        src/engine/input.cpp
        include/engine/engine.h
        src/engine/engine.cpp
        # gpu
        include/gpu/shader.h
        src/gpu/shader.cpp
        include/gpu/textures.h
        src/gpu/textures.cpp
        # main
        src/main/main.cpp
        include/main/sim.h
        src/main/sim.cpp
        include/main/render.h
        src/main/render.cpp
        # misc
        include/misc/helpers.h
        src/misc/helpers.cpp
        # imgui
        ${imgui_SOURCE_DIR}/imgui.cpp
        ${imgui_SOURCE_DIR}/imgui_draw.cpp
        ${imgui_SOURCE_DIR}/imgui_tables.cpp
        ${imgui_SOURCE_DIR}/imgui_widgets.cpp
        ${imgui_SOURCE_DIR}/backends/imgui_impl_glfw.cpp
        ${imgui_SOURCE_DIR}/backends/imgui_impl_opengl3.cpp
)

# include libraries & directories
target_include_directories(${PROJECT_NAME} PRIVATE include external/glad/include ${CMAKE_CURRENT_SOURCE_DIR}/include ${imgui_SOURCE_DIR} ${imgui_SOURCE_DIR}/backends )
target_link_libraries(${PROJECT_NAME} PRIVATE glfw OpenGL::GL glm::glm )
target_compile_definitions(${PROJECT_NAME} PRIVATE
        GLFW_INCLUDE_NONE
        SHADER_DIR="${CMAKE_CURRENT_SOURCE_DIR}/shaders")