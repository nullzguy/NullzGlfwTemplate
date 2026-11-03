#pragma once

#include <glm/glm.hpp>
#include <GLFW/glfw3.h>

using namespace glm;

struct input
{
    GLFWwindow* window = nullptr;
    dvec2 cursorPos{};
    dvec2 scrollAccum{};
    dvec2 scrollDelta{};
    
    // Methods
    bool Attach(GLFWwindow* w);
    bool KeyDown(int key);
    bool MouseButtonDown(int mb);
    void Poll();
    static void ScrollCallback(GLFWwindow* w, double x, double y);
    dvec2 ScrollDelta() const;
    dvec2 CursorDelta();
    
    input() = default;
};
