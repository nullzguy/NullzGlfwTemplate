// -- NULLZ'S GLFW TEMPLATE --
// Recommended to read README.md

#include <exception>
#include <iostream>
#include <GLFW/glfw3.h>
#include "globalStuff.h"
#include "engine.h"
#include "shader.h"

using namespace std;

int main()
{
    try
    {
        // Init
        engine engine("nullz's glfw template", 800, 600);
        if (engine.InitImGui()!=0) return 1;
        InitRenderTargets(engine.sets.w, engine.sets.h);
        StartTimer();
        
        // The main loop
        while (!glfwWindowShouldClose(engine.window))
        {
            // Poll
            glfwPollEvents();
            engine.inputs.Poll();
            // Update timers
            UpdateDt();
            // Try updating the simulation
            TryUpdateSim();
            // Try render
            TryRender(engine);
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