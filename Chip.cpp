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

    stack.clear();

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
    pc = PROGRAM_OFFSET;
}

Display* Chip::GetDisplay() {
    return display;
}

void Chip::StackPush(uint16_t i) {
    //todo: some sort of check for overflow
    stack.push_back(i);
}

uint16_t Chip::StackPop() {
    if(stack.empty()){
        throw std::runtime_error("Tried to pop from empty stack!");
    }
    uint16_t i = stack.back();
    stack.pop_back();
    return i;
}

void Chip::LoadProgram(uint8_t *program, int programSize) {
    std::copy(program,program+programSize, mem+PROGRAM_OFFSET);
}

void Chip::Step(int input) {
    //Fetch

    //get current instruction
    uint8_t b1 = mem[pc];
    uint8_t b2 = mem[pc+1];
    pc += 2;

    //Decode
    uint8_t c = (b1 >> 4);
    uint8_t x = (b1 & 0x0f);
    uint8_t y = (b2 >> 4);
    uint8_t n = (b2 & 0x0f);
    #define nn b2
    uint16_t nnn = ((b1 & 0x0f) << 8) + nn;

    std::cout.setf(std::ios::hex, std::ios::basefield);
    std::cout << "INSTRUCTION: " << (int)c<<(int)x<<(int)y<<(int)n<<" | PC: " <<pc << " | " << std::endl;
    //Execute
    switch (c) {
        case 0x0:
            if(nnn == 0x0e0){ //Clear screen
                display->Clear();
            }else{
                //Machine code
            }
            break;
        case 0x1: //Jump to nnn
            pc = nnn;
            break;
        case 0x6: //Set vx to nn
            v[x] = nn;
            //std::cout << "set v" << (int)x << " to " << (int)v[x] << std::endl;
            break;
        case 0x7: //add nn to vx
            v[x] += nn;
            break;
        case 0xa: //set index
            index = nnn;
            //std::cout << "index set to " << index << std::endl;
            break;
        case 0xd: //draw
            v[0xf] = display->Draw(v[x],v[y],n,index,mem);
            break;
        default:
            //unknown instruction!
            break;

    }
}
