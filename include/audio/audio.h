#pragma once

#include <iostream>
#include <stdlib.h>
#include <cmath>
#include <vector>

struct audio {
    float sampleRate; // 48000 for instance
    std::vector<float> samples;

    audio(float rate, std::vector<float> samples_) : sampleRate(rate), samples(samples_) {}

    void ImportWav(const char* path) {}
    void ExportWav(const char* path) {}

    void ChangeSpeed(float mul) {}
    void ChangeVolume(float mul) {}
    void ClampAmplitude(float max) {}
    void Cut(float start, float end) {}
};