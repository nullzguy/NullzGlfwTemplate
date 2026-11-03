#include "gpu/textures.h"

#include <iostream>

#include <glad/gl.h>

using namespace std;

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

void CreateTex1D(int width, unsigned int &texID) {
    createTex1D(texID, width, GL_RGBA8, GL_RGBA, GL_UNSIGNED_BYTE);
}
void CreateTex2D(int width, int height, unsigned int &texID) {
    createTex2D(texID, width, height, GL_RGBA8, GL_RGBA, GL_UNSIGNED_BYTE);
}
void CreateTex3D(int width, int height, int depth, unsigned int &texID) {
    createTex3D(texID, width, height, depth, GL_RGBA8, GL_RGBA, GL_UNSIGNED_BYTE);
}

void CreateTex1DUI(int width, unsigned int &texID) {
    createTex1D(texID, width, GL_RGBA32UI, GL_RGBA_INTEGER, GL_UNSIGNED_INT);
}
void CreateTex2DUI(int width, int height, unsigned int &texID) {
    createTex2D(texID, width, height, GL_RGBA32UI, GL_RGBA_INTEGER, GL_UNSIGNED_INT);
}
void CreateTex3DUI(int width, int height, int depth, unsigned int &texID) {
    createTex3D(texID, width, height, depth, GL_RGBA32UI, GL_RGBA_INTEGER, GL_UNSIGNED_INT);
}

void CreateFBO1D(unsigned int &FBOId, unsigned int &texID) {
    glGenFramebuffers(1, &FBOId);
    glBindFramebuffer(GL_FRAMEBUFFER, FBOId);
    glFramebufferTexture1D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_1D, texID, 0);
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) cerr << "FBO is incomplete!\n";

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}
void CreateFBO2D(unsigned int &FBOId, unsigned int &texID) {
    glGenFramebuffers(1, &FBOId);
    glBindFramebuffer(GL_FRAMEBUFFER, FBOId);
    glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, texID, 0);
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) cerr << "FBO is incomplete!\n";

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}
void CreateFBO3D(unsigned int &FBOId, unsigned int &texID) {
    glGenFramebuffers(1, &FBOId);
    glBindFramebuffer(GL_FRAMEBUFFER, FBOId);
    glFramebufferTexture3D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_3D, texID, 0, 0);
    if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) cerr << "FBO is incomplete!\n";

    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

void CreateFBO1DUI(unsigned int &FBOId, unsigned int &texID) {
    CreateFBO1D(FBOId, texID);
}
void CreateFBO2DUI(unsigned int &FBOId, unsigned int &texID) {
    CreateFBO2D(FBOId, texID);
}
void CreateFBO3DUI(unsigned int &FBOId, unsigned int &texID) {
    CreateFBO3D(FBOId, texID);
}

void DestroyTex(unsigned int &texID) {
    if (texID == 0) return;
    glDeleteTextures(1, &texID);
    texID = 0;
}

void DestroyFBO(unsigned int &FBOId) {
    if (FBOId == 0) return;
    glDeleteFramebuffers(1, &FBOId);
    FBOId = 0;
}