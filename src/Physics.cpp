#include "Physics.h"

void Physics::update(
    Level& level,
    float deltaTime)
{
    Player& player =
        level.player();

    Transform& playerTransform =
        player.transform();

    // =========================
    // RESET GROUNDED STATE
    // =========================
    player.grounded() = false;

    // =========================
    // GRAVITY
    // =========================
    player.velocityY() +=
        kGravity * deltaTime;

    // =========================
    // HORIZONTAL MOVEMENT
    // =========================
    playerTransform.x +=
        player.velocityX() * deltaTime;

    // =========================
    // VERTICAL MOVEMENT
    // =========================
    playerTransform.y +=
        player.velocityY() * deltaTime;

    // =========================
    // COLLISION CHECK
    // =========================
    for (const Platform& platform : level.platforms())
    {
        const Transform& platformTransform =
            platform.transform();

        if (!intersects(
                playerTransform,
                platformTransform))
        {
            continue;
        }

        // Only resolve when falling
        if (player.velocityY() < 0.0f)
        {
            const float platformTop =
                platformTransform.y +
                platformTransform.height * 0.5f;

            playerTransform.y =
                platformTop +
                playerTransform.height * 0.5f;

            player.velocityY() = 0.0f;

            player.grounded() = true;
        }
    }
}

bool Physics::intersects(
    const Transform& a,
    const Transform& b) const
{
    const float aLeft =
        a.x - a.width * 0.5f;

    const float aRight =
        a.x + a.width * 0.5f;

    const float aBottom =
        a.y - a.height * 0.5f;

    const float aTop =
        a.y + a.height * 0.5f;

    const float bLeft =
        b.x - b.width * 0.5f;

    const float bRight =
        b.x + b.width * 0.5f;

    const float bBottom =
        b.y - b.height * 0.5f;

    const float bTop =
        b.y + b.height * 0.5f;

    return
        aLeft < bRight &&
        aRight > bLeft &&
        aBottom < bTop &&
        aTop > bBottom;
}