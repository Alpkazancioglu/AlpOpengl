#pragma once

#include "include.h"
#include <iostream>
#include <string>
#include "sstream"
#include <fstream>

#define TEXTURECOLOR 0
#define RGBCOLOR 1




static std::string ParseShader(const std::string& filepath)
{
    std::ifstream inputFile(filepath, std::ios::binary);

    std::stringstream buffer;
    if (inputFile.is_open())
    {
        buffer << inputFile.rdbuf();
        inputFile.close();
    }
    else {
        std::cout << "file does not exist" << '\n';

    }
    return buffer.str();

}


static unsigned int CompileShader(unsigned int type, const std::string& source)
{
    unsigned int id = glCreateShader(type);
    const char* src = source.c_str();
    glShaderSource(id, 1, &src, nullptr);
    glCompileShader(id);

    int result;

    glGetShaderiv(id, GL_COMPILE_STATUS, &result);

    if (result == GL_FALSE)
    {
        int lenght;
        glGetShaderiv(id, GL_INFO_LOG_LENGTH, &lenght);
        char* messeage = (char*)alloca(lenght * sizeof(char));
        glGetShaderInfoLog(id, lenght, &lenght, messeage);
        std::cout << "failed to compile " << (type == GL_VERTEX_SHADER ? "vertex" : "fragment") << "shader" << '\n';
        std::cout << messeage << '\n';
        glDeleteShader(id);
        return 0;
    }

    return id;

}


static unsigned int CreateProgram(const std::string& vertexShader, const std::string& fragmentShader)
{
    unsigned int program = glCreateProgram();
    unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
    unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);
    glAttachShader(program, vs);
    glAttachShader(program, fs);
    glLinkProgram(program);
    glValidateProgram(program);
    glDeleteShader(vs);
    glDeleteShader(fs);
    return program;


}


class Shader {

public:
    Shader(const char* VertexShaderFilePath, const char* FragmentShaderFilePath);
    ~Shader() {glDeleteProgram(shaderId);};
    void clear();
    GLuint getShader();
    void bind() const;
    void unBind() const;

    void setUniform4f(const std::string& name, float v0, float v1, float v2, float v3);
    void setUniform3f(const std::string& name, float v0, float v1, float v2);
    void setUniform1i(const std::string& name, int v);
    void setUniformMat4(const std::string& name, glm::mat4& data);

private:
    GLuint shaderId;


};