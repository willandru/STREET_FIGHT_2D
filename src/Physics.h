#pragma once

#include "Match.h"
#include "FighterCommand.h"
#include "Fighter.h"

class Physics
{
public:
    void update(
        Match& match,
        float deltaTime,
        const FighterCommand& p1,
        const FighterCommand& p2);

private:
    static constexpr float kGravity = -5.0f;
};  