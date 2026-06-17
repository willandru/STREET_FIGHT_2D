#pragma once

#include "FighterAnimationData.h"

struct CharacterData
{
    FighterAnimationData animations;

    float moveSpeed = 3.0f;
    float jumpSpeed = 6.5f;

    float width = 0.3f;
    float height = 0.3f;

    int maxHealth = 100;
};