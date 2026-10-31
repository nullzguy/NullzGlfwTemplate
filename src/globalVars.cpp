#include "globalVars.h"

#include <algorithm>
#include "engine.h"
#include "globalSettings.h"
#include "render.h"
#include "simStep.h"

void StartTimer()
{
    oldT = glfwGetTime();
}

void UpdateDt()
{
    double currentT = glfwGetTime();
    dt = std::min(currentT - oldT, 0.25); // min() so that dt doesnt get too high
    oldT = currentT;
}

void UpdateSim()
{
    if (globalSets.maxTps > 0.0)
    {
        const double step = 1.0 / globalSets.maxTps;
        simTimer += dt;
        if (simTimer > 0.25) simTimer = 0.25;
        while (simTimer >= step)
        {
            SimStep(step);
            simTimer -= step;
            ticks++;
        }
    }
    else
    {
        SimStep(dt);
        ticks++;
    }
}

void UpdateRenderTimer(engine& e)
{
    if (e.sets.maxFps > 0.0) renderTimer += dt*e.sets.maxFps;
    else renderTimer = 0.0;

    tpsTimer += dt;
    if (tpsTimer >= 1.0)
    {
        tpsTimer -= 1.0;
        tps = ticks;
        ticks = 0;
    }
}

bool ShouldRender(engine& e)
{
    if (e.sets.maxFps <= 0.0) return true;
    if (renderTimer >= 1.0)
    {
        renderTimer -= 1.0;
        return true;
    }
    return false;
}

void UpdateRender(engine& e)
{
    // Update render timer
    UpdateRenderTimer(e);

    // Rendering:
    if (ShouldRender(e))
    {
        // Update window stuff
        e.Update();
            
        // Rendering logic
        Render();
            
        // ImGui frame
        e.ImGuiFrame(tps);
        // Render and swap buffers
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        glfwSwapBuffers(e.window);
    }
}