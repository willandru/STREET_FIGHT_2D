#pragma once

#include "Fighter.h"

class Match
{
public:

    Match();

    const Fighter& fighter1() const;
    Fighter& fighter1();

    const Fighter& fighter2() const;
    Fighter& fighter2();

private:

    Fighter fighter1_;
    Fighter fighter2_;
};