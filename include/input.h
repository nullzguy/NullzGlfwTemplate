#pragma once

#include <algorithm>
#include <limits>
#include <cmath>
#include <iostream>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GLFW/glfw3.h>
#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

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
