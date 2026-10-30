#pragma once

struct winSettings
{
    // width and height
    int w, h;
    // frames per second & capping (simulation runs continuously, 
    // rendering happens every 1/fps seconds)
    bool capFps;
    float fps;
    // returns the aspect ratio in the .cpp
    double aspect() const;
    
    winSettings(int W, int H, bool CapFps = false, float Fps = 60.0f)
    {
        w = W;
        h = H;
        capFps = CapFps;
        fps = Fps;
    }
};