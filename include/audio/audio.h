#pragma once

#include <iostream>
#include <algorithm>
#include <string>
#include <utility>
#include <vector>

#include "files_management/files.h"
#include "misc/helpers.h"

struct audio {
    int sampleRate; // 48000 for instance
    std::vector<float> samples;

    audio(int rate, std::vector<float> samples_) : sampleRate(rate), samples(std::move(samples_)) {}

    int ImportWav(const char* path);
    int ExportWav(const char* path);

    int ChangeSpeed(float mul);
    int ChangeVolume(float mul);
    int ClampAmplitude(float max);
    int Cut(float start, float end); // [0;1]
};