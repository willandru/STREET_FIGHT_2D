#include "Texture.h"

#include <glad/glad.h>
#include <stb_image.h>

Texture::Texture(
    const std::filesystem::path& path)
{
    stbi_set_flip_vertically_on_load(true);

    int channels = 0;

    unsigned char* data =
        stbi_load(
            path.string().c_str(),
            &width_,
            &height_,
            &channels,
            STBI_rgb_alpha);

    if (!data)
    {
        return;
    }

    glGenTextures(1, &id_);

    if (id_ == 0)
    {
        stbi_image_free(data);
        return;
    }

    glBindTexture(
        GL_TEXTURE_2D,
        id_);

    glTexParameteri(
        GL_TEXTURE_2D,
        GL_TEXTURE_WRAP_S,
        GL_CLAMP_TO_EDGE);

    glTexParameteri(
        GL_TEXTURE_2D,
        GL_TEXTURE_WRAP_T,
        GL_CLAMP_TO_EDGE);

    glTexParameteri(
        GL_TEXTURE_2D,
        GL_TEXTURE_MIN_FILTER,
        GL_LINEAR);

    glTexParameteri(
        GL_TEXTURE_2D,
        GL_TEXTURE_MAG_FILTER,
        GL_LINEAR);

    glTexImage2D(
        GL_TEXTURE_2D,
        0,
        GL_RGBA8,
        width_,
        height_,
        0,
        GL_RGBA,
        GL_UNSIGNED_BYTE,
        data);

    glGenerateMipmap(
        GL_TEXTURE_2D);

    glBindTexture(
        GL_TEXTURE_2D,
        0);

    stbi_image_free(data);
}

Texture::~Texture()
{
    if (id_ != 0)
    {
        glDeleteTextures(
            1,
            &id_);
    }
}

bool Texture::isValid() const
{
    return id_ != 0;
}

void Texture::bind() const
{
    glBindTexture(
        GL_TEXTURE_2D,
        id_);
}

int Texture::width() const
{
    return width_;
}

int Texture::height() const
{
    return height_;
}