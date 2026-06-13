#pragma once

#include "Transform.h"
#include "Facing.h"
#include "FighterState.h"

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

    bool crouching() const;
    bool& crouching();

    Facing facing() const;
    Facing& facing();

    FighterState state() const;
    FighterState& state();

    void updateState();

    static constexpr float MoveSpeed = 3.0f;
    static constexpr float JumpSpeed = 6.5f;

private:
    Transform transform_;

    float velocityX_ = 0.0f;
    float velocityY_ = 0.0f;

    bool grounded_ = false;

    bool crouching_ = false;


    Facing facing_ = Facing::Right;

    FighterState state_ = FighterState::Idle;
};