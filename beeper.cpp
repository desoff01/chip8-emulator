#include "beeper.h"

Beeper::Beeper() {
    SDL_Init(SDL_INIT_AUDIO);
    SDL_AudioSpec desiredSpec;

    desiredSpec.freq = FREQUENCY;
    desiredSpec.format = AUDIO_S16SYS;
    desiredSpec.channels = 1;
    desiredSpec.samples = 2048;
    desiredSpec.callback = audio_callback;
    desiredSpec.userdata = this;

    SDL_AudioSpec obtainedSpec;

    dev = SDL_OpenAudioDevice(NULL, 0, &desiredSpec, &obtainedSpec, SDL_AUDIO_ALLOW_ANY_CHANGE);

    SDL_PauseAudioDevice(dev, 0);
}

Beeper::~Beeper() {
    SDL_CloseAudioDevice(dev);
}

void Beeper::generateSamples(Sint16* stream, int length) {
    if (beeps.empty()){
        for (int i {0}; i < length; i++) stream[i] = 0;

        return;
    }
    BeepObject& bo {beeps.front()};

    int samplesToDo {std::min(bo.samplesLeft, length)};
    bo.samplesLeft -= samplesToDo;

    for (int i {0}; i < samplesToDo; i++) {
        stream[i] = AMPLITUDE * std::sin(v * 2 * M_PI / FREQUENCY);
        v += bo.freq;
    }

    if (bo.samplesLeft == 0) beeps.pop();
}

void Beeper::beep(double freq, int duration) {
    BeepObject bo;
    bo.freq = freq;
    bo.samplesLeft = duration * FREQUENCY / 1000;

    SDL_LockAudioDevice(dev);
    beeps.push(bo);
    SDL_UnlockAudioDevice(dev);
}

void audio_callback(void* _beeper, Uint8* _stream, int _length) {
    Sint16* stream {reinterpret_cast<Sint16*>(_stream)};
    int length {_length / 2};
    Beeper* beeper {reinterpret_cast<Beeper*>(_beeper)};

    beeper->generateSamples(stream, length);
}