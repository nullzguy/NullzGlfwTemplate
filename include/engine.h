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

#include "winSettings.h"

using namespace std;

struct Engine
{
    GLFWwindow* window;
    winSettings sets;
    
    // Methods
    int Init(const char* name);
    void Update();
    int InitImGui();
    void ImGuiFrame(int tps);
    
    // Constructor
    Engine(string title, int width, int height, float fps = -1.0f) 
    : window(nullptr), sets(width, height, fps != 0.0, fps <= 0.0f ? 60.0f : fps)
    { if (Init((title == "") ? "Title" : title.c_str()) != 0) throw runtime_error("Failed to initialize engine!"); }
};