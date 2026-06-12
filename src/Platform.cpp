#include "Platform.h"

Platform::Platform(
    float x,
    float y,
    float width,
    float height)
{
    transform_.x = x;
    transform_.y = y;

    transform_.width = width;
    transform_.height = height;
}

const Transform& Platform::transform() const
{
    return transform_;
}

Transform& Platform::transform()
{
    return transform_;
}