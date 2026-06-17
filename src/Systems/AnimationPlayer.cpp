#include "AnimationPlayer.h"
#include "Animation.h"
#include "AnimationFrame.h"
#include "Texture.h"

void AnimationPlayer::play(const Animation* animation)
{
    if (current == animation)
        return;

    current = animation;
    frameIndex = 0;
    timer = 0.0f;
}

void AnimationPlayer::update(float dt)
{
    if (!current || current->frames.empty())
        return;

    timer += dt;

    const AnimationFrame& frame =
        current->frames[frameIndex];

    if (timer >= frame.duration)
    {
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
}

const Texture* AnimationPlayer::getTexture() const
{
    if (!current || current->frames.empty())
        return nullptr;

    return current->frames[frameIndex].texture;
}

void AnimationPlayer::reset()
{
    frameIndex = 0;
    timer = 0.0f;
}