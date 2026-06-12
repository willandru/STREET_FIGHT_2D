#include "GameTime.h"

#include <GLFW/glfw3.h>

void GameTime::update()
{
    const double currentTime =
        glfwGetTime();

    if (!initialized_)
    {
        lastTime_ = currentTime;
        initialized_ = true;
        deltaTime_ = 0.0f;
        return;
    }

    deltaTime_ =
        static_cast<float>(
            currentTime - lastTime_);

    lastTime_ = currentTime;
}

float GameTime::deltaTime() const
{
    return deltaTime_;
}