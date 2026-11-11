#include "globals/globalStuff.h"

void StartTimer() {
    oldT = glfwGetTime();
}

void UpdateDt() {
    double currentT = glfwGetTime();
    dt = std::min(currentT - oldT, 0.25); // min() so that dt doesnt get too high
    oldT = currentT;
}

void TryUpdateRes(engine& e) {
    int width, height;
    glfwGetFramebufferSize(e.window, &width, &height);

    if (width != renderWidth || height != renderHeight) {
        DestroyFBO(FrameFBO0);
        DestroyTex(FrameTex);

        renderWidth = width;
        renderHeight = height;
        CreateTex2D(width, height, FrameTex);
        CreateFBO2D(FrameFBO0, FrameTex);
    }

    screenWidth = width;
    screenHeight = height;
}

void TryUpdateSim() {
    if (globalSets.maxTps > 0.0) {
        const double step = 1.0 / globalSets.maxTps;
        simTimer += dt;
        if (simTimer > 0.25) simTimer = 0.25;
        while (simTimer >= step) {
            SimStep(step);
            simTimer -= step;
            ticks++;
        }
    } else {
        SimStep(dt);
        ticks++;
    }
}

void UpdateRenderTimer(engine& e) {
    if (e.sets.maxFps > 0.0) renderTimer += dt*e.sets.maxFps;
    else renderTimer = 0.0;

    tpsTimer += dt;
    if (tpsTimer >= 1.0) {
        tpsTimer -= 1.0;
        tps = ticks;
        ticks = 0;
    }
}

bool ShouldRender(engine& e) {
    if (e.sets.maxFps <= 0.0) return true;
    if (renderTimer >= 1.0) {
        renderTimer -= 1.0;
        return true;
    }
    return false;
}

void TryRender(engine& e) {
    // Update render timer
    UpdateRenderTimer(e);

    // Rendering:
    if (ShouldRender(e)) {
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