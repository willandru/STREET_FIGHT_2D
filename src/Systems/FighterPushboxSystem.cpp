#include "FighterPushboxSystem.h"
#include "Match.h"
#include "Fighter.h"
#include <cmath>

namespace
{
float getHalfWidth(const Fighter& f)
{
    return f.physics.transform.width * 0.5f;
}

float getHalfHeight(const Fighter& f)
{
    return f.physics.transform.height * 0.5f;
}

void resolvePair(Fighter& a, Fighter& b)
{
    auto& ta = a.physics.transform;
    auto& tb = b.physics.transform;

    float dx = tb.x - ta.x;
    float dy = tb.y - ta.y;

    // =========================
    // FILTRO VERTICAL (ANTI BLOCK EN SALTO)
    // =========================
    float verticalThreshold =
        getHalfHeight(a) + getHalfHeight(b);

    if (std::abs(dy) > verticalThreshold)
        return;

    float minDist = getHalfWidth(a) + getHalfWidth(b);
    float overlap = minDist - std::abs(dx);

    if (overlap <= 0.0f)
        return;

    // separación estable
    float correction = overlap * 0.5f;

    if (dx > 0.0f)
    {
        ta.x -= correction;
        tb.x += correction;
    }
    else
    {
        ta.x += correction;
        tb.x -= correction;
    }
}
}

void FighterPushboxSystem::resolve(Match& match)
{
    Fighter& a = match.fighter1();
    Fighter& b = match.fighter2();

    resolvePair(a, b);
}