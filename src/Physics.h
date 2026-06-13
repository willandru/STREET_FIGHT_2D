#pragma once

#include "Match.h"

class Physics
{
public:

    void update(
        Match& match,
        float deltaTime);

private:

    void resolveFighterCollision(
        Fighter& fighter1,
        Fighter& fighter2);

    static constexpr float kGravity = -5.0f;
};