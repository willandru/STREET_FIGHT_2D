#include "Physics.h"

#include "Facing.h"
#include "Fighter.h"
#include "Stage.h"
#include "Transform.h"
#include "CharacterData.h"

namespace
{
void updateFighter(
    Fighter& fighter,
    const FighterCommand& cmd,
    float deltaTime,
    float gravity,
    float groundY,
    float leftBoundary,
    float rightBoundary)
{
    Transform& t =
        fighter.physics.transform;

    // =========================
    // INPUT DE MOVIMIENTO
    // =========================

    fighter.crouching =
        cmd.crouch;

    fighter.physics.velocityX =
        0.0f;

    if (fighter.character == nullptr)
    {
        return;
    }

    if (cmd.moveLeft)
    {
        fighter.physics.velocityX =
            -fighter.character->moveSpeed;
    }

    if (cmd.moveRight)
    {
        fighter.physics.velocityX =
            fighter.character->moveSpeed;
    }

    // =========================
    // SALTO
    // =========================

    const bool wasGrounded =
        fighter.physics.grounded;

    if (cmd.jump && wasGrounded)
    {
        fighter.physics.velocityY =
            fighter.character->jumpSpeed;
    }

    // =========================
    // GRAVEDAD
    // =========================

    fighter.physics.velocityY +=
        gravity * deltaTime;

    // =========================
    // INTEGRACIÓN
    // =========================

    t.x +=
        fighter.physics.velocityX *
        deltaTime;

    t.y +=
        fighter.physics.velocityY *
        deltaTime;

    // =========================
    // COLISIÓN CON SUELO
    // =========================

    const float halfH =
        t.height * 0.5f;

    const float bottom =
        t.y - halfH;

    if (bottom <= groundY)
    {
        t.y =
            groundY + halfH;

        fighter.physics.velocityY =
            0.0f;

        fighter.physics.grounded =
            true;
    }
    else
    {
        fighter.physics.grounded =
            false;
    }

    // =========================
    // LÍMITES DEL STAGE
    // =========================

    const float halfW =
        t.width * 0.5f;

    if (t.x - halfW < leftBoundary)
    {
        t.x =
            leftBoundary + halfW;
    }

    if (t.x + halfW > rightBoundary)
    {
        t.x =
            rightBoundary - halfW;
    }
}
}

void Physics::update(
    Match& match,
    float deltaTime,
    const FighterCommand& p1,
    const FighterCommand& p2)
{
    const float groundY =
        match.stage().groundY();

    const float leftBoundary =
        match.stage().leftBoundary();

    const float rightBoundary =
        match.stage().rightBoundary();

    updateFighter(
        match.fighter1(),
        p1,
        deltaTime,
        kGravity,
        groundY,
        leftBoundary,
        rightBoundary);

    updateFighter(
        match.fighter2(),
        p2,
        deltaTime,
        kGravity,
        groundY,
        leftBoundary,
        rightBoundary);

    // =========================
    // FACING
    // =========================

    Fighter& fighter1 =
        match.fighter1();

    Fighter& fighter2 =
        match.fighter2();

    if (fighter1.physics.transform.x <
        fighter2.physics.transform.x)
    {
        fighter1.facing =
            Facing::Right;

        fighter2.facing =
            Facing::Left;
    }
    else
    {
        fighter1.facing =
            Facing::Left;

        fighter2.facing =
            Facing::Right;
    }
}