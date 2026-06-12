#pragma once

#include "Level.h"

class Physics
{
public:
    void update(
        Level& level,
        float deltaTime);

private:
    bool intersects(
        const Transform& a,
        const Transform& b) const;

    static constexpr float kGravity = -5.0f;
};