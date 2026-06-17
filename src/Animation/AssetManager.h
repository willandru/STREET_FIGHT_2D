#pragma once

#include <unordered_map>
#include <string>

class Texture;

class AssetManager
{
public:
    void loadAll(const std::string& basePath);

    const Texture& get(const std::string& key) const;

private:
    std::unordered_map<std::string, Texture*> textures;
};