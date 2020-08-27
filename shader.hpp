#pragma once

#include <string>

struct Shader
{   
    unsigned int shaderProgram;
    std::string open_shader(std::string path);
    Shader();
    ~Shader() = default;
};