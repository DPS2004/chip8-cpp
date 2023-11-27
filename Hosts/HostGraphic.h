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
    int GetInput() override;
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
};


