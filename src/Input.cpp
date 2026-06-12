#include "Input.h"

#include <GLFW/glfw3.h>

GLFWwindow* Input::window_ = nullptr;

void Input::Initialize(
    GLFWwindow* window)
{
    window_ = window;
}

bool Input::IsKeyDown(
    Key key)
{
    if (!window_)
    {
        return false;
    }

    int glfwKey = GLFW_KEY_UNKNOWN;

    switch (key)
    {
    case Key::W:
        glfwKey = GLFW_KEY_W;
        break;

    case Key::A:
        glfwKey = GLFW_KEY_A;
        break;

    case Key::S:
        glfwKey = GLFW_KEY_S;
        break;

    case Key::D:
        glfwKey = GLFW_KEY_D;
        break;

    case Key::Space:
        glfwKey = GLFW_KEY_SPACE;
        break;
    }

    return glfwGetKey(
               window_,
               glfwKey) == GLFW_PRESS;
}