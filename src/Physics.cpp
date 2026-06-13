#include "Physics.h"

namespace
{
    void updateFighter(
        Fighter& fighter,
        float deltaTime,
        float gravity,
        float groundY,
        float leftBoundary,
        float rightBoundary)
    {
        Transform& transform =
            fighter.transform();

        fighter.grounded() = false;

        // =========================
        // GRAVITY
        // =========================

        fighter.velocityY() +=
            gravity * deltaTime;

        // =========================
        // MOVEMENT
        // =========================

        transform.x +=
            fighter.velocityX() * deltaTime;

        transform.y +=
            fighter.velocityY() * deltaTime;

        // =========================
        // GROUND COLLISION
        // =========================

        const float fighterBottom =
            transform.y -
            transform.height * 0.5f;

        if (fighterBottom <= groundY)
        {
            transform.y =
                groundY +
                transform.height * 0.5f;

            fighter.velocityY() = 0.0f;

            fighter.grounded() = true;
        }

        // =========================
        // STAGE BOUNDARIES
        // =========================

        const float fighterLeft =
            transform.x -
            transform.width * 0.5f;

        const float fighterRight =
            transform.x +
            transform.width * 0.5f;

        if (fighterLeft < leftBoundary)
        {
            transform.x =
                leftBoundary +
                transform.width * 0.5f;
        }

        if (fighterRight > rightBoundary)
        {
            transform.x =
                rightBoundary -
                transform.width * 0.5f;
        }
    }
}

void Physics::update(
    Match& match,
    float deltaTime)
{
    const float groundY =
        match.stage().groundY();

    const float leftBoundary =
        match.stage().leftBoundary();

    const float rightBoundary =
        match.stage().rightBoundary();

    updateFighter(
        match.fighter1(),
        deltaTime,
        kGravity,
        groundY,
        leftBoundary,
        rightBoundary);

    updateFighter(
        match.fighter2(),
        deltaTime,
        kGravity,
        groundY,
        leftBoundary,
        rightBoundary);

    // =========================
    // FACING UPDATE
    // =========================

    if (match.fighter1().transform().x <
        match.fighter2().transform().x)
    {
        match.fighter1().facing() =
            Facing::Right;

        match.fighter2().facing() =
            Facing::Left;
    }
    else
    {
        match.fighter1().facing() =
            Facing::Left;

        match.fighter2().facing() =
            Facing::Right;
    }
}