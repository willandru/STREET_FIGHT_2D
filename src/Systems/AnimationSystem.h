#pragma once

class Fighter;

class AnimationSystem
{
public:
    void update(
        Fighter& fighter,
        float deltaTime);
};