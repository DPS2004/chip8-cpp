#pragma once

#include "../Host.h"
#include "SDL.h"


#define SCREENSCALE 8
#define BORDERSIZE 1

#define INSTRUCTIONSPERSECOND 700

#define SCREENWIDTH (64 * SCREENSCALE)
#define SCREENHEIGHT (32 * SCREENSCALE)
#define COLOR_OFF 0x00, 0x00, 0x00
#define COLOR_ON 0xFF, 0xFF, 0xFF


class HostGraphic: public Host {
public:
    void Init() override;
    void Update(Chip* chip) override;
    void Draw(Display* display) override;
    uint16_t GetInput() override;
    void LoadProgram(std::string filename, Chip* chip)  override;

    void Exit() override;

private:
    void DrawPixel(int x, int y);

    SDL_Window* window = nullptr;
    SDL_Surface* screenSurface = nullptr;

    Uint32 colorOff = 0;
    Uint32 colorOn = 0;

    Uint64 lastTick = 0;

    double stepAccumulator = 0;
    double deltaTime = 0;

    bool useVipsLayout = true;
};

const SDL_Scancode map_default[] = {
        SDL_SCANCODE_0, SDL_SCANCODE_1, SDL_SCANCODE_2, SDL_SCANCODE_3,SDL_SCANCODE_4,SDL_SCANCODE_5,SDL_SCANCODE_6,SDL_SCANCODE_7,SDL_SCANCODE_8,SDL_SCANCODE_9,SDL_SCANCODE_A,SDL_SCANCODE_B,SDL_SCANCODE_C,SDL_SCANCODE_D,SDL_SCANCODE_E,SDL_SCANCODE_F
};

const SDL_Scancode map_vips[] = {
        SDL_SCANCODE_X,SDL_SCANCODE_1,SDL_SCANCODE_2,SDL_SCANCODE_3,SDL_SCANCODE_Q,SDL_SCANCODE_W,SDL_SCANCODE_E,SDL_SCANCODE_A,SDL_SCANCODE_S,SDL_SCANCODE_D,SDL_SCANCODE_Z,SDL_SCANCODE_C,SDL_SCANCODE_4,SDL_SCANCODE_R,SDL_SCANCODE_F,SDL_SCANCODE_V
};
