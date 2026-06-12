#include "Player.h"

Player::Player()
{
    transform_.x = 0.6f;
    transform_.y = 0.20f;

    transform_.width = 0.30f;
    transform_.height = 0.30f;
}

const Transform& Player::transform() const
{
    return transform_;
}

Transform& Player::transform()
{
    return transform_;
}

float Player::velocityX() const
{
    return velocityX_;
}

float& Player::velocityX()
{
    return velocityX_;
}

float Player::velocityY() const
{
    return velocityY_;
}

float& Player::velocityY()
{
    return velocityY_;
}

bool Player::grounded() const
{
    return grounded_;
}

bool& Player::grounded()
{
    return grounded_;
}