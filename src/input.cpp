#include "input.h"

bool input::Attach(GLFWwindow* w)
{
    window = w;
    if (window) glfwGetCursorPos(window, &cursorPos.x, &cursorPos.y);
    else return false;
    return true;
}

bool input::KeyDown(int key)
{
    if (ImGui::GetIO().WantCaptureKeyboard) return false;
    return glfwGetKey(window, key);
}

bool input::MouseButtonDown(int mb)
{
    if (ImGui::GetIO().WantCaptureMouse) return false;
    return glfwGetMouseButton(window, mb);
}

dvec2 input::CursorDelta()
{
    if (ImGui::GetIO().WantCaptureMouse) return cursorPos;
    glm::dvec2 lastPos = cursorPos;
    glfwGetCursorPos(window, &cursorPos.x, &cursorPos.y);
    return cursorPos - lastPos;
}