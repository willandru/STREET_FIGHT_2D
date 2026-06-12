#pragma once

#include "Platform.h"
#include "Player.h"

#include <vector>

class Level
{
public:
    Level();

    const Player& player() const;
    Player& player();

    const std::vector<Platform>& platforms() const;
    std::vector<Platform>& platforms();

private:
    Player player_;

    std::vector<Platform> platforms_;
};