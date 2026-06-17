#pragma once

#include "CharacterData.h"

class AssetManager;

namespace Characters
{
    CharacterData createRyu(const AssetManager& assets);
    CharacterData createKen(const AssetManager& assets);
    CharacterData createMaki(const AssetManager& assets);
}