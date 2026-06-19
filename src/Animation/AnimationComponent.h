#pragma once

class Animation;
class Texture;

class AnimationComponent
{
public:
    void play(const Animation* animation);

    void update(float dt);

    const Texture* getTexture() const;

    const Animation* getCurrentAnimation() const;

    void reset();

private:
    const Animation* current = nullptr;

    int frameIndex = 0;
    float timer = 0.0f;
};