#pragma once

#include <cstdint>

//The actual CHIP-8 interpreter
class Chip {
public:
    Chip();
private:
    uint16_t pc;
    uint16_t index;
    uint8_t* v;
};
