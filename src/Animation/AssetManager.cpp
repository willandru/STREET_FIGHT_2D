#include "AssetManager.h"
#include "Texture.h"

#include <filesystem>
#include <iostream>

void AssetManager::loadAll(const std::string& basePath)
{
    std::cout << "Loading assets from: " << basePath << "\n";

    // IDLE

    textures["ryu_idle_1"] = new Texture(basePath + "/ryu/idle_ryu/ryu_idle_1.png");
    textures["ryu_idle_2"] = new Texture(basePath + "/ryu/idle_ryu/ryu_idle_2.png");
    textures["ryu_idle_3"] = new Texture(basePath + "/ryu/idle_ryu/ryu_idle_3.png");
    textures["ryu_idle_4"] = new Texture(basePath + "/ryu/idle_ryu/ryu_idle_4.png");

    textures["ken_idle_1"] = new Texture(basePath + "/ken/idle_ken/ken_idle_1.png");
    textures["ken_idle_2"] = new Texture(basePath + "/ken/idle_ken/ken_idle_2.png");
    textures["ken_idle_3"] = new Texture(basePath + "/ken/idle_ken/ken_idle_3.png");
    textures["ken_idle_4"] = new Texture(basePath + "/ken/idle_ken/ken_idle_4.png");

    // WALK RIGHT

    textures["ryu_walk_r_1"] = new Texture(basePath + "/ryu/walk_ryu/ryu_walk_r_1.png");
    textures["ryu_walk_r_2"] = new Texture(basePath + "/ryu/walk_ryu/ryu_walk_r_2.png");
    textures["ryu_walk_r_3"] = new Texture(basePath + "/ryu/walk_ryu/ryu_walk_r_3.png");
    textures["ryu_walk_r_4"] = new Texture(basePath + "/ryu/walk_ryu/ryu_walk_r_4.png");
    }

const Texture& AssetManager::get(const std::string& key) const
{
    return *textures.at(key);
}