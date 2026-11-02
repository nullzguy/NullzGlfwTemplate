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

# add executables
add_executable(${PROJECT_NAME}
        # glad
        external/glad/src/gl.c
        # global settings
        include/globalSettings.h
        src/globalSettings.cpp
        # variables
        include/globalStuff.h
        src/globalStuff.cpp
        # window settings
        include/winSettings.h
        src/winSettings.cpp
        # engine
        include/engine.h
        src/engine.cpp
        # inputs
        include/input.h
        src/input.cpp
        # simulation
        include/simStep.h
        src/simStep.cpp
        # rendering
        include/render.h
        src/render.cpp
        # shader
        include/shader.h
        src/shader.cpp
        # main
        src/main.cpp
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
# GLFW_INCLUDE_NONE stops GLFW from pulling in <GL/gl.h>, which conflicts with glad
# SHADER_DIR makes shader loading independent of the working directory
target_compile_definitions(${PROJECT_NAME} PRIVATE
        GLFW_INCLUDE_NONE
        SHADER_DIR="${CMAKE_CURRENT_SOURCE_DIR}/shaders")