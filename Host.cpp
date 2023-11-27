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

//Returns 0x0 through 0xf for keys, or -1 for no input at all.
int Host::GetInput() {
    return -1;
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
