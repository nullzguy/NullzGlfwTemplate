#include "audio/audio.h"
#include "files_management/files.h"

int audio::ChangeSpeed(float mul) {
    if (mul <= 0) {
        std::cerr << "Audio speed multiplier is less than or equal to zero!\n";
        return 1;
    }

    sampleRate = static_cast<int>(sampleRate * mul);

    return 0;
}

int audio::ChangeVolume(float mul) {
    if (mul < 0) {
        std::cerr << "Audio volume multiplier is less than zero!\n";
        return 1;
    }

    for (float& s : samples) {
        s *= mul;
    }

    return 0;
}

int audio::ClampAmplitude(float max) {
    if (max < 0) {
        std::cerr << "Audio max amplitude is less than zero!\n";
        return 1;
    }

    for (float& s : samples) {
        s = std::clamp(s, -max, max);
    }

    return 0;
}

int audio::Cut(float start, float end) {
    if (start < 0 || end < 0 || start > 1 || end > 1) {
        std::cerr << "Invalid start/end args in the audio cut!\nExpected [0;1] range.\n";
        return 1;
    }
    if (start >= end) {
        std::cerr << "Start of the audio cut must be smaller than the end!\n";
        return 1;
    }

    const std::size_t size = samples.size();
    const std::size_t startSample = static_cast<std::size_t>(size * start);
    const std::size_t endSample = static_cast<std::size_t>(size * end);

    samples = std::vector<float>(samples.begin() + startSample, samples.begin() + endSample);

    return 0;
}