// /src/Shader.cpp


#include "Shader.h"

#include <glad/glad.h>

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <glm/gtc/type_ptr.hpp>

namespace
{
std::string readTextFile(const std::filesystem::path& path)
{
    std::ifstream file(path);

    if (!file)
    {
        return {};
    }

    std::stringstream buffer;
    buffer << file.rdbuf();

    return buffer.str();
}

unsigned int compileShader(
    GLenum type,
    const std::string& source)
{
    const unsigned int shader = glCreateShader(type);

    const char* sourcePtr = source.c_str();

    glShaderSource(
        shader,
        1,
        &sourcePtr,
        nullptr);

    glCompileShader(shader);

    int success = 0;

    glGetShaderiv(
        shader,
        GL_COMPILE_STATUS,
        &success);

    if (!success)
    {
        char infoLog[1024];

        glGetShaderInfoLog(
            shader,
            sizeof(infoLog),
            nullptr,
            infoLog);

        std::cerr
            << "Shader compilation error:\n"
            << infoLog
            << '\n';

        glDeleteShader(shader);

        return 0;
    }

    return shader;
}
}

Shader::Shader(
    const std::filesystem::path& vertexPath,
    const std::filesystem::path& fragmentPath)
{
    const std::string vertexSource =
        readTextFile(vertexPath);

    const std::string fragmentSource =
        readTextFile(fragmentPath);

    if (vertexSource.empty() ||
        fragmentSource.empty())
    {
        return;
    }

    const unsigned int vertexShader =
        compileShader(
            GL_VERTEX_SHADER,
            vertexSource);

    const unsigned int fragmentShader =
        compileShader(
            GL_FRAGMENT_SHADER,
            fragmentSource);

    if (vertexShader == 0 ||
        fragmentShader == 0)
    {
        return;
    }

    id_ = glCreateProgram();

    glAttachShader(id_, vertexShader);
    glAttachShader(id_, fragmentShader);

    glLinkProgram(id_);

    int success = 0;

    glGetProgramiv(
        id_,
        GL_LINK_STATUS,
        &success);

    if (!success)
    {
        char infoLog[1024];

        glGetProgramInfoLog(
            id_,
            sizeof(infoLog),
            nullptr,
            infoLog);

        std::cerr
            << "Shader link error:\n"
            << infoLog
            << '\n';

        glDeleteProgram(id_);
        id_ = 0;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

Shader::~Shader()
{
    if (id_ != 0)
    {
        glDeleteProgram(id_);
    }
}

bool Shader::isValid() const
{
    return id_ != 0;
}

void Shader::use() const
{
    glUseProgram(id_);
}


void Shader::setMat4(
    const char* name,
    const glm::mat4& matrix) const
{
    const int location =
        glGetUniformLocation(
            id_,
            name);

    glUniformMatrix4fv(
        location,
        1,
        GL_FALSE,
        glm::value_ptr(matrix));
}