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
        Animation walkForward;
        Animation walkBackward;

        // =========================
        // IDLE
        // =========================
        idle.frames.push_back({ &assets.get("ryu_idle_1"), 0.12f });
        idle.frames.push_back({ &assets.get("ryu_idle_2"), 0.12f });
        idle.frames.push_back({ &assets.get("ryu_idle_3"), 0.12f });
        idle.frames.push_back({ &assets.get("ryu_idle_4"), 0.12f });
        idle.loop = true;

        c.animations.idle = idle;

        // =========================
        // WALK FORWARD (derecha por defecto)
        // =========================
        walkForward.frames.push_back({ &assets.get("ryu_walk_r_1"), 0.10f });
        walkForward.frames.push_back({ &assets.get("ryu_walk_r_2"), 0.10f });
        walkForward.frames.push_back({ &assets.get("ryu_walk_r_3"), 0.10f });
        walkForward.frames.push_back({ &assets.get("ryu_walk_r_4"), 0.10f });
        walkForward.loop = true;

        c.animations.walkForward = walkForward;

        // =========================
        // WALK BACKWARD (puedes reutilizar o invertir luego)
        // =========================
        walkBackward = walkForward; 
        walkBackward.loop = true;

        c.animations.walkBackward = walkBackward;

        // =========================
        // STATS
        // =========================
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
        Animation walkForward;
        Animation walkBackward;

        idle.frames.push_back({ &assets.get("ken_idle_1"), 0.12f });
        idle.frames.push_back({ &assets.get("ken_idle_2"), 0.12f });
        idle.frames.push_back({ &assets.get("ken_idle_3"), 0.12f });
        idle.frames.push_back({ &assets.get("ken_idle_4"), 0.12f });
        idle.loop = true;

        c.animations.idle = idle;

        walkForward = idle; // placeholder temporal
        walkBackward = idle;

        c.animations.walkForward = walkForward;
        c.animations.walkBackward = walkBackward;

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
        Animation walkForward;
        Animation walkBackward;

        idle.frames.push_back({ &assets.get("maki_idle_1"), 0.12f });
        idle.frames.push_back({ &assets.get("maki_idle_2"), 0.12f });
        idle.frames.push_back({ &assets.get("maki_idle_3"), 0.12f });
        idle.frames.push_back({ &assets.get("maki_idle_4"), 0.12f });
        idle.loop = true;

        c.animations.idle = idle;

        walkForward = idle;
        walkBackward = idle;

        c.animations.walkForward = walkForward;
        c.animations.walkBackward = walkBackward;

        c.moveSpeed = 3.8f;
        c.jumpSpeed = 7.5f;
        c.width = 0.28f;
        c.height = 0.32f;
        c.maxHealth = 90;

        return c;
    }
}