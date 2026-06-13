#pragma once

#include "Match.h"
#include "Fighter.h"
#include "CombatTypes.h"

class CombatSystem
{
public:
    void update(Match& match);

private:
    void checkFighterPair(Fighter& a, Fighter& b);

    bool checkOverlap(
        float ax, float ay, float aw, float ah,
        float bx, float by, float bw, float bh);

    void processHit(Fighter& attacker, Fighter& victim, int damage);
};