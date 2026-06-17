#include "CharacterPresets.h"

#include "Texture.h"
#include "Animation.h"
#include "AnimationFrame.h"

namespace Characters
{
    CharacterData createRyu(
        Texture& idle1,
        Texture& idle2,
        Texture& idle3,
        Texture& idle4)
    {
        CharacterData c;

        Animation idleAnim;

        idleAnim.frames.push_back({ &idle1, 0.12f });
        idleAnim.frames.push_back({ &idle2, 0.12f });
        idleAnim.frames.push_back({ &idle3, 0.12f });
        idleAnim.frames.push_back({ &idle4, 0.12f });

        idleAnim.loop = true;

        c.animations.idle = idleAnim;

        c.moveSpeed = 3.0f;
        c.jumpSpeed = 6.5f;

        c.width = 0.30f;
        c.height = 0.30f;

        c.maxHealth = 100;

        return c;
    }

    CharacterData createKen(
        Texture& idle1,
        Texture& idle2,
        Texture& idle3,
        Texture& idle4)
    {
        CharacterData c;

        Animation idleAnim;

        idleAnim.frames.push_back({ &idle1, 0.12f });
        idleAnim.frames.push_back({ &idle2, 0.12f });
        idleAnim.frames.push_back({ &idle3, 0.12f });
        idleAnim.frames.push_back({ &idle4, 0.12f });

        idleAnim.loop = true;

        c.animations.idle = idleAnim;

        c.moveSpeed = 3.2f;
        c.jumpSpeed = 7.0f;

        c.width = 0.30f;
        c.height = 0.30f;

        c.maxHealth = 100;

        return c;
    }

    CharacterData createMaki(
        Texture& idle1,
        Texture& idle2,
        Texture& idle3,
        Texture& idle4)
    {
        CharacterData c;

        Animation idleAnim;

        idleAnim.frames.push_back({ &idle1, 0.12f });
        idleAnim.frames.push_back({ &idle2, 0.12f });
        idleAnim.frames.push_back({ &idle3, 0.12f });
        idleAnim.frames.push_back({ &idle4, 0.12f });

        idleAnim.loop = true;

        c.animations.idle = idleAnim;

        c.moveSpeed = 3.8f;
        c.jumpSpeed = 7.5f;

        c.width = 0.28f;
        c.height = 0.32f;

        c.maxHealth = 90;

        return c;
    }
}