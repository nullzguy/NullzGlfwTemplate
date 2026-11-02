#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include <glm/glm.hpp>
#include <glad/gl.h>

#include "shader.h"

using namespace std;

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
void shader::SetVec2(const char* var, vec2 value) {
    int location = GetUniformLocation(var);
    glUniform2f(location, value.x, value.y);
}
void shader::SetVec3(const char* var, vec3 value) {
    int location = GetUniformLocation(var);
    glUniform3f(location, value.x, value.y, value.z);
}
void shader::SetVec4(const char* var, vec4 value) {
    int location = GetUniformLocation(var);
    glUniform4f(location, value.x, value.y, value.z, value.w);
}
void shader::SetFloatArray(const char* var, const float* values, int count) {
    int location = GetUniformLocation(var);
    glUniform1fv(location, count, values);
}
void shader::SetVec2Array(const char* var, const vec2* values, int count) {
    int location = GetUniformLocation(var);
    glUniform2fv(location, count, &values[0].x);
}
void shader::SetVec3Array(const char* var, const vec3* values, int count) {
    int location = GetUniformLocation(var);
    glUniform3fv(location, count, &values[0].x);
}
void shader::SetVec4Array(const char* var, const vec4* values, int count) {
    int location = GetUniformLocation(var);
    glUniform4fv(location, count, &values[0].x);
}

void shader::SetInt(const char* var, int value) {
    int location = GetUniformLocation(var);
    glUniform1i(location, value);
}
void shader::SetIvec2(const char* var, ivec2 value) {
    int location = GetUniformLocation(var);
    glUniform2i(location, value.x, value.y);
}
void shader::SetIvec3(const char* var, ivec3 value) {
    int location = GetUniformLocation(var);
    glUniform3i(location, value.x, value.y, value.z);
}
void shader::SetIvec4(const char* var, ivec4 value) {
    int location = GetUniformLocation(var);
    glUniform4i(location, value.x, value.y, value.z, value.w);
}
void shader::SetIntArray(const char* var, const int* values, int count) {
    int location = GetUniformLocation(var);
    glUniform1iv(location, count, values);
}
void shader::SetIvec2Array(const char* var, const ivec2* values, int count) {
    int location = GetUniformLocation(var);
    glUniform2iv(location, count, &values[0].x);
}
void shader::SetIvec3Array(const char* var, const ivec3* values, int count) {
    int location = GetUniformLocation(var);
    glUniform3iv(location, count, &values[0].x);
}
void shader::SetIvec4Array(const char* var, const ivec4* values, int count) {
    int location = GetUniformLocation(var);
    glUniform4iv(location, count, &values[0].x);
}

void shader::SetBool(const char* var, bool value) {
    int location = GetUniformLocation(var);
    glUniform1i(location, value);
}

static void createTex1D(unsigned int &texID, int width, GLint internalFormat, GLenum format, GLenum type) {
    glGenTextures(1, &texID);
    glBindTexture(GL_TEXTURE_1D, texID);
    glTexImage1D(GL_TEXTURE_1D, 0, internalFormat, width, 0, format, type, nullptr);
    glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glBindTexture(GL_TEXTURE_1D, 0);
}

static void createTex2D(unsigned int &texID, int width, int height, GLint internalFormat, GLenum format, GLenum type) {
    glGenTextures(1, &texID);
    glBindTexture(GL_TEXTURE_2D, texID);
    glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, format, type, nullptr);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glBindTexture(GL_TEXTURE_2D, 0);
}

static void createTex3D(unsigned int &texID, int width, int height, int depth, GLint internalFormat, GLenum format, GLenum type) {
    glGenTextures(1, &texID);
    glBindTexture(GL_TEXTURE_3D, texID);
    glTexImage3D(GL_TEXTURE_3D, 0, internalFormat, width, height, depth, 0, format, type, nullptr);
    glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_3D, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    glBindTexture(GL_TEXTURE_3D, 0);
}

void shader::CreateTex1D(int width, unsigned int &texID) {
    createTex1D(texID, width, GL_RGBA8, GL_RGBA, GL_UNSIGNED_BYTE);
}
void shader::CreateTex2D(int width, int height, unsigned int &texID) {
    createTex2D(texID, width, height, GL_RGBA8, GL_RGBA, GL_UNSIGNED_BYTE);
}
void shader::CreateTex3D(int width, int height, int depth, unsigned int &texID) {
    createTex3D(texID, width, height, depth, GL_RGBA8, GL_RGBA, GL_UNSIGNED_BYTE);
}

void shader::CreateTex1DUI(int width, unsigned int &texID) {
    createTex1D(texID, width, GL_RGBA32UI, GL_RGBA_INTEGER, GL_UNSIGNED_INT);
}
void shader::CreateTex2DUI(int width, int height, unsigned int &texID) {
    createTex2D(texID, width, height, GL_RGBA32UI, GL_RGBA_INTEGER, GL_UNSIGNED_INT);
}
void shader::CreateTex3DUI(int width, int height, int depth, unsigned int &texID) {
    createTex3D(texID, width, height, depth, GL_RGBA32UI, GL_RGBA_INTEGER, GL_UNSIGNED_INT);
}

void shader::CreateFBO1D(unsigned int &FBOId, unsigned int &texID) {
    glGenFramebuffers(1, &FBOId);
    glBindFramebuffer(GL_FRAMEBUFFER, FBOId);
    glFramebufferTexture1D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_1D, texID, 0);
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) cerr << "FBO is incomplete!\n";

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}
void shader::CreateFBO2D(unsigned int &FBOId, unsigned int &texID) {
    glGenFramebuffers(1, &FBOId);
    glBindFramebuffer(GL_FRAMEBUFFER, FBOId);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texID, 0);
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) cerr << "FBO is incomplete!\n";

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}
void shader::CreateFBO3D(unsigned int &FBOId, unsigned int &texID) {
    glGenFramebuffers(1, &FBOId);
    glBindFramebuffer(GL_FRAMEBUFFER, FBOId);
    glFramebufferTexture3D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_3D, texID, 0, 0);
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) cerr << "FBO is incomplete!\n";

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void shader::CreateFBO1DUI(unsigned int &FBOId, unsigned int &texID) {
    CreateFBO1D(FBOId, texID);
}
void shader::CreateFBO2DUI(unsigned int &FBOId, unsigned int &texID) {
    CreateFBO2D(FBOId, texID);
}
void shader::CreateFBO3DUI(unsigned int &FBOId, unsigned int &texID) {
    CreateFBO3D(FBOId, texID);
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

        cerr << infoLog << '\n';

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

        cerr << "Failed to link shader:\n" << infoLog << '\n';

        glDeleteProgram(program);
        glDeleteShader(vertexShader);
        glDeleteShader(fragmentShader);
        return;
    }

    ID = program;

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}