#include "FighterStateMachine.h"

void FighterStateMachine::update(
    Fighter& fighter,
    const FighterCommand& cmd)
{
    // =========================
    // INPUT STATE (CROUCH)
    // =========================
    fighter.crouching = cmd.crouch;

    // =========================
    // ATTACKS (HIGHEST PRIORITY)
    // =========================
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

    // =========================
    // AIRBORNE
    // =========================
    if (!fighter.physics.grounded)
    {
        fighter.state = FighterState::Jumping;
        return;
    }

    // =========================
    // CROUCHING
    // =========================
    if (fighter.crouching)
    {
        fighter.state = FighterState::Crouching;
        return;
    }

    // =========================
    // WALKING
    // =========================
    if (fighter.physics.velocityX != 0.0f)
    {
        fighter.state = FighterState::Walking;
        return;
    }

    // =========================
    // IDLE DEFAULT
    // =========================
    fighter.state = FighterState::Idle;
}

bool FighterStateMachine::isAttackActive(
    const Fighter& fighter) const
{
    return
        fighter.state == FighterState::LightAttack ||
        fighter.state == FighterState::HeavyAttack;
}