#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include <glm/glm.hpp>
#include <glad/gl.h>

#include "gpu/shader.h"

int shader::GetUniformLocation(const char* var) {
    auto it = uniformCache.find(var);
    if (it != uniformCache.end()) return it->second;

    int location = glGetUniformLocation(ID, var);
    uniformCache[var] = location;
    return location;
}

void shader::Use() const{
    glUseProgram(ID);
}

void shader::SetFloat(const char* var, float value) {
    int location = GetUniformLocation(var);
    glUniform1f(location, value);
}
void shader::SetVec2(const char* var, glm::vec2 value) {
    int location = GetUniformLocation(var);
    glUniform2f(location, value.x, value.y);
}
void shader::SetVec3(const char* var, glm::vec3 value) {
    int location = GetUniformLocation(var);
    glUniform3f(location, value.x, value.y, value.z);
}
void shader::SetVec4(const char* var, glm::vec4 value) {
    int location = GetUniformLocation(var);
    glUniform4f(location, value.x, value.y, value.z, value.w);
}
void shader::SetFloatArray(const char* var, const float* values, int count) {
    int location = GetUniformLocation(var);
    glUniform1fv(location, count, values);
}
void shader::SetVec2Array(const char* var, const glm::vec2* values, int count) {
    int location = GetUniformLocation(var);
    glUniform2fv(location, count, &values[0].x);
}
void shader::SetVec3Array(const char* var, const glm::vec3* values, int count) {
    int location = GetUniformLocation(var);
    glUniform3fv(location, count, &values[0].x);
}
void shader::SetVec4Array(const char* var, const glm::vec4* values, int count) {
    int location = GetUniformLocation(var);
    glUniform4fv(location, count, &values[0].x);
}

void shader::SetInt(const char* var, int value) {
    int location = GetUniformLocation(var);
    glUniform1i(location, value);
}
void shader::SetIvec2(const char* var, glm::ivec2 value) {
    int location = GetUniformLocation(var);
    glUniform2i(location, value.x, value.y);
}
void shader::SetIvec3(const char* var, glm::ivec3 value) {
    int location = GetUniformLocation(var);
    glUniform3i(location, value.x, value.y, value.z);
}
void shader::SetIvec4(const char* var, glm::ivec4 value) {
    int location = GetUniformLocation(var);
    glUniform4i(location, value.x, value.y, value.z, value.w);
}
void shader::SetIntArray(const char* var, const int* values, int count) {
    int location = GetUniformLocation(var);
    glUniform1iv(location, count, values);
}
void shader::SetIvec2Array(const char* var, const glm::ivec2* values, int count) {
    int location = GetUniformLocation(var);
    glUniform2iv(location, count, &values[0].x);
}
void shader::SetIvec3Array(const char* var, const glm::ivec3* values, int count) {
    int location = GetUniformLocation(var);
    glUniform3iv(location, count, &values[0].x);
}
void shader::SetIvec4Array(const char* var, const glm::ivec4* values, int count) {
    int location = GetUniformLocation(var);
    glUniform4iv(location, count, &values[0].x);
}

void shader::SetBool(const char* var, bool value) {
    int location = GetUniformLocation(var);
    glUniform1i(location, value);
}

static unsigned int compileShader(const char* source, GLenum shaderType) {
    unsigned int shader = glCreateShader(shaderType);

    glShaderSource(shader, 1, &source, nullptr);
    glCompileShader(shader);

    int success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

    if (!success) {
        char infoLog[4096];

        glGetShaderInfoLog(
            shader,
            4096,
            nullptr,
            infoLog
        );

        std::cerr << infoLog << '\n';

        glDeleteShader(shader);
        return 0;
    }

    return shader;
}

static std::string readFile(const char* path) {
    std::ifstream file(path, std::ios::binary);
    if (!file) {
        std::cerr << "Failed to open shader file: " << path << '\n';
        return {};
    }

    std::ostringstream contents;
    contents << file.rdbuf();
    return contents.str();
}

shader::shader(const char* vertexPath, const char* fragmentPath) {
    const std::string vertexSource = readFile(vertexPath);
    const std::string fragmentSource = readFile(fragmentPath);
    if (vertexSource.empty() || fragmentSource.empty()) return;

    unsigned int vertexShader = compileShader(vertexSource.c_str(), GL_VERTEX_SHADER);
    unsigned int fragmentShader = compileShader(fragmentSource.c_str(), GL_FRAGMENT_SHADER);

    if (vertexShader == 0 || fragmentShader == 0) {
        if (vertexShader) glDeleteShader(vertexShader);
        if (fragmentShader) glDeleteShader(fragmentShader);
        return;
    }

    unsigned int program = glCreateProgram();

    glAttachShader(program, vertexShader);
    glAttachShader(program, fragmentShader);

    glLinkProgram(program);

    int success;
    glGetProgramiv(program, GL_LINK_STATUS, &success);

    if (!success) {
        char infoLog[4096];

        glGetProgramInfoLog(
            program,
            4096,
            nullptr,
            infoLog
        );

        std::cerr << "Failed to link shader:\n" << infoLog << '\n';

        glDeleteProgram(program);
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
        return;
    }

    ID = program;

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}