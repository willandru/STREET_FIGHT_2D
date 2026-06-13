#pragma once

#include "Input.h"
#include "Fighter.h"

class FighterController
{
public:
    void update(Fighter& fighter, bool isPlayer1);
};