// -- NULLZ'S GLFW TEMPLATE --
// Recommended to read README.md

#include <exception>
#include <iostream>
#include <GLFW/glfw3.h>
#include "globals/globalStuff.h"
#include "engine/engine.h"
#include "gpu/shader.h"

using namespace std;

int main()
{
    try
    {
        // Init
        engine engine("nullz's glfw template", 800, 600);
        if (engine.InitImGui()!=0) return 1;
        InitShaders();
        InitRenderTargets(engine.sets.w, engine.sets.h, 10, 10);
        StartTimer();

        // The main loop
        while (!glfwWindowShouldClose(engine.window))
        {
            // Poll
            glfwPollEvents();
            // Try updating the resolution
            TryUpdateRes(engine);
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