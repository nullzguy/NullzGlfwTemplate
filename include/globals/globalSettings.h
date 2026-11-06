#pragma once

struct globalSettings {
    float maxTps;
    
    globalSettings(float Tps) : maxTps(Tps) {}
};

extern globalSettings globalSets;
