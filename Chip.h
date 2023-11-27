#pragma once

#include <cstdint>
#include "Display.h"
#include "ChipConfig.h"
#include <vector>

#define PROGRAM_OFFSET 0x200

enum Keystate{
    released,
    up,
    down
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
