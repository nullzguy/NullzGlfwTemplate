#pragma once

#include <iostream>
#include <algorithm>
#include <utility>
#include <vector>

struct audio {
    int sampleRate; // 48000 for instance
    std::vector<float> samples;

    audio(int rate, std::vector<float> samples_) : sampleRate(rate), samples(std::move(samples_)) {}

    void ImportWav(const char* path) {}
    void ExportWav(const char* path) {}

    int ChangeSpeed(float mul);
    int ChangeVolume(float mul);
    int ClampAmplitude(float max);
    int Cut(float start, float end); // [0;1]
};