#pragma once

#include "Fighter.h"
#include "FighterCommand.h"

class FighterStateMachine
{
public:
    void update(
        Fighter& fighter,
        const FighterCommand& cmd);

    bool isAttackActive(
        const Fighter& fighter) const;
};