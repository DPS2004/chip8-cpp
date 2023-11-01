#pragma once

#include <cstdint>

#define CHIPDISPLAYWIDTH 64
#define CHIPDISPLAYHEIGHT 32

//Stores the current display state, and functions relating to it.
class Display {
public:
    Display();
    void Clear();
    uint8_t Draw(uint8_t x,uint8_t y, uint8_t n, uint16_t index, uint8_t* mem);
    bool updated;

    bool* data;
};
