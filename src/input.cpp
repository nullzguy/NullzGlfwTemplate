#include "input.h"

bool input::Attach(GLFWwindow* w)
{
    window = w;
    if (!window) return false;

    glfwSetWindowUserPointer(window, this);
    glfwSetScrollCallback(window, &input::ScrollCallback);

    glfwGetCursorPos(window, &cursorPos.x, &cursorPos.y);
    return true;
}

bool input::KeyDown(int key)
{
    if (ImGui::GetIO().WantCaptureKeyboard) return false;
    return glfwGetKey(window, key) != GLFW_RELEASE;
}

bool input::MouseButtonDown(int mb)
{
    if (ImGui::GetIO().WantCaptureMouse) return false;
    return glfwGetMouseButton(window, mb) == GLFW_PRESS;
}

void input::ScrollCallback(GLFWwindow* w, double x, double y)
{
    void* raw = glfwGetWindowUserPointer(w);
    input* self = static_cast<input*>(raw);
    if (self) self->scrollAccum += dvec2(x, y);
}

void input::Poll()
{
    if (ImGui::GetIO().WantCaptureMouse)
        scrollAccum = dvec2(0.0);

    scrollDelta = scrollAccum;
    scrollAccum = dvec2(0.0);
}

dvec2 input::ScrollDelta() const
{
    return scrollDelta;
}

dvec2 input::CursorDelta()
{
    dvec2 lastPos = cursorPos;
    glfwGetCursorPos(window, &cursorPos.x, &cursorPos.y);
    if (ImGui::GetIO().WantCaptureMouse) return dvec2(0.0);
    return cursorPos - lastPos;
}