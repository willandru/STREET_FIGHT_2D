// src\Window.h

#pragma once

#include <GLFW/glfw3.h>

class Window
{
public:
    Window(int width, int height, const char* title);
    ~Window();

    Window(const Window&) = delete;
    Window& operator=(const Window&) = delete;

    bool isValid() const;
    bool shouldClose() const;
    void pollEvents() const;
    void swapBuffers() const;
    void processInput() const;

    GLFWwindow* glfwHandle() const; // <-- ESTA LÍNEA FALTA

private:
    GLFWwindow* handle_ = nullptr;
};