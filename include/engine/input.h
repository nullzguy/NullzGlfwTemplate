#pragma once

#include <glm/glm.hpp>
#include <GLFW/glfw3.h>

struct input {
    GLFWwindow* window = nullptr;
    glm::dvec2 cursorPos{};
    glm::dvec2 scrollAccum{};
    glm::dvec2 scrollDelta{};
    
    // Methods
    bool Attach(GLFWwindow* w);
    bool KeyDown(int key);
    bool MouseButtonDown(int mb);
    void Poll();
    static void ScrollCallback(GLFWwindow* w, double x, double y);
    glm::dvec2 ScrollDelta() const;
    glm::dvec2 CursorDelta();
    
    input() = default;
};
