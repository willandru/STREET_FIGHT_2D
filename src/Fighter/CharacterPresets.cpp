#include "CharacterPresets.h"
#include "AssetManager.h"
#include "Animation.h"
#include "AnimationFrame.h"

namespace Characters
{
    CharacterData createRyu(const AssetManager& assets)
    {
        CharacterData c;

        Animation idle;

        idle.frames.push_back({ &assets.get("ryu_idle_1"), 0.12f });
        idle.frames.push_back({ &assets.get("ryu_idle_2"), 0.12f });
        idle.frames.push_back({ &assets.get("ryu_idle_3"), 0.12f });
        idle.frames.push_back({ &assets.get("ryu_idle_4"), 0.12f });

        idle.loop = true;

        c.animations.idle = idle;

        c.moveSpeed = 3.0f;
        c.jumpSpeed = 6.5f;
        c.width = 0.30f;
        c.height = 0.30f;
        c.maxHealth = 100;

        return c;
    }

    CharacterData createKen(const AssetManager& assets)
    {
        CharacterData c;

        Animation idle;

        idle.frames.push_back({ &assets.get("ken_idle_1"), 0.12f });
        idle.frames.push_back({ &assets.get("ken_idle_2"), 0.12f });
        idle.frames.push_back({ &assets.get("ken_idle_3"), 0.12f });
        idle.frames.push_back({ &assets.get("ken_idle_4"), 0.12f });

        idle.loop = true;

        c.animations.idle = idle;

        c.moveSpeed = 3.2f;
        c.jumpSpeed = 7.0f;
        c.width = 0.30f;
        c.height = 0.30f;
        c.maxHealth = 100;

        return c;
    }

    CharacterData createMaki(const AssetManager& assets)
    {
        CharacterData c;

        Animation idle;

        idle.frames.push_back({ &assets.get("maki_idle_1"), 0.12f });
        idle.frames.push_back({ &assets.get("maki_idle_2"), 0.12f });
        idle.frames.push_back({ &assets.get("maki_idle_3"), 0.12f });
        idle.frames.push_back({ &assets.get("maki_idle_4"), 0.12f });

        idle.loop = true;

        c.animations.idle = idle;

        c.moveSpeed = 3.8f;
        c.jumpSpeed = 7.5f;
        c.width = 0.28f;
        c.height = 0.32f;
        c.maxHealth = 90;

        return c;
    }
}