#pragma once

#include <cstdint>
#include "Display.h"
#include "ChipConfig.h"
#include <vector>

#define PROGRAM_OFFSET 0x200

//The actual CHIP-8 interpreter
class Chip {
public:
    Chip();
    void Init();
    void LoadProgram(uint8_t* program, int programSize);
    Display* GetDisplay();
    ChipConfig* chipConfig;

    void Step(int input);

private:

    uint8_t* mem;


    Display* display;

    uint16_t pc;
    uint16_t index;

    std::vector<uint16_t> stack;

    uint8_t delay;
    uint8_t sound;

    uint8_t* v;
    void StackPush(uint16_t i);
    uint16_t StackPop();


};
