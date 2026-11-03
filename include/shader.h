#pragma once

#include <string>
#include <unordered_map>

#include <glm/glm.hpp>

using namespace glm;

struct shader {
    shader(const char* vertexPath, const char* fragmentPath);

    shader() = default;

    void Use() const;

    void SetFloat(const char* var, float value);
    void SetVec2(const char* var, vec2 value);
    void SetVec3(const char* var, vec3 value);
    void SetVec4(const char* var, vec4 value);
    void SetFloatArray(const char* var, const float* values, int count);
    void SetVec2Array(const char* var, const vec2* values, int count);
    void SetVec3Array(const char* var, const vec3* values, int count);
    void SetVec4Array(const char* var, const vec4* values, int count);

    void SetInt(const char* var, int value);
    void SetIvec2(const char* var, ivec2 value);
    void SetIvec3(const char* var, ivec3 value);
    void SetIvec4(const char* var, ivec4 value);
    void SetIntArray(const char* var, const int* values, int count);
    void SetIvec2Array(const char* var, const ivec2* values, int count);
    void SetIvec3Array(const char* var, const ivec3* values, int count);
    void SetIvec4Array(const char* var, const ivec4* values, int count);

    void SetBool(const char* var, bool value);

    unsigned int ID = 0;

private:
    int GetUniformLocation(const char* var);
    std::unordered_map<std::string, int> uniformCache;
};