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
    std::cout
        << "[SHADER] Leyendo archivo: "
        << path.string()
        << std::endl;

    std::ifstream file(path);

    if (!file)
    {
        std::cout
            << "[SHADER] ERROR: no se pudo abrir: "
            << path.string()
            << std::endl;

        return {};
    }

    std::stringstream buffer;
    buffer << file.rdbuf();

    std::cout
        << "[SHADER] Archivo cargado correctamente"
        << std::endl;

    return buffer.str();
}

unsigned int compileShader(
    GLenum type,
    const std::string& source)
{
    std::cout
        << "[SHADER] Compilando "
        << (type == GL_VERTEX_SHADER ? "VERTEX" : "FRAGMENT")
        << std::endl;

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
            << "[SHADER] Shader compilation error:\n"
            << infoLog
            << '\n';

        glDeleteShader(shader);

        return 0;
    }

    std::cout
        << "[SHADER] Compilacion OK"
        << std::endl;

    return shader;
}
}

Shader::Shader(
    const std::filesystem::path& vertexPath,
    const std::filesystem::path& fragmentPath)
{
    std::cout
        << "[SHADER] Constructor Shader"
        << std::endl;

    const std::string vertexSource =
        readTextFile(vertexPath);

    const std::string fragmentSource =
        readTextFile(fragmentPath);

    if (vertexSource.empty() ||
        fragmentSource.empty())
    {
        std::cout
            << "[SHADER] ERROR: vertexSource o fragmentSource vacio"
            << std::endl;

        return;
    }

    std::cout
        << "[SHADER] Fuentes cargadas"
        << std::endl;

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
        std::cout
            << "[SHADER] ERROR: fallo compilacion de shaders"
            << std::endl;

        return;
    }

    std::cout
        << "[SHADER] Creando programa OpenGL"
        << std::endl;

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
            << "[SHADER] Shader link error:\n"
            << infoLog
            << '\n';

        glDeleteProgram(id_);
        id_ = 0;
    }
    else
    {
        std::cout
            << "[SHADER] Link OK"
            << std::endl;
    }

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    std::cout
        << "[SHADER] Shader listo"
        << std::endl;
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

void Shader::setInt(
    const char* name,
    int value) const
{
    const int location =
        glGetUniformLocation(
            id_,
            name);

    glUniform1i(
        location,
        value);
}