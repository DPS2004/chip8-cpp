#include <algorithm>
#include <iostream>
#include <iomanip>

#include "Chip.h"
#include "font.h"

Chip::Chip() {

    mem = new uint8_t[4096]();

    display = new Display();

    pc = 0;
    index = 0;
    //stack

    delay = 0;
    sound = 0;

    v = new uint8_t[16]();

}

void Chip::Init() {
    //load font
    std::copy(font,font+FONT_SIZE,mem+FONT_OFFSET);
    /*
    for (int i = 0; i < 0x512; ++i) {
        std::cout.setf(std::ios::hex, std::ios::basefield);
        std::cout.precision(4);
        std::cout  << std::setfill('0') << std::setw(2) << std::right << mem[i]+0;
    }
    */
}

Display* Chip::GetDisplay() {
    return display;
}
