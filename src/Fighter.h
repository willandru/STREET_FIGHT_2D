#pragma once

#include "Transform.h"

class Fighter
{
public:
    Fighter();

    const Transform& transform() const;
    Transform& transform();

    float velocityX() const;
    float& velocityX();

    float velocityY() const;
    float& velocityY();

    bool grounded() const;
    bool& grounded();

    static constexpr float MoveSpeed = 3.0f;
    static constexpr float JumpSpeed = 6.5f;

private:
    Transform transform_;

    float velocityX_ = 0.0f;
    float velocityY_ = 0.0f;

    bool grounded_ = false;
};