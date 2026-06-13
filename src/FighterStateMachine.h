#pragma once

#include "Fighter.h"
#include "FighterCommand.h"

class FighterStateMachine
{
public:
    void applyCommand(Fighter& fighter, const FighterCommand& cmd);
    void updateState(Fighter& fighter);
    bool isAttackActive(const Fighter& fighter);
};