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

// May conflict
using namespace std;
using namespace glm;

struct winSettings {
    // Width and height
    int w, h;
    // Frames per second & capping (simulation runs continuously, 
    // rendering happens every 1/fps seconds)
    bool capFps;
    float fps;
    // Returns the aspect
    double aspect() const { return (double)w/(double)h; };
};

struct Engine {
    GLFWwindow* window;
    winSettings sets;

    int Init(const char* name) {
        // Initialize glfw
        if (!glfwInit()) { cerr << "Failed to initialize GLFW!\n"; return 1; }
        // Hint gl version for glfw
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);
        // Create window
        window = glfwCreateWindow(sets.w, sets.h, name, nullptr, nullptr);
        if (window == nullptr) { cerr << "Failed to create GLFW window!\n"; glfwTerminate(); return 1; }
        glfwMakeContextCurrent(window);
        // Unlock fps
        glfwSwapInterval(0);

        return 0;
    }
};

int initImGui(Engine& e) {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    // Style
    ImGuiStyle& style = ImGui::GetStyle();
    style.Alpha = 0.8f;
    style.WindowRounding = 8.0f;
    // Colors
    // example:
    // style.Colors[ImGuiCol_Text] = ImVec4(1.0f, 0.0f, 0.0f, 1.0f);

    // Thanks to:
    // https://deepwiki.com/ocornut/imgui/6.3-styling-and-theming
    // https://docs.anvil.team/enums/imguicol

    // Init ImGUI
    if (!ImGui_ImplGlfw_InitForOpenGL(e.window, true)) { cerr << "Failed to initialize ImGUI for OpenGL!\n"; return 1; }
    if (!ImGui_ImplOpenGL3_Init("#version 460")) { cerr << "Failed to initialize ImGUI!\n"; return 1; }
    return 0;
}

void ImGuiFrame(Engine& e, int tps) {
    // Create new frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
    ImGui::Begin("Controls and stuff");
    // The whole menu
    ImGui::Checkbox("Cap FPS", &e.sets.capFps);
    if (e.sets.capFps) ImGui::SliderFloat("Max FPS", &e.sets.fps, 5.0f, 360.0f);
    ImGui::Text("%.1f FPS", ImGui::GetIO().Framerate);
    ImGui::Text("%d TPS", tps);

    ImGui::End();
    ImGui::Render();
}

void updateGlfwWindow(Engine& e) {
    // Update width, height, projection.
    glfwGetFramebufferSize(e.window, &e.sets.w, &e.sets.h);
    glViewport(0, 0, e.sets.w, e.sets.h);
    glClearColor(0.1f, 0.1f, 0.16f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glOrtho(-e.sets.aspect(), e.sets.aspect(), -1.0, 1.0, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

int main() {
    Engine engine;
    // 800x600 window, with fps capping enabled, and capped to 60.
    engine.sets = {800, 600, true, 60.0f};
    if (engine.Init((char*)"Title")!=0) return 1;
    if (initImGui(engine)!=0) return 1;

    int ticks = 0, tps = 0;
    double tpsTimer = 0.0, renderTimer = 0.0;
    double oldT = glfwGetTime();
    while (!glfwWindowShouldClose(engine.window)) {
        // Compute delta time
        double currentT = glfwGetTime();
        double dt = currentT - oldT;
        oldT = currentT;
        
        // - Simulation -

        // simulation logic should go here

        // renderTimer & TPS logic
        renderTimer += dt*engine.sets.fps;
        tpsTimer += dt;
        ticks++;
        if (tpsTimer >= 1.0) {
            tpsTimer -= 1.0;
            tps = ticks;
            ticks = 0;
        }

        if (!engine.sets.capFps || renderTimer >= 1.0) {
            // Subtract back the renderTimer
            if (engine.sets.capFps) renderTimer -= 1.0;
            // Update window stuff & render
            updateGlfwWindow(engine);
            glfwPollEvents();
            ImGuiFrame(engine, tps);
            ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
            glfwSwapBuffers(engine.window);
        }
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(engine.window);
    glfwTerminate();
    return 0;
}
