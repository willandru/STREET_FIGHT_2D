#pragma once

class Texture;

struct CharacterData
{
    Texture* idleTexture = nullptr;

    Texture* walkTexture = nullptr;
    Texture* jumpTexture = nullptr;
    Texture* crouchTexture = nullptr;

    Texture* lightPunchTexture = nullptr;
    Texture* heavyPunchTexture = nullptr;

    Texture* lightKickTexture = nullptr;
    Texture* heavyKickTexture = nullptr;

    Texture* hurtTexture = nullptr;
    Texture* blockTexture = nullptr;

    Texture* winTexture = nullptr;

    float moveSpeed = 3.0f;
    float jumpSpeed = 6.5f;

    float width = 0.3f;
    float height = 0.3f;

    int maxHealth = 100;
};