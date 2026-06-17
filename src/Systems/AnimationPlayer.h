#pragma once

class Animation;
class Texture;

class AnimationPlayer
{
public:
    void play(const Animation* animation);

    void update(float dt);

    const Texture* getTexture() const;

    void reset();

private:
    const Animation* current = nullptr;

    int frameIndex = 0;
    float timer = 0.0f;
};