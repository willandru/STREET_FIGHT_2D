#include "Fighter.h"

Fighter::Fighter()
{
    transform_.x = 0.6f;
    transform_.y = 0.20f;

    transform_.width = 0.30f;
    transform_.height = 0.30f;
}

const Transform& Fighter::transform() const
{
    return transform_;
}

Transform& Fighter::transform()
{
    return transform_;
}

float Fighter::velocityX() const
{
    return velocityX_;
}

float& Fighter::velocityX()
{
    return velocityX_;
}

float Fighter::velocityY() const
{
    return velocityY_;
}

float& Fighter::velocityY()
{
    return velocityY_;
}

bool Fighter::grounded() const
{
    return grounded_;
}

bool& Fighter::grounded()
{
    return grounded_;
}

Facing Fighter::facing() const
{
    return facing_;
}

Facing& Fighter::facing()
{
    return facing_;
}