#pragma once

#include <stdexcept>
#include <string>

#include <GLFW/glfw3.h>

#include "engine/input.h"
#include "winSettings.h"

struct engine {
    GLFWwindow* window;
    winSettings sets;
    input inputs;
    
    // Methods
    int Init(const char* name);
    void Update();
    int InitImGui();
    void ImGuiFrame(int tps);
    void DestroyAll();
    
    // Constructor
    engine(std::string title, int width, int height, float fps = -1.0f) 
    : window(nullptr), sets(width, height, fps <= 0.0f ? 60.0f : fps), inputs() {
        if (Init((title == "") ? "Title" : title.c_str()) != 0) throw std::runtime_error("Failed to initialize engine!");
        inputs.Attach(window);
    }
};