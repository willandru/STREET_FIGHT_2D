#pragma once

struct FighterCommand
{
    bool moveLeft = false;
    bool moveRight = false;
    bool jump = false;
    bool crouch = false;

    bool lightAttack = false;
    bool heavyAttack = false;
};