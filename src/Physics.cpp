#include "Physics.h"
#include "Fighter.h"
#include "Transform.h"
#include "Stage.h"

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
    Transform& transform = fighter.transform();

    fighter.grounded() = false;
    fighter.crouching() = cmd.crouch;

    fighter.velocityX() = 0.0f;

    if (cmd.moveLeft)
        fighter.velocityX() = -Fighter::MoveSpeed;

    if (cmd.moveRight)
        fighter.velocityX() = Fighter::MoveSpeed;

    if (cmd.jump && fighter.grounded())
        fighter.velocityY() = Fighter::JumpSpeed;

    fighter.velocityY() += gravity * deltaTime;

    transform.x += fighter.velocityX() * deltaTime;
    transform.y += fighter.velocityY() * deltaTime;

    const float halfH = transform.height * 0.5f;
    const float bottom = transform.y - halfH;

    if (bottom <= groundY)
    {
        transform.y = groundY + halfH;
        fighter.velocityY() = 0.0f;
        fighter.grounded() = true;
    }

    const float halfW = transform.width * 0.5f;

    if (transform.x - halfW < leftBoundary)
        transform.x = leftBoundary + halfW;

    if (transform.x + halfW > rightBoundary)
        transform.x = rightBoundary - halfW;
}
}

void Physics::update(
    Match& match,
    float deltaTime,
    const FighterCommand& p1,
    const FighterCommand& p2)
{
    const float groundY = match.stage().groundY();
    const float leftBoundary = match.stage().leftBoundary();
    const float rightBoundary = match.stage().rightBoundary();

    updateFighter(match.fighter1(), p1, deltaTime, kGravity,
                  groundY, leftBoundary, rightBoundary);

    updateFighter(match.fighter2(), p2, deltaTime, kGravity,
                  groundY, leftBoundary, rightBoundary);

    if (match.fighter1().transform().x < match.fighter2().transform().x)
    {
        match.fighter1().facing() = Facing::Right;
        match.fighter2().facing() = Facing::Left;
    }
    else
    {
        match.fighter1().facing() = Facing::Left;
        match.fighter2().facing() = Facing::Right;
    }
}