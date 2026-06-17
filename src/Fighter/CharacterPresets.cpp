#include "CharacterPresets.h"

#include "Texture.h"

namespace Characters
{
    CharacterData createRyu(
        Texture& idle)
    {
        CharacterData c;

        c.idleTexture = &idle;

        c.moveSpeed = 3.0f;
        c.jumpSpeed = 6.5f;

        c.width = 0.30f;
        c.height = 0.30f;

        c.maxHealth = 100;

        return c;
    }

    CharacterData createKen(
        Texture& idle)
    {
        CharacterData c;

        c.idleTexture = &idle;

        c.moveSpeed = 3.2f;
        c.jumpSpeed = 7.0f;

        c.width = 0.30f;
        c.height = 0.30f;

        c.maxHealth = 100;

        return c;
    }

    CharacterData createMaki(
        Texture& idle)
    {
        CharacterData c;

        c.idleTexture = &idle;

        c.moveSpeed = 3.8f;
        c.jumpSpeed = 7.5f;

        c.width = 0.28f;
        c.height = 0.32f;

        c.maxHealth = 90;

        return c;
    }
}