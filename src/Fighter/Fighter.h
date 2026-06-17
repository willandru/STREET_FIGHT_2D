#pragma once

#include "FighterPhysicsData.h"
#include "FighterCombatData.h"

#include "CharacterData.h"
#include "Facing.h"
#include "FighterState.h"

class Fighter
{
public:
    Fighter();

    void applyDamage(int damage);

    FighterPhysicsData physics;
    FighterCombatData combat;

    CharacterData* character = nullptr;

    Facing facing = Facing::Right;

    FighterState state = FighterState::Idle;

    bool crouching = false;
};