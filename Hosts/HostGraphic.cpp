#include <iostream>
#include <fstream>
#include <cmath>
#include "HostGraphic.h"


void HostGraphic::Init() {
    std::cout << "Graphic init" << std::endl;


    if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        throw std::runtime_error("Could not init SDL: " +  std::string(SDL_GetError()));
    }

    window = SDL_CreateWindow( "chip8-cpp", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREENWIDTH, SCREENHEIGHT, SDL_WINDOW_SHOWN );
    if(window == nullptr){
        throw std::runtime_error("Could not init SDL window: " +  std::string(SDL_GetError()));
    }

    screenSurface = SDL_GetWindowSurface( window );

    //set up colors
    colorOff = SDL_MapRGB( screenSurface->format, COLOR_OFF);
    colorOn = SDL_MapRGB( screenSurface->format, COLOR_ON);

    TTF_Init();

    font = TTF_OpenFont("pico-8-mono.ttf",12);

    textRenderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);

    state = SELECT_PROGRAM;


}

void HostGraphic::Update(Chip *chip) {

    int input = GetInput();

    if(backPressed){
        state = SELECT_PROGRAM;
        InitMenu();
    }else{
        stepAccumulator += (double)(SDL_GetTicks() - lastTick) * INSTRUCTIONSPERSECOND * (double)0.001;
        deltaTime =  (double)(SDL_GetTicks() - lastTick) * (double)0.001;
        lastTick = SDL_GetTicks();
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

uint16_t HostGraphic::GetInput() {

    //reset keys
    upPressed = false;
    downPressed = false;
    enterPressed = false;
    backPressed = false;

    SDL_Event e;
    uint16_t inputState = 0;
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

    return inputState;
}

void HostGraphic::Draw(Display *display) {

    //clear screen
    SDL_FillRect( screenSurface, nullptr, colorOff );


    for (int y = 0; y < display->height; y++) {
        for (int x = 0; x < display->width; x++) {
            if(display->data[y*display->width+x]){
                DrawPixel(x,y);
            }
        }
    }
    display->updated=false;

    SDL_UpdateWindowSurface( window );
}


void HostGraphic::DrawPixel(int x, int y) {
    SDL_FillRect(screenSurface,new SDL_Rect{x*SCREENSCALE,y*SCREENSCALE,SCREENSCALE-BORDERSIZE,SCREENSCALE-BORDERSIZE},colorOn);
}


void HostGraphic::LoadProgram(std::string filename, Chip* chip) {
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
}

void HostGraphic::Exit() {
    SDL_DestroyWindow( window );
    SDL_Quit();
}

void HostGraphic::InitMenu() {
    GetPrograms(&programs,PROGRAMDIRECTORY);
    selectedProgram = 0;
}

void HostGraphic::UpdateMenu(Chip *chip) {
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
        } else if (selectedProgram > programs.size()){
            selectedProgram = 0;
        }

        if(enterPressed){
            chip->Init();
            LoadProgram(programs[selectedProgram], chip);
            state = RUN_PROGRAM;
            lastTick = SDL_GetTicks();
        }
    }
}

void HostGraphic::DrawMenu() {
    //SDL_FillRect( screenSurface, nullptr, colorOff );

    SDL_SetRenderDrawColor(textRenderer,COLOR_OFF,0xff);
    SDL_RenderClear(textRenderer);

    SDL_SetRenderDrawColor(textRenderer,COLOR_ON,0xff);

    for (int i = 0; i < programs.size(); ++i) {
        if(i == selectedProgram){

            DrawText("> " + programs[i],10,(SCREENHEIGHT / 2) + ((i-selectedProgram) *24));
        }else{

            DrawText("  " + programs[i],10,(SCREENHEIGHT / 2) + ((i-selectedProgram) *24));
        }
    }

    SDL_RenderPresent(textRenderer);

}

void HostGraphic::DrawText(const std::string& text, int x, int y) {
    textSurface = TTF_RenderUTF8_Solid_Wrapped(font, text.c_str(), {COLOR_ON}, 0);
    TTF_SizeText(font, text.c_str(), &textPosition.w,&textPosition.h);
    textTexture = SDL_CreateTextureFromSurface(textRenderer,textSurface);
    textPosition.x = x;
    textPosition.y = y;

    SDL_RenderCopy(textRenderer, textTexture, nullptr, &textPosition);

}
