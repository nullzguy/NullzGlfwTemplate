#include <algorithm>
#include <GLFW/glfw3.h>
#include <glad/gl.h>
#include "imgui.h"
#include "imgui_impl_opengl3.h"
#include "globalStuff.h"
#include "engine.h"
#include "globalSettings.h"
#include "render.h"
#include "simStep.h"
#include "shader.h"

#ifndef SHADER_DIR
#define SHADER_DIR "shaders"
#endif

shader& computeShader()
{
    static shader s(SHADER_DIR "/vertex.glsl", SHADER_DIR "/compute.glsl");
    return s;
}

shader& fragmentShader()
{
    static shader s(SHADER_DIR "/vertex.glsl", SHADER_DIR "/fragment.glsl");
    return s;
}

void InitRenderTargets(int width, int height)
{
    renderWidth = width;
    renderHeight = height;

    // Compute ping-pong targets (integer, initially empty)
    computeShader().CreateTex2DUI(width, height, ComputeTexA);
    computeShader().CreateTex2DUI(width, height, ComputeTexB);
    computeShader().CreateFBO2DUI(ComputeFBOA, ComputeTexA);
    computeShader().CreateFBO2DUI(ComputeFBOB, ComputeTexB);

    // Fragment pass target: RGBA8 so it can be blitted to the screen
    fragmentShader().CreateTex2D(width, height, FrameTex);
    fragmentShader().CreateFBO2D(FrameFBO, FrameTex);

    // Constant texture unit bindings
    computeShader().Use();
    computeShader().SetInt("simTexA", 0);
    fragmentShader().Use();
    fragmentShader().SetInt("computeTex", 0);

    // Make the compute textures empty
    glBindFramebuffer(GL_FRAMEBUFFER, ComputeFBOA);
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glBindFramebuffer(GL_FRAMEBUFFER, ComputeFBOB);
    glClear(GL_COLOR_BUFFER_BIT);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

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

void TryUpdateSim()
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

void TryRender(engine& e)
{
    // Update render timer
    UpdateRenderTimer(e);

    // Rendering:
    if (ShouldRender(e))
    {
        // Update window stuff
        e.Update();
        screenWidth = e.sets.w;
        screenHeight = e.sets.h;

        // Rendering logic
        Render();
            
        // ImGui frame
        e.ImGuiFrame(tps);
        // Render and swap buffers
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        glfwSwapBuffers(e.window);
    }
}