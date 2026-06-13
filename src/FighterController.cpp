#include "FighterController.h"
#include "Input.h"

FighterCommand FighterController::build(bool isPlayer1)
{
    FighterCommand cmd;

    if (isPlayer1)
    {
        cmd.moveLeft = Input::IsKeyDown(Key::A);
        cmd.moveRight = Input::IsKeyDown(Key::D);
        cmd.jump = Input::IsKeyDown(Key::W);
        cmd.crouch = Input::IsKeyDown(Key::S);

        cmd.lightAttack = Input::IsKeyDown(Key::Space);
        cmd.heavyAttack = false;
    }
    else
    {
        cmd.moveLeft = Input::IsKeyDown(Key::J);
        cmd.moveRight = Input::IsKeyDown(Key::L);
        cmd.jump = Input::IsKeyDown(Key::I);
        cmd.crouch = Input::IsKeyDown(Key::K);

        cmd.lightAttack = Input::IsKeyDown(Key::U);
        cmd.heavyAttack = false;
    }

    return cmd;
}