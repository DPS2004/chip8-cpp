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


}

void HostGraphic::Update(Chip *chip) {

    int input = GetInput();


    stepAccumulator += (double)(SDL_GetTicks() - lastTick) * INSTRUCTIONSPERSECOND * (double)0.001;
    lastTick = SDL_GetTicks();
    int stepsToDo = (int)stepAccumulator;
    stepAccumulator = std::fmod(stepAccumulator,1);
    //std::cout << stepAccumulator << std::endl;
    //std::cout << (float)stepsToDo << std::endl;
    if(!stop){
        for (int i = 0; i < stepsToDo; ++i) {
            chip->Step(input);
        }
    }

}

int HostGraphic::GetInput() {

    SDL_Event e;
    while( SDL_PollEvent( &e ) != 0 )
    {
        if( e.type == SDL_QUIT )
        {
            stop = true;
        }
    }

    return -1;
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
