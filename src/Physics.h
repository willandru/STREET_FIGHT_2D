#pragma once

#include "Match.h"

class Physics
{
public:

    void update(
        Match& match,
        float deltaTime);

private:

    static constexpr float kGravity = -5.0f;
};