#pragma once

#include "Fighter.h"
#include "Stage.h"

class Match
{
public:

    Match();

    const Fighter& fighter1() const;
    Fighter& fighter1();

    const Fighter& fighter2() const;
    Fighter& fighter2();

    const Stage& stage() const;
    Stage& stage();

private:

    Stage stage_;

    Fighter fighter1_;
    Fighter fighter2_;
};