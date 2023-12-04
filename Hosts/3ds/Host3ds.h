#pragma once

#include <cstdint>
#include "../Host.h"

#include <citro2d.h>

#define PIXELXOFFSET 8
#define PIXELYOFFSET 24
#define SCREENSCALE 6

#define BORDERSIZE 1

#define INSTRUCTIONSPERSECOND 700

#define SCREENWIDTH 400
#define SCREENHEIGHT 240
#define COLOR_OFF 0x00, 0x00, 0x00
#define COLOR_ON 0xFF, 0xFF, 0xFF

#define PROGRAMDIRECTORY "Programs"


class Host3ds: public Host {
public:
    void Init() override;
    void Update(Chip* chip) override;
    void Draw(Display* display) override;

    void InitMenu() override;
    void UpdateMenu(Chip* chip) override;
    void DrawMenu() override;

    uint16_t GetInput() override;
    void LoadProgram(std::string filename, Chip* chip)  override;

    void Exit() override;

private:
    void DrawPixel(int x, int y);

    void DrawText(const std::string& text, int x, int y);

    /*
    SDL_Window* window = nullptr;
    SDL_Surface* screenSurface = nullptr;
    */
	C3D_RenderTarget* top;
	C3D_RenderTarget* bottom;
	
    u32 colorOff;
    u32 colorOn;

    uint64_t lastTick = 0;


    double stepAccumulator = 0;
    double deltaTime = 0;

    bool useVipsLayout = true;

    bool upPressed = false;
    bool downPressed = false;
    bool enterPressed = false;
    bool backPressed = false;

    int selectedProgram = 0;

	C2D_Font font;
	C2D_TextBuf textBuf;
	C2D_Text staticText;
    /*
    TTF_Font* font = nullptr;
    SDL_Surface* textSurface = nullptr;
    SDL_Texture* textTexture = nullptr;
    SDL_Rect textPosition;
    SDL_Renderer* textRenderer;
    */

};
