#include "FighterStateMachine.h"

void FighterStateMachine::applyCommand(Fighter& fighter, const FighterCommand& cmd)
{
    if (fighter.state() == FighterState::LightAttack ||
        fighter.state() == FighterState::HeavyAttack)
        return;

    fighter.crouching() = cmd.crouch;

    if (cmd.lightAttack && fighter.state() == FighterState::Idle)
    {
        fighter.state() = FighterState::LightAttack;
    }

    if (cmd.heavyAttack && fighter.state() == FighterState::Idle)
    {
        fighter.state() = FighterState::HeavyAttack;
    }
}

void FighterStateMachine::updateState(Fighter& fighter)
{
    if (fighter.state() == FighterState::LightAttack ||
        fighter.state() == FighterState::HeavyAttack)
    {
        if (!fighter.grounded())
            fighter.state() = FighterState::Jumping;
        else
            fighter.state() = FighterState::Idle;

        return;
    }

    if (!fighter.grounded())
    {
        fighter.state() = FighterState::Jumping;
        return;
    }

    if (fighter.crouching())
    {
        fighter.state() = FighterState::Crouching;
        return;
    }

    if (fighter.velocityX() != 0.0f)
    {
        fighter.state() = FighterState::Walking;
        return;
    }

    fighter.state() = FighterState::Idle;
}

bool FighterStateMachine::isAttackActive(const Fighter& fighter)
{
    return fighter.state() == FighterState::LightAttack ||
           fighter.state() == FighterState::HeavyAttack;
}