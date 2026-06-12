#pragma once

#include "Transform.h"

class Platform
{
public:
    Platform() = default;

    Platform(
        float x,
        float y,
        float width,
        float height);

    const Transform& transform() const;
    Transform& transform();

private:
    Transform transform_;
};