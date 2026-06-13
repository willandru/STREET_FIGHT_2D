#pragma once

struct Hitbox
{
    float offsetX = 0.0f;
    float offsetY = 0.0f;
    float width = 0.0f;
    float height = 0.0f;

    int activeFrameStart = 0;
    int activeFrameEnd = 0;
    int damage = 0;
};

struct Hurtbox
{
    float offsetX = 0.0f;
    float offsetY = 0.0f;
    float width = 0.0f;
    float height = 0.0f;
};