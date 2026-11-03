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
#include "textures.h"

void InitShaders()
{
    computeShader = shader(SHADER_DIR "/vertex.glsl", SHADER_DIR "/compute.glsl");
    fragmentShader = shader(SHADER_DIR "/vertex.glsl", SHADER_DIR "/fragment.glsl");
}

void InitRenderTargets(int width, int height, int compWidth, int compHeight)
{
    renderWidth = width;
    renderHeight = height;
    screenWidth = width;
    screenHeight = height;
    simWidth = compWidth;
    simHeight = compHeight;

    // Compute A/B tex&FBO creation
    CreateTex2DUI(compWidth, compHeight, ComputeTexA);
    CreateTex2DUI(compWidth, compHeight, ComputeTexB);
    CreateFBO2DUI(ComputeFBOA, ComputeTexA);
    CreateFBO2DUI(ComputeFBOB, ComputeTexB);

    // And for frame
    CreateTex2D(width, height, FrameTex);
    CreateFBO2D(FrameFBO, FrameTex);

    // Texture bindings
    computeShader.Use();
    computeShader.SetInt("simTexA", 0);
    fragmentShader.Use();
    fragmentShader.SetInt("computeTex", 0);

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

void TryUpdateRes(engine& e)
{
    int width, height;
    glfwGetFramebufferSize(e.window, &width, &height);

    if (width != renderWidth || height != renderHeight)
    {
        DestroyFBO(FrameFBO);
        DestroyTex(FrameTex);

        renderWidth = width;
        renderHeight = height;
        CreateTex2D(width, height, FrameTex);
        CreateFBO2D(FrameFBO, FrameTex);
    }

    screenWidth = width;
    screenHeight = height;
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