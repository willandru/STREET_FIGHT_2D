#include "AnimationSystem.h"

#include "Fighter.h"
#include "Animation.h"
#include "CharacterData.h"
#include "FighterState.h"

void AnimationSystem::update(
    Fighter& fighter,
    float deltaTime)
{
    if (!fighter.character)
    {
        return;
    }

    // =========================
    // 1. SELECT ANIMATION FROM STATE
    // =========================

    const Animation* targetAnimation = nullptr;

    switch (fighter.state)
    {
        case FighterState::Idle:
            targetAnimation =
                &fighter.character->animations.idle;
            break;

        case FighterState::Walking:
            targetAnimation =
                &fighter.character->animations.idle;
            break;

        case FighterState::Jumping:
            targetAnimation =
                &fighter.character->animations.idle;
            break;

        case FighterState::Crouching:
            targetAnimation =
                &fighter.character->animations.idle;
            break;

        case FighterState::LightAttack:
            targetAnimation =
                &fighter.character->animations.idle;
            break;

        case FighterState::HeavyAttack:
            targetAnimation =
                &fighter.character->animations.idle;
            break;

        default:
            targetAnimation =
                &fighter.character->animations.idle;
            break;
    }

    // =========================
    // 2. SWITCH ANIMATION IF NEEDED
    // =========================

    if (fighter.currentAnimation != targetAnimation)
    {
        fighter.currentAnimation = targetAnimation;
        fighter.currentFrame = 0;
        fighter.animationTimer = 0.0f;
    }

    if (!fighter.currentAnimation ||
        fighter.currentAnimation->frames.empty())
    {
        return;
    }

    // =========================
    // 3. FRAME TIMING
    // =========================

    fighter.animationTimer += deltaTime;

    const AnimationFrame& frame =
        fighter.currentAnimation->frames[fighter.currentFrame];

    if (fighter.animationTimer < frame.duration)
    {
        return;
    }

    fighter.animationTimer = 0.0f;
    fighter.currentFrame++;

    if (fighter.currentFrame >=
        (int)fighter.currentAnimation->frames.size())
    {
        if (fighter.currentAnimation->loop)
        {
            fighter.currentFrame = 0;
        }
        else
        {
            fighter.currentFrame =
                (int)fighter.currentAnimation->frames.size() - 1;
        }
    }
}