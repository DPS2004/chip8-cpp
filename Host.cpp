#include <iostream>

#include "Host.h"
#include "Chip.h"

void Host::Init() {
    std::cout << "empty host init" << std::endl;
}
//Handles running GetInput, decrementing timers, and stepping CHIP-8.
void Host::Update(Chip* chip) {

}

//Draws the Display class (and possibly more) to the screen.
void Host::Draw(Display* display) {

}

//Returns bitfield based on input
uint16_t Host::GetInput() {
    return 0;
}

//Load a binary program from a file into memory
void Host::LoadProgram(std::string filename, Chip* chip) {

}
//Has the host requested to stop running?
bool Host::GetStop() {
    return stop;
}

void Host::Exit() {

}
