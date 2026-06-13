#pragma once

#include "Match.h"
#include "FighterCommand.h"

class Physics
{
public:

    void update(
        Match& match,
        float deltaTime,
        const FighterCommand& p1,
        const FighterCommand& p2);

private:

    void resolveFighterCollision(
        Fighter& fighter1,
        Fighter& fighter2);

    static constexpr float kGravity = -5.0f;
};