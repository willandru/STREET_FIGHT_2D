#pragma once

#include "Animation.h"

struct FighterAnimationData
{
    Animation idle;

    Animation walkForward;
    Animation walkBackward;

    Animation jump;
    Animation crouch;

    Animation lightAttack;
    Animation heavyAttack;
};