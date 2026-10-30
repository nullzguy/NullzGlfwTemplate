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
        # winSettings
        include/winSettings.h
        src/winSettings.cpp
        # engine
        include/engine.h
        src/engine.cpp
        # simulation
        include/simStep.h
        src/simStep.cpp
        # rendering
        include/render.h
        src/render.cpp
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
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include ${imgui_SOURCE_DIR} ${imgui_SOURCE_DIR}/backends )
target_link_libraries(${PROJECT_NAME} PRIVATE glfw OpenGL::GL glm::glm )