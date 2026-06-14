#include "Match.h"

Match::Match()
{
    fighter1_.physics.transform.x = -0.5f;
    fighter1_.physics.transform.y = -0.4f;

    fighter2_.physics.transform.x = 0.5f;
    fighter2_.physics.transform.y = -0.4f;
}

const Fighter& Match::fighter1() const
{
    return fighter1_;
}

Fighter& Match::fighter1()
{
    return fighter1_;
}

const Fighter& Match::fighter2() const
{
    return fighter2_;
}

Fighter& Match::fighter2()
{
    return fighter2_;
}

const Stage& Match::stage() const
{
    return stage_;
}

Stage& Match::stage()
{
    return stage_;
}