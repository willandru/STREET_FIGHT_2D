#pragma once

class GameTime
{
public:
    void update();

    float deltaTime() const;

private:
    float deltaTime_ = 0.0f;

    double lastTime_ = 0.0;
    bool initialized_ = false;
};