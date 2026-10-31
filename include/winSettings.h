#pragma once

struct winSettings
{
    // width and height
    int w, h;
    // frames per second (rendering happens every 1/fps seconds)
    float maxFps;
    // returns the aspect ratio in the .cpp
    double aspect() const;
    
    winSettings(int W, int H, float Fps = 60.0f) : w(W), h(H), maxFps(Fps) {}
};