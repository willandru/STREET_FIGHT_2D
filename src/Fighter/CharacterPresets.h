#pragma once

#include "CharacterData.h"

class Texture;

namespace Characters
{
    CharacterData createRyu(
        Texture& idle1,
        Texture& idle2,
        Texture& idle3,
        Texture& idle4);

    CharacterData createKen(
        Texture& idle1,
        Texture& idle2,
        Texture& idle3,
        Texture& idle4);

    CharacterData createMaki(
        Texture& idle1,
        Texture& idle2,
        Texture& idle3,
        Texture& idle4);
}