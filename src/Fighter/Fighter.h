#pragma once

#include "FighterPhysicsData.h"
#include "FighterCombatData.h"

#include "CharacterData.h"
#include "Facing.h"
#include "FighterState.h"

struct Animation;

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

    // =========================
    // ANIMATION
    // =========================

    const Animation* currentAnimation = nullptr;

    int currentFrame = 0;

    float animationTimer = 0.0f;
};