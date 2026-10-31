#pragma once

#include <GLFW/glfw3.h>
#include "engine.h"

inline int ticks = 0, tps = 0;
inline double tpsTimer = 0.0, renderTimer = 0.0,
oldT = 0.0,
dt = 0.0,
simTimer = 0.0;
    
void StartTimer();
void UpdateDt();
void UpdateSim();
void UpdateRenderTimer(engine& e);
bool ShouldRender(engine& e);
void UpdateRender(engine& e);