#pragma once

class Texture;

struct AnimationFrame
{
    Texture* texture = nullptr;

    float duration = 0.1f;
};