#include "FighterStateMachine.h"
#include "Facing.h"
#include "Fighter.h"
#include "FighterCommand.h"
#include "FighterState.h"

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
    // WALK FORWARD / BACKWARD
    // =========================
    bool movingLeft  = cmd.moveLeft;
    bool movingRight = cmd.moveRight;

    if (movingLeft || movingRight)
    {
        bool forward =
            (movingRight && fighter.facing == Facing::Right) ||
            (movingLeft  && fighter.facing == Facing::Left);

        fighter.state =
            forward
            ? FighterState::WalkingForward
            : FighterState::WalkingBackward;

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