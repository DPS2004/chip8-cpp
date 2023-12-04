#include <iostream>
#include <fstream>
#include <cmath>
#include "Host3ds.h"


void Host3ds::Init() {
	romfsInit();
	cfguInit();
	gfxInitDefault();
	C3D_Init(C3D_DEFAULT_CMDBUF_SIZE);
	C2D_Init(C2D_DEFAULT_MAX_OBJECTS);
	C2D_Prepare();
	consoleInit(GFX_BOTTOM, NULL);
	
    std::cout << "3ds init" << std::endl;
	
	top = C2D_CreateScreenTarget(GFX_TOP, GFX_LEFT);
    
    bottom = C2D_CreateScreenTarget(GFX_BOTTOM, GFX_LEFT);
	
	
	textBuf = C2D_TextBufNew(4096);
	font = C2D_FontLoad("romfs:/pico-8-mono.bcfnt");
	colorOff = C2D_Color32(0x00, 0x00, 0x00, 0xFF);
	colorOn = C2D_Color32(0xFF, 0xFF, 0xFF, 0xFF);

	/*
    screenSurface = SDL_GetWindowSurface( window );

    //set up colors
    colorOff = SDL_MapRGB( screenSurface->format, COLOR_OFF);
    colorOn = SDL_MapRGB( screenSurface->format, COLOR_ON);

    TTF_Init();

    font = TTF_OpenFont("pico-8-mono.ttf",12);

    textRenderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);

    state = SELECT_PROGRAM;
	*/

}

void Host3ds::Update(Chip *chip) {
    int input = GetInput();

    if(backPressed){
        state = SELECT_PROGRAM;
        InitMenu();
    }else{
        stepAccumulator += INSTRUCTIONSPERSECOND * (double)0.016;
        deltaTime =  (double)0.016;
        int stepsToDo = (int)stepAccumulator;
        stepAccumulator = std::fmod(stepAccumulator,1);
        //std::cout << stepAccumulator << std::endl;
        //std::cout << (float)stepsToDo << std::endl;
        if(state == RUN_PROGRAM){
            for (int i = 0; i < stepsToDo; ++i) {
                chip->Step(input, deltaTime);
            }
        }
    }



}

uint16_t Host3ds::GetInput() {

    //reset keys
    upPressed = false;
    downPressed = false;
    enterPressed = false;
    backPressed = false;
    uint16_t inputState = 0;
	
	hidScanInput();

	u32 kDown = hidKeysDown();
	if(kDown & KEY_DUP || kDown & KEY_CPAD_UP){
		upPressed = true;
	}
	if(kDown & KEY_DDOWN || kDown & KEY_CPAD_DOWN){
		downPressed = true;
	}
	if(kDown & KEY_A || kDown & KEY_B){
		enterPressed = true;
	}
	if(kDown & KEY_START){
		backPressed = true;
		if(state == SELECT_PROGRAM){
			state = STOP;
		}
	}
	
	/*
    SDL_Event e;
    while( SDL_PollEvent( &e ) != 0 )
    {
        if( e.type == SDL_QUIT )
        {
            state = STOP;
        }
        else if(e.type == SDL_KEYDOWN){
            switch(e.key.keysym.sym){
                case SDLK_UP:
                    upPressed = true;
                    break;
                case SDLK_DOWN:
                    downPressed = true;
                    break;
                case SDLK_RETURN:
                    enterPressed = true;
                    break;
                case SDLK_ESCAPE:
                    backPressed = true;
                    if(state == SELECT_PROGRAM){
                        state = STOP;
                    }
                    break;
            }
        }
    }

    const Uint8* keystate = SDL_GetKeyboardState(nullptr);
    for (int i = 0; i <= 0xf; ++i) {
        SDL_Scancode keycode;
        if(useVipsLayout){
            keycode = map_vips[i];
        }else{
            keycode = map_default[i];
        }
        if(keystate[keycode]){
            inputState += 1 << i;
        }
    }
	*/
	
	
    return inputState;
}

void Host3ds::Draw(Display *display) {

	C3D_FrameBegin(C3D_FRAME_SYNCDRAW);
	C2D_TargetClear(top, colorOff);
	C2D_SceneBegin(top);
	
    for (int y = 0; y < display->height; y++) {
        for (int x = 0; x < display->width; x++) {
            if(display->data[y*display->width+x]){
                DrawPixel(x,y);
            }
        }
    }
    display->updated=false;

	C3D_FrameEnd(0);
}


void Host3ds::DrawPixel(int x, int y) {
	/*
    SDL_FillRect(screenSurface,new SDL_Rect{x*SCREENSCALE,y*SCREENSCALE,SCREENSCALE-BORDERSIZE,SCREENSCALE-BORDERSIZE},colorOn);
	*/
	C2D_DrawRectSolid(x*SCREENSCALE+PIXELXOFFSET,y*SCREENSCALE+PIXELYOFFSET,0,SCREENSCALE-BORDERSIZE,SCREENSCALE-BORDERSIZE,colorOn);
}


void Host3ds::LoadProgram(std::string filename, Chip* chip) {
	
    std::ifstream programFile(filename,std::ios::in | std::ios::binary);
    uint8_t *program;
    program = new uint8_t[4096-PROGRAM_OFFSET]();
    int size = 0;
    while(programFile.peek() != EOF){
        uint8_t byte = programFile.get();
        program[size] = byte;
        size++;
    }
    chip->LoadProgram(program,size);
	/*
	*/
}

void Host3ds::Exit() {
	/*
    SDL_DestroyWindow( window );
    SDL_Quit();
	*/
}

void Host3ds::InitMenu() {
    GetPrograms(&programs,PROGRAMDIRECTORY);
    selectedProgram = 0;
}

void Host3ds::UpdateMenu(Chip *chip) {
    GetInput();
    if(backPressed){
        state = STOP;
    } else {
        if(upPressed){
            selectedProgram -= 1;
        }
        if(downPressed){
            selectedProgram += 1;
        }

        if(selectedProgram < 0){
            selectedProgram = (int)programs.size();
        } else if (selectedProgram > (int)programs.size()){
            selectedProgram = 0;
        }

        if(enterPressed){
            chip->Init();
            LoadProgram(programs[selectedProgram], chip);
            state = RUN_PROGRAM;
			/*
            lastTick = SDL_GetTicks();
			*/
        }
    }
}

void Host3ds::DrawMenu() {

	C3D_FrameBegin(C3D_FRAME_SYNCDRAW);
	C2D_TargetClear(top, colorOff);
	C2D_SceneBegin(top);

    for (int i = 0; i < (int)programs.size(); ++i) {
        if(i == selectedProgram){

            DrawText("> " + programs[i],10,(SCREENHEIGHT / 2) + ((i-selectedProgram) *24));
        }else{

            DrawText("  " + programs[i],10,(SCREENHEIGHT / 2) + ((i-selectedProgram) *24));
        }
    }
	
	C3D_FrameEnd(0);

}

void Host3ds::DrawText(const std::string& text, int x, int y) {
	/*
    textSurface = TTF_RenderUTF8_Solid_Wrapped(font, text.c_str(), {COLOR_ON}, 0);
    TTF_SizeText(font, text.c_str(), &textPosition.w,&textPosition.h);
    textTexture = SDL_CreateTextureFromSurface(textRenderer,textSurface);
    textPosition.x = x;
    textPosition.y = y;

    SDL_RenderCopy(textRenderer, textTexture, nullptr, &textPosition);
	*/
	C2D_TextBufClear(textBuf);
	C2D_TextFontParse(&staticText, font, textBuf, text.c_str());
	C2D_TextOptimize(&staticText);
	C2D_DrawText(&staticText,C2D_AtBaseline | C2D_WithColor, x, y, 0.0f, 0.333f, 0.333f, colorOn);

}
