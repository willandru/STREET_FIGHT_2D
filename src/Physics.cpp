#include "Physics.h"

namespace
{
    void updateFighter(
        Fighter& fighter,
        float deltaTime,
        float gravity,
        float groundY)
    {
        Transform& transform =
            fighter.transform();

        fighter.grounded() = false;

        fighter.velocityY() +=
            gravity * deltaTime;

        transform.x +=
            fighter.velocityX() * deltaTime;

        transform.y +=
            fighter.velocityY() * deltaTime;

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
    }
}

void Physics::update(
    Match& match,
    float deltaTime)
{
    updateFighter(
        match.fighter1(),
        deltaTime,
        kGravity,
        kGroundY);

    updateFighter(
        match.fighter2(),
        deltaTime,
        kGravity,
        kGroundY);
}