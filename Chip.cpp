#include <algorithm>
#include <iostream>
#include <iomanip>

#include "Chip.h"
#include "font.h"

Chip::Chip() {



    pc = 0;
    index = 0;

    stack.clear();

    delay = 0;
    sound = 0;

    v = new uint8_t[16]();

}

void Chip::Init() {

    pc = PROGRAM_OFFSET;

    chipConfig = new ChipConfig("common");
    mem = new uint8_t[chipConfig->memsize]();

    display = new Display(chipConfig->screenwidth,chipConfig->screenheight);

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
            if(nnn == 0x0e0) { //Clear screen
                display->Clear();
            }else if(nnn == 0x0ee) {//return from subroutine
                pc = StackPop();
            }else{
                //Machine code
            }
            break;
        case 0x1: //Jump to nnn
            pc = nnn;
            break;
        case 0x2: //go to subroutine
            StackPush(pc);
            pc = nnn;
            break;
        case 0x3: // skip if vx == nn
            if(v[x] == nn){
                pc += 2;
            }
            break;
        case 0x4: // skip if vx != nn
            if(v[x] != nn){
                pc += 2;
            }
            break;
        case 0x5: //skip if vx == vy
            if(v[x] == v[y]){
                pc += 2;
            }
            break;
        case 0x6: //Set vx to nn
            v[x] = nn;
            //std::cout << "set v" << (int)x << " to " << (int)v[x] << std::endl;
            break;
        case 0x7: //add nn to vx
            v[x] += nn;
            break;
        case 0x8: //mathy stuff
            uint8_t sub_op_1;
            uint8_t sub_op_2;
            uint8_t vf;

            switch (n) {
                case 0x0: //set vx to vy
                    v[x] = v[y];
                    break;
                case 0x1: //binary or
                    v[x] = v[x] | v[y];
                    break;
                case 0x2: //binary and
                    v[x] = v[x] & v[y];
                    break;
                case 0x3: //logical xor
                    v[x] = v[x] ^ v[y];
                    break;
                case 0x4: //add
                    vf = 0;
                    if((int)v[x] + (int)v[y] >= 256) {
                        //set carry flag
                        vf = 1;
                    }
                    v[x] = v[x] + v[y];
                    v[0xf] = vf;
                    break;
                case 0x5:
                    sub_op_1 = x;
                    sub_op_2 = y;
                case 0x7:
                    sub_op_1 = y;
                    sub_op_2 = x;
                    //subtract
                    vf = 1;
                    if((int)v[sub_op_1] - (int)v[sub_op_2] < 0) {
                        //set carry flag
                        vf = 0;
                    }
                    v[x] = v[sub_op_1] - v[sub_op_2];
                    v[0xf] = vf;
                    break;
                    //ignoring shift for now
                default:
                    std::cout << "UNKNOWN MATH INSTRUCTION!\n";
                    break;
            }

        case 0x9: //skip if vx != vy
            if(v[x] != v[y]){
                pc += 2;
            }
            break;
        case 0xa: //set index
            index = nnn;
            //std::cout << "index set to " << index << std::endl;
            break;
        case 0xd: //draw
            v[0xf] = display->Draw(v[x],v[y],n,index,mem);
            break;
        case 0xe: //skip (or dont) if key

            break;
        default:
            //unknown instruction!
            std::cout << "UNKNOWN INSTRUCTION!\n";
            break;

    }
}
