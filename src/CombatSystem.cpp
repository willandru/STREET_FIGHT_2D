#include "CombatSystem.h"

#include "Fighter.h"
#include "FighterStateMachine.h"
#include "Transform.h"

void CombatSystem::update(
    Match& match,
    FighterStateMachine& stateMachine)
{
    checkFighterPair(
        match.fighter1(),
        match.fighter2(),
        stateMachine);
}

void CombatSystem::checkFighterPair(
    Fighter& a,
    Fighter& b,
    FighterStateMachine& stateMachine)
{
    const Transform& ta =
        a.physics.transform;

    const Transform& tb =
        b.physics.transform;

    const Hurtbox& ha =
        a.combat.hurtbox;

    const Hurtbox& hb =
        b.combat.hurtbox;

    float ax = ta.x + ha.offsetX;
    float ay = ta.y + ha.offsetY;

    float bx = tb.x + hb.offsetX;
    float by = tb.y + hb.offsetY;

    // =========================
    // A -> B
    // =========================

    if (stateMachine.isAttackActive(a))
    {
        for (const Hitbox& hit : a.combat.hitboxes)
        {
            float hx = ta.x + hit.offsetX;
            float hy = ta.y + hit.offsetY;

            if (checkOverlap(
                hx,
                hy,
                hit.width,
                hit.height,
                bx,
                by,
                hb.width,
                hb.height))
            {
                processHit(
                    a,
                    b,
                    hit.damage);

                return;
            }
        }
    }

    // =========================
    // B -> A
    // =========================

    if (stateMachine.isAttackActive(b))
    {
        for (const Hitbox& hit : b.combat.hitboxes)
        {
            float hx = tb.x + hit.offsetX;
            float hy = tb.y + hit.offsetY;

            if (checkOverlap(
                hx,
                hy,
                hit.width,
                hit.height,
                ax,
                ay,
                ha.width,
                ha.height))
            {
                processHit(
                    b,
                    a,
                    hit.damage);

                return;
            }
        }
    }
}

bool CombatSystem::checkOverlap(
    float ax,
    float ay,
    float aw,
    float ah,
    float bx,
    float by,
    float bw,
    float bh)
{
    const float leftA = ax - aw * 0.5f;
    const float rightA = ax + aw * 0.5f;
    const float topA = ay + ah * 0.5f;
    const float bottomA = ay - ah * 0.5f;

    const float leftB = bx - bw * 0.5f;
    const float rightB = bx + bw * 0.5f;
    const float topB = by + bh * 0.5f;
    const float bottomB = by - bh * 0.5f;

    if (rightA < leftB || rightB < leftA)
        return false;

    if (topA < bottomB || topB < bottomA)
        return false;

    return true;
}

void CombatSystem::processHit(
    Fighter& attacker,
    Fighter& victim,
    int damage)
{
    victim.combat.health -= damage;

    if (victim.combat.health < 0)
    {
        victim.combat.health = 0;
    }
}