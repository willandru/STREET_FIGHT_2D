#pragma once

#include "Transform.h"

struct FighterPhysicsData
{
    Transform transform;

    float velocityX = 0.0f;
    float velocityY = 0.0f;

    bool grounded = false;
};