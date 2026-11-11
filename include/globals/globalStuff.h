#pragma once

#include <algorithm>
#include <GLFW/glfw3.h>
#include <glad/gl.h>
#include "imgui.h"
#include "imgui_impl_opengl3.h"
#include "engine/engine.h"
#include "gpu/shader.h"
#include "engine/engine.h"
#include "globals/globalSettings.h"
#include "main/render.h"
#include "main/sim.h"
#include "gpu/shader.h"
#include "gpu/textures.h"

inline int ticks = 0, tps = 0;
inline double tpsTimer = 0.0, renderTimer = 0.0,
oldT = 0.0,
dt = 0.0,
simTimer = 0.0;

inline shader computeShader = shader();
inline shader fragmentShader = shader();

inline unsigned int ComputeTexA = 0, ComputeTexB = 0;
inline unsigned int ComputeFBOA = 0, ComputeFBOB = 0;
inline unsigned int FrameTex = 0, FrameFBO0 = 0;
inline int renderWidth = 0, renderHeight = 0;
inline int screenWidth = 0, screenHeight = 0;
inline int simWidth = 0, simHeight = 0;

void StartTimer();
void UpdateDt();
void TryUpdateRes(engine& e);
void TryUpdateSim();
void UpdateRenderTimer(engine& e);
bool ShouldRender(engine& e);
void TryRender(engine& e);