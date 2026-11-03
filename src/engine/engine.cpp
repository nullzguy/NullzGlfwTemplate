#include <iostream>

#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include "imgui.h"
#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "engine/engine.h"
#include "globals/globalSettings.h"

using namespace std;

int engine::Init(const char* name)
{
    // Initialize glfw
    if (!glfwInit()) { cerr << "Failed to initialize GLFW!\n"; return 1; }
    // Hint gl version for glfw
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE);
    // Create window
    window = glfwCreateWindow(sets.w, sets.h, name, nullptr, nullptr);
    if (window == nullptr) { cerr << "Failed to create GLFW window!\n"; glfwTerminate(); return 1; }
    glfwMakeContextCurrent(window);
    // Load OpenGL function pointers through glad
    if (!gladLoadGL(glfwGetProcAddress)) { cerr << "Failed to initialize GLAD!\n"; glfwDestroyWindow(window); glfwTerminate(); return 1; }
    // Unlock fps
    glfwSwapInterval(0);

    return 0;
}

void engine::Update()
{
    // Update width, height, projection, etc.
    // You can put some settings here, maybe.
    glfwGetFramebufferSize(window, &sets.w, &sets.h);
    glViewport(0, 0, sets.w, sets.h);
    glClearColor(0.1f, 0.1f, 0.16f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-sets.aspect(), sets.aspect(), -1.0, 1.0, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

int engine::InitImGui()
{
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
    if (!ImGui_ImplGlfw_InitForOpenGL(window, true)) { cerr << "Failed to initialize ImGUI for OpenGL!\n"; return 1; }
    if (!ImGui_ImplOpenGL3_Init("#version 410 compatibility")) { cerr << "Failed to initialize ImGUI!\n"; return 1; }
    return 0;
}

void engine::ImGuiFrame(int tps) 
{
    // Create new frame
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
    ImGui::Begin("Frame");
    // The whole menu
    // maxFps <= 0 means uncapped
    static float lastMaxFps = 60.0f;
    bool capFps = sets.maxFps > 0.0f;
    if (ImGui::Checkbox("Cap FPS", &capFps))
    {
        if (capFps) sets.maxFps = lastMaxFps;
        else
        {
            lastMaxFps = sets.maxFps;
            sets.maxFps = 0.0f;
        }
    }
    if (capFps) ImGui::SliderFloat("Max FPS", &sets.maxFps, 5.0f, 360.0f);
    // Same for tps
    static float lastMaxTps = 20.0f;
    bool capTps = globalSets.maxTps > 0.0f;
    if (ImGui::Checkbox("Cap TPS", &capTps))
    {
        if (capTps) globalSets.maxTps = lastMaxTps;
        else
        {
            lastMaxTps = globalSets.maxTps;
            globalSets.maxTps = 0.0f;
        }
    }
    if (capTps) ImGui::SliderFloat("Max TPS", &globalSets.maxTps, 5.0f, 360.0f);
    // FPS and TPS display
    ImGui::Text("%.1f FPS", ImGui::GetIO().Framerate);
    ImGui::Text("%d TPS", tps);

    ImGui::End();
    ImGui::Render();
}

void engine::DestroyAll()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwDestroyWindow(window);
    glfwTerminate();
}
