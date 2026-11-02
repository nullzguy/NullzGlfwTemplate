#pragma once

#include "engine.h"
#include "shader.h"

inline int ticks = 0, tps = 0;
inline double tpsTimer = 0.0, renderTimer = 0.0,
oldT = 0.0,
dt = 0.0,
simTimer = 0.0;

shader& computeShader();
shader& fragmentShader();

// Render targets
inline unsigned int ComputeTexA = 0, ComputeTexB = 0;
inline unsigned int ComputeFBOA = 0, ComputeFBOB = 0;
inline unsigned int FrameTex = 0, FrameFBO = 0;
inline int renderWidth = 0, renderHeight = 0;
inline int screenWidth = 0, screenHeight = 0;

void InitRenderTargets(int width, int height);
void StartTimer();
void UpdateDt();
void TryUpdateSim();
void UpdateRenderTimer(engine& e);
bool ShouldRender(engine& e);
void TryRender(engine& e);