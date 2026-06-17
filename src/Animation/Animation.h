#pragma once

#include <vector>

#include "AnimationFrame.h"

struct Animation
{
    std::vector<AnimationFrame> frames;

    bool loop = true;
};