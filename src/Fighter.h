#pragma once

#include "FighterPhysicsData.h"
#include "FighterCombatData.h"

#include "Facing.h"
#include "FighterState.h"

class Fighter
{
public:
    Fighter();

    void applyDamage(int damage);

    FighterPhysicsData physics;
    FighterCombatData combat;

    Facing facing = Facing::Right;

    FighterState state = FighterState::Idle;

    bool crouching = false;

    static constexpr float MoveSpeed = 3.0f;
    static constexpr float JumpSpeed = 6.5f;
};