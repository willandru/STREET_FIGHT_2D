#pragma once

#include <filesystem>
#include <glm/mat4x4.hpp>

class Shader
{
public:
    Shader(
        const std::filesystem::path& vertexPath,
        const std::filesystem::path& fragmentPath);

    ~Shader();

    Shader(const Shader&) = delete;
    Shader& operator=(const Shader&) = delete;

    bool isValid() const;

    void use() const;

    void setMat4(
        const char* name,
        const glm::mat4& matrix) const;

private:
    unsigned int id_ = 0;
};