#include "Texture.h"

#include <glad/glad.h>
#include <stb_image.h>

#include <iostream>

Texture::Texture(
    const std::filesystem::path& path)
{
    std::cout
        << "\n=====================================\n"
        << "LOADING TEXTURE\n"
        << path.string()
        << '\n';

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
        std::cout
            << "stbi_load FAILED\n";

        const char* reason =
            stbi_failure_reason();

        if (reason)
        {
            std::cout
                << "Reason: "
                << reason
                << '\n';
        }

        return;
    }

    std::cout
        << "stbi_load OK\n"
        << "Width: "
        << width_
        << '\n'
        << "Height: "
        << height_
        << '\n'
        << "Channels: "
        << channels
        << '\n';

    glGenTextures(
        1,
        &id_);

    std::cout
        << "Texture ID: "
        << id_
        << '\n';

    if (id_ == 0)
    {
        std::cout
            << "glGenTextures FAILED\n";

        stbi_image_free(data);

        return;
    }

    glBindTexture(
        GL_TEXTURE_2D,
        id_);

    GLenum error =
        glGetError();

    if (error != GL_NO_ERROR)
    {
        std::cout
            << "glBindTexture ERROR: "
            << error
            << '\n';
    }
    else
    {
        std::cout
            << "glBindTexture OK\n";
    }

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

    error =
        glGetError();

    if (error != GL_NO_ERROR)
    {
        std::cout
            << "glTexImage2D FAILED\n"
            << "OpenGL Error: "
            << error
            << '\n';
    }
    else
    {
        std::cout
            << "glTexImage2D OK\n";
    }

    glGenerateMipmap(
        GL_TEXTURE_2D);

    error =
        glGetError();

    if (error != GL_NO_ERROR)
    {
        std::cout
            << "glGenerateMipmap FAILED\n"
            << "OpenGL Error: "
            << error
            << '\n';
    }
    else
    {
        std::cout
            << "glGenerateMipmap OK\n";
    }

    glBindTexture(
        GL_TEXTURE_2D,
        0);

    stbi_image_free(data);

    std::cout
        << "TEXTURE LOADED SUCCESSFULLY\n";
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