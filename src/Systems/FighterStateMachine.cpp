#include "FighterStateMachine.h"
#include "Fighter.h"
#include "FighterCommand.h"
#include "FighterState.h"

void FighterStateMachine::update(
    Fighter& fighter,
    const FighterCommand& cmd)
{
    fighter.crouching = cmd.crouch;

    // =====================================================
    // ATTACK PRIORITY
    // =====================================================
    if (cmd.lightAttack)
    {
        fighter.state = FighterState::LightAttack;
        return;
    }

    if (cmd.heavyAttack)
    {
        fighter.state = FighterState::HeavyAttack;
        return;
    }

    // =====================================================
    // AIRBORNE
    // =====================================================
    if (!fighter.physics.grounded)
    {
        fighter.state = FighterState::Jumping;
        return;
    }

    // =====================================================
    // CROUCH
    // =====================================================
    if (fighter.crouching)
    {
        fighter.state = FighterState::Crouching;
        return;
    }

    // =====================================================
    // WALK (SIMPLIFICADO)
    // =====================================================
    bool moving =
        cmd.moveLeft || cmd.moveRight;

    if (moving)
    {
        fighter.state = FighterState::Walking;
        return;
    }

    // =====================================================
    // IDLE
    // =====================================================
    fighter.state = FighterState::Idle;
}

bool FighterStateMachine::isAttackActive(
    const Fighter& fighter) const
{
    return
        fighter.state == FighterState::LightAttack ||
        fighter.state == FighterState::HeavyAttack;
}