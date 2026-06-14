#pragma once

#include "Match.h"
#include "CombatTypes.h"

class Fighter;
class FighterStateMachine;

class CombatSystem
{
public:
    void update(Match& match, FighterStateMachine& stateMachine);

private:
    void checkFighterPair(
        Fighter& a,
        Fighter& b,
        FighterStateMachine& stateMachine);

    bool checkOverlap(
        float ax, float ay, float aw, float ah,
        float bx, float by, float bw, float bh);

    void processHit(
        Fighter& attacker,
        Fighter& victim,
        int damage);
};