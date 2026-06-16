#pragma once

#include "CombatTypes.h"

#include <vector>

struct FighterCombatData
{
    int health = 100;

    Hurtbox hurtbox;
    std::vector<Hitbox> hitboxes;
};