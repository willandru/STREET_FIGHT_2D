#include "AnimationSystem.h"

#include "Fighter.h"
#include "Animation.h"
#include "CharacterData.h"
#include "FighterState.h"
#include "Facing.h"
#include "AnimationComponent.h"

void AnimationSystem::update(
    Fighter& fighter,
    float deltaTime)
{
    if (!fighter.character || !fighter.animation)
        return;

    const Animation* targetAnimation = nullptr;

    switch (fighter.state)
    {
        case FighterState::Idle:
            targetAnimation = &fighter.character->animations.idle;
            break;

        case FighterState::Walking:
        {
            bool movingRight = fighter.physics.velocityX > 0.01f;
            bool movingLeft  = fighter.physics.velocityX < -0.01f;

            bool forward =
                (movingRight && fighter.facing == Facing::Right) ||
                (movingLeft  && fighter.facing == Facing::Left);

            targetAnimation =
                forward
                ? &fighter.character->animations.walkForward
                : &fighter.character->animations.walkBackward;

            break;
        }

        case FighterState::Jumping:
            targetAnimation = &fighter.character->animations.jump;
            break;

        case FighterState::Crouching:
            targetAnimation = &fighter.character->animations.crouch;
            break;

        case FighterState::LightAttack:
            targetAnimation = &fighter.character->animations.lightAttack;
            break;

        case FighterState::HeavyAttack:
            targetAnimation = &fighter.character->animations.heavyAttack;
            break;

        default:
            targetAnimation = &fighter.character->animations.idle;
            break;
    }

    // ================================
    // ONLY CHANGE IF DIFFERENT
    // ================================
    if (fighter.animation->getCurrentAnimation() != targetAnimation)
    {
        fighter.animation->play(targetAnimation);
    }
}