#pragma once

#include <SDL2/SDL.h>
#include <GL/gl.h>

class Platform {
public:
    Platform(char const* title, int windowWidth, int windowHeight,
        int textureWidth, int textureHeight);

    ~Platform();

    void update(void const* buffer, int pitch);

    bool processInput(uint8_t* keys);

private:
    SDL_Window* window{};
    SDL_Renderer* renderer{};
    SDL_Texture* texture{};
};