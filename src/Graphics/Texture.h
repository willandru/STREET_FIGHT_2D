#pragma once

#include <filesystem>

class Texture
{
public:
    Texture(
        const std::filesystem::path& path);

    ~Texture();

    Texture(const Texture&) = delete;
    Texture& operator=(const Texture&) = delete;

    bool isValid() const;

    void bind() const;

    int width() const;
    int height() const;

private:
    unsigned int id_ = 0;

    int width_ = 0;
    int height_ = 0;
};