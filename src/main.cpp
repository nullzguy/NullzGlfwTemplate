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
#include "engine.h"
#include "simStep.h"
#include "render.h"

using namespace std;

int main()
{
    try
    {
        Engine engine("nullz's glfw template", 800, 600);
        if (engine.InitImGui()!=0) return 1;

        // Timer stuff creation (ignore this)
        int ticks = 0, tps = 0;
        double tpsTimer = 0.0, renderTimer = 0.0;
        double oldT = glfwGetTime();
    
        // The main loop
        while (!glfwWindowShouldClose(engine.window))
        {
            // Compute delta time
            double currentT = glfwGetTime();
            double dt = min(currentT - oldT, 0.25);
            oldT = currentT;
        
            // Run simulation logic
            SimStep(dt);
        
            // renderTimer & TPS logic
            renderTimer += dt*engine.sets.fps;
            tpsTimer += dt;
            ticks++;
            if (tpsTimer >= 1.0)
            {
                tpsTimer -= 1.0;
                tps = ticks;
                ticks = 0;
            }
        
            // Rendering:
            if (!engine.sets.capFps || renderTimer >= 1.0)
            {
                // Subtract back the renderTimer
                if (engine.sets.capFps) renderTimer -= 1.0;
                // Poll events
                glfwPollEvents();
                // Update window stuff
                engine.Update();
            
                // Rendering logic
                Render();
            
                // ImGui frame
                engine.ImGuiFrame(tps);
            
                ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
                glfwSwapBuffers(engine.window);
            }
        }
    
        // Destroy stuff when window is closed
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyContext();
        glfwDestroyWindow(engine.window);
        glfwTerminate();
        return 0;
    }
    catch (const exception& e)
    {
        cerr << "Fatal error:\n" << e.what() << "\n";
        return 1;
    }
}