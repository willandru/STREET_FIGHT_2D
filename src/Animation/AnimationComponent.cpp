#include "AnimationComponent.h"
#include "Animation.h"
#include "AnimationFrame.h"
#include "Texture.h"

void AnimationComponent::play(const Animation* animation)
{
    if (!animation)
        return;

    if (current == animation)
        return;

    current = animation;
    frameIndex = 0;
    timer = 0.0f;
}

void AnimationComponent::update(float dt)
{
    if (!current || current->frames.empty())
        return;

    timer += dt;

    const AnimationFrame& frame =
        current->frames[frameIndex];

    if (timer < frame.duration)
        return;

    timer = 0.0f;
    frameIndex++;

    if (frameIndex >= (int)current->frames.size())
    {
        if (current->loop)
            frameIndex = 0;
        else
            frameIndex = (int)current->frames.size() - 1;
    }
}

const Texture* AnimationComponent::getTexture() const
{
    if (!current || current->frames.empty())
        return nullptr;

    return current->frames[frameIndex].texture;
}

const Animation* AnimationComponent::getCurrentAnimation() const
{
    return current;
}

void AnimationComponent::reset()
{
    frameIndex = 0;
    timer = 0.0f;
}