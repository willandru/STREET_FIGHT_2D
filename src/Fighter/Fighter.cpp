#include "Fighter.h"

Fighter::Fighter()
{
    physics.transform.x = 0.6f;
    physics.transform.y = 0.2f;

    physics.transform.width = 0.3f;
    physics.transform.height = 0.3f;

    combat.hurtbox.offsetX = 0.0f;
    combat.hurtbox.offsetY = 0.0f;

    combat.hurtbox.width = 0.3f;
    combat.hurtbox.height = 0.3f;

    combat.health = 100;

    physics.velocityX = 0.0f;
    physics.velocityY = 0.0f;

    physics.grounded = false;

    character = nullptr;

    crouching = false;

    facing = Facing::Right;

    state = FighterState::Idle;
}

void Fighter::applyDamage(int damage)
{
    combat.health -= damage;

    if (combat.health < 0)
    {
        combat.health = 0;
    }
}