#include "Physics.h"

#include "Facing.h"
#include "Fighter.h"
#include "Stage.h"
#include "Transform.h"
#include "CharacterData.h"
#include "Match.h"
#include "FighterCommand.h"

namespace
{
void updateFighter(
    Fighter& fighter,
    const FighterCommand& cmd,
    float dt,
    float gravity,
    float groundY,
    float leftBoundary,
    float rightBoundary)
{
    Transform& t = fighter.physics.transform;

    if (!fighter.character)
        return;

    fighter.crouching = cmd.crouch;

    // =====================================================
    // INPUT RAW (ABSOLUTO, NO RELATIVO A FACING)
    // =====================================================
    float input = 0.0f;

    if (cmd.moveLeft)  input -= 1.0f;
    if (cmd.moveRight) input += 1.0f;

    // =====================================================
    // MOVIMIENTO DIRECTO
    // =====================================================
    fighter.physics.velocityX =
        input * fighter.character->moveSpeed;

    // =====================================================
    // JUMP
    // =====================================================
    if (cmd.jump && fighter.physics.grounded)
    {
        fighter.physics.velocityY =
            fighter.character->jumpSpeed;
    }

    // =====================================================
    // GRAVITY
    // =====================================================
    fighter.physics.velocityY += gravity * dt;

    // =====================================================
    // INTEGRATION
    // =====================================================
    t.x += fighter.physics.velocityX * dt;
    t.y += fighter.physics.velocityY * dt;

    // =====================================================
    // GROUND COLLISION
    // =====================================================
    const float halfH = t.height * 0.5f;
    const float bottom = t.y - halfH;

    if (bottom <= groundY)
    {
        t.y = groundY + halfH;
        fighter.physics.velocityY = 0.0f;
        fighter.physics.grounded = true;
    }
    else
    {
        fighter.physics.grounded = false;
    }

    // =====================================================
    // STAGE LIMITS
    // =====================================================
    const float halfW = t.width * 0.5f;

    if (t.x - halfW < leftBoundary)
        t.x = leftBoundary + halfW;

    if (t.x + halfW > rightBoundary)
        t.x = rightBoundary - halfW;
}
}

void Physics::update(
    Match& match,
    float dt,
    const FighterCommand& p1,
    const FighterCommand& p2)
{
    const float groundY = match.stage().groundY();
    const float leftBoundary = match.stage().leftBoundary();
    const float rightBoundary = match.stage().rightBoundary();

    updateFighter(match.fighter1(), p1, dt, kGravity, groundY, leftBoundary, rightBoundary);
    updateFighter(match.fighter2(), p2, dt, kGravity, groundY, leftBoundary, rightBoundary);

    // =====================================================
    // FACING SOLO VISUAL (NO IMPACTA INPUT NI STATE)
    // =====================================================
    Fighter& a = match.fighter1();
    Fighter& b = match.fighter2();

    if (a.physics.transform.x < b.physics.transform.x)
    {
        a.facing = Facing::Right;
        b.facing = Facing::Left;
    }
    else
    {
        a.facing = Facing::Left;
        b.facing = Facing::Right;
    }
}