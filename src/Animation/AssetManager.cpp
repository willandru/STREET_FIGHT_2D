#include "AssetManager.h"
#include "Texture.h"

#include <filesystem>
#include <iostream>

void AssetManager::loadAll(const std::string& basePath)
{
    namespace fs = std::filesystem;

    std::cout << "Loading assets from: " << basePath << "\n";

    // =========================
    // RYU IDLE
    // =========================
    textures["ryu_idle_1"] =
        new Texture(basePath + "/ryu/idle_ryu/ryu_idle_1.png");

    textures["ryu_idle_2"] =
        new Texture(basePath + "/ryu/idle_ryu/ryu_idle_2.png");

    textures["ryu_idle_3"] =
        new Texture(basePath + "/ryu/idle_ryu/ryu_idle_3.png");

    textures["ryu_idle_4"] =
        new Texture(basePath + "/ryu/idle_ryu/ryu_idle_4.png");

    // =========================
    // KEN IDLE (reutiliza o cambia luego)
    // =========================
    textures["ken_idle_1"] =
        new Texture(basePath + "/ken/idle_ken/ken_idle_1.png");

    textures["ken_idle_2"] =
        new Texture(basePath + "/ken/idle_ken/ken_idle_2.png");

    textures["ken_idle_3"] =
        new Texture(basePath + "/ken/idle_ken/ken_idle_3.png");

    textures["ken_idle_4"] =
        new Texture(basePath + "/ken/idle_ken/ken_idle_4.png");
}

const Texture& AssetManager::get(const std::string& key) const
{
    return *textures.at(key);
}