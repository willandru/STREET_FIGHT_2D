#pragma once

class Texture;

struct AnimationFrame
{
    const Texture* texture = nullptr;
    float duration = 0.1f;
};