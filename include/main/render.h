#pragma once

#include <glad/gl.h>
#include <glm/glm.hpp>
#include "globals/globalStuff.h"
#include "gpu/shader.h"

void InitShaders();
void InitRenderTargets(int width, int height, int compWidth, int compHeight);
void BlitFBO(int FBO);
void Render();