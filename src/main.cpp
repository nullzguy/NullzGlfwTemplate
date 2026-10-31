// -- NULLZ'S GLFW TEMPLATE --
// Recommended to read README.md

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
#include "globalVars.h"
#include "engine.h"
#include "render.h"

using namespace std;

int main()
{
    try
    {
        engine engine("nullz's glfw template", 800, 600);
        if (engine.InitImGui()!=0) return 1;
        StartTimer();
    
        // The main loop
        while (!glfwWindowShouldClose(engine.window))
        {
            // Poll
            glfwPollEvents();
            engine.inputs.Poll();
            // Update timers
            UpdateDt();
            // Try simulation
            UpdateSim();
            // Try render
            UpdateRender(engine);
        }
    
        engine.DestroyAll();
        return 0;
    }
    catch (const exception& e)
    {
        cerr << "Fatal error:\n" << e.what() << "\n";
        return 1;
    }
}