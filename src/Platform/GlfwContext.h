//src\GlfwContext.h

#pragma once

#include <GLFW/glfw3.h>

class GlfwContext
{
public:
    GlfwContext();
    ~GlfwContext();

    GlfwContext(const GlfwContext&) = delete;
    GlfwContext& operator=(const GlfwContext&) = delete;

    bool isValid() const;

private:
    bool valid_ = false;
};