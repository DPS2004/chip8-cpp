#pragma once

#include <cstdint>
#include "Display.h"

//The actual CHIP-8 interpreter
class Chip {
public:
    Chip();
    void Init();
    Display* GetDisplay();
private:

    uint8_t* mem;

    Display* display;

    uint16_t pc;
    uint16_t index;

    //stack

    uint8_t delay;
    uint8_t sound;

    uint8_t* v;


};
