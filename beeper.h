#pragma once

#include <SDL2/SDL.h>
#include <SDL2/SDL_audio.h>
#include <queue>
#include <math.h>

#define AMPLITUDE 28000
#define FREQUENCY 44100

struct BeepObject {
    double freq;
    int samplesLeft;
};

class Beeper {
private:
    SDL_AudioDeviceID dev;
    double v;
    std::queue<BeepObject> beeps;

public:
    Beeper();
    ~Beeper();

    void beep(double freq, int duration);
    void generateSamples(Sint16* stream, int length);
};

void audio_callback(void*, Uint8*, int);