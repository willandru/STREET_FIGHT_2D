#include "FighterController.h"

void FighterController::update(Fighter& fighter, bool isPlayer1)
{
    fighter.velocityX() = 0.0f;
    fighter.crouching() = false;

    if (isPlayer1)
    {
        if (Input::IsKeyDown(Key::A))
            fighter.velocityX() = -Fighter::MoveSpeed;

        if (Input::IsKeyDown(Key::D))
            fighter.velocityX() = Fighter::MoveSpeed;

        if (Input::IsKeyDown(Key::W) && fighter.grounded())
            fighter.velocityY() = Fighter::JumpSpeed;

        if (Input::IsKeyDown(Key::S))
            fighter.crouching() = true;
    }
    else
    {
        if (Input::IsKeyDown(Key::J))
            fighter.velocityX() = -Fighter::MoveSpeed;

        if (Input::IsKeyDown(Key::L))
            fighter.velocityX() = Fighter::MoveSpeed;

        if (Input::IsKeyDown(Key::I) && fighter.grounded())
            fighter.velocityY() = Fighter::JumpSpeed;

        if (Input::IsKeyDown(Key::K))
            fighter.crouching() = true;
    }
}