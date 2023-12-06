/*
Author        : Dimitri Sophinos
Class         : CSI - 240 : Advanced Programming
Assignment    : Final project
Due Date      : 12/5/23 11:59PM
*/
/*
Project Description :
Create an interpreter for the CHIP-8 system.

Certification of Authenticity :

I certify that this is entirely my own work, except where I have given
fully-documented references to the work of others. I understand the
definition and consequences of plagiarism and acknowledge that the assessor
of this assignment may, for the purpose of assessing this assignment:
- Reproduce this assignment and provide a copy to another member of
academic staff; and/or
- Communicate a copy of this assignment to a plagiarism checking
service (which may then retain a copy of this assignment on its
database for the purpose of future plagiarism checking)
*/
#pragma once

#include <cstdint>
#include "Display.h"
#include "ChipConfig.h"
#include <vector>

#define PROGRAM_OFFSET 0x200

enum Keystate{
    released,
    up,
    down,
    held
};

//The actual CHIP-8 interpreter
class Chip {
public:
    Chip();
    void Init();
    void LoadProgram(uint8_t* program, int programSize);
    Display* GetDisplay();
    ChipConfig* chipConfig;

    void Step(uint16_t input, double deltaTime);

private:

    uint8_t* mem;

    Keystate* inputState;


    Display* display;

    uint16_t pc;
    uint16_t index;

    std::vector<uint16_t> stack;

    uint8_t delay;
    uint8_t sound;

    double timerAccumulator;

    uint8_t* v;
    void StackPush(uint16_t i);
    uint16_t StackPop();


};
