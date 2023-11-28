#include <algorithm>
#include <iostream>
#include <iomanip>
#include <cmath>

#include "Chip.h"
#include "font.h"

Chip::Chip() {



    pc = 0;
    index = 0;

    stack.clear();

    delay = 0;
    sound = 0;

    v = new uint8_t[16]();
    inputState = new Keystate[16]();

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

    //reset keys
    for (int i = 0; i < 16; ++i) {
        inputState[i] = up;
    }

    timerAccumulator = 0;
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

void Chip::Step(uint16_t input, double deltaTime) {
    std::cout << "--------------------------------------\n";
    //handle input
    for (int i = 0; i < 16; ++i) {
        if((input & (1<<i)) == (1<<i)){
            //std::cout << i << " is down!\n";
            if(inputState[i] == down || inputState[i] == held){
                inputState[i] = held;
            } else {
                inputState[i] = down;
            }
        } else {
            switch (inputState[i]) {
                case released:
                case up:
                    inputState[i] = up;
                    break;
                case down:
                case held:
                    inputState[i] = released;
                    break;
            }
        }
    }

    //handle timers
    timerAccumulator += deltaTime * 60;
    int stepsToDo = (int)timerAccumulator;
    timerAccumulator = std::fmod(timerAccumulator,1);
    for (int i = 0; i < stepsToDo; ++i) {
        if(delay > 0){
            delay--;
        }
        if(sound > 0){
            sound--;
        }
    }
    
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
                    //subtract
                    vf = 1;
                    if((int)v[x] - (int)v[y] < 0) {
                        //set carry flag
                        vf = 0;
                    }
                    v[x] = v[x] - v[y];
                    v[0xf] = vf;
                    break;
                case 0x7:
                    //subtract
                    vf = 1;
                    if((int)v[y] - (int)v[x] < 0) {
                        //set carry flag
                        vf = 0;
                    }
                    v[x] = v[y] - v[x];
                    v[0xf] = vf;
                    break;
                case 0x6: //shift right
                    if(chipConfig->vyshift){
                        v[x] = v[y];
                    }
                    vf = (v[x]&0x1);
                    v[x] = v[x] >> 1;
                    v[0xf] = vf;
                    break;
                case 0xe: //shift left
                    if(chipConfig->vyshift){
                        v[x] = v[y];
                    }
                    vf = (v[x]>>7);
                    v[x] = v[x] << 1;
                    v[0xf] = vf;

                    break;
                default:
                    std::cout << "UNKNOWN MATH INSTRUCTION!\n";
                    break;
            }
            break;

        case 0x9: //skip if vx != vy
            if(v[x] != v[y]){
                pc += 2;
            }
            break;
        case 0xa: //set index
            index = nnn;
            //std::cout << "index set to " << index << std::endl;
            break;
        case 0xb: //jump with offset
            uint8_t offset;
            offset = 0;
            if(chipConfig->vxoffsetjump){
                offset = x;
            }
            pc = nnn + v[offset];
            break;
        case 0xc: //random
            v[x] = (rand() & nn);
        case 0xd: //draw
            v[0xf] = display->Draw(v[x],v[y],n,index,mem);
            break;
        case 0xe: //skip (or dont) if key
            switch (nn) {
                case 0x9e: //skip if down
                    if(v[x] <= 0xf){
                        if(inputState[v[x]] == down){
                            pc += 2;
                        }
                    }
                    break;
                case 0xa1:
                    if(v[x] <= 0xf){
                        if(inputState[v[x]] != down){
                            pc += 2;
                        }
                    } else {
                        pc += 2;
                    }
                    break;
                default:
                    std::cout << "UNKNOWN 0xE INSTRUCTION!\n";
                    break;
            }

            break;
        case 0xf://misc
            uint8_t looplimit;
            switch (nn) {
                case 0x07://set vx to delay
                    v[x] = delay;
                    break;
                case 0x15://set delay to vx
                    delay = v[x];
                    break;
                case 0x18://set sound to vx
                    sound = v[x];
                    break;
                case 0x1e://add to index
                    if(chipConfig->indexoverflow){
                        if(index + v[x] >= 0x1000){
                            vf = 1;
                        }else {
                            vf = 0;
                        }
                    }
                    index = (index + v[x]) & 0x0fff;
                    if(chipConfig->indexoverflow){
                        v[0xf] = vf;
                    }
                    break;
                case 0x0a://get key
                    pc -= 2;
                    for (int i = 0; i < 16; ++i) {
                        if(chipConfig->waitforrelease){
                            if(inputState[i] == released) {
                                v[x] = i;
                                pc += 2;
                                break;
                            }
                        } else {
                            if(inputState[i] == down){
                                v[x] = i;
                                pc += 2;
                                break;
                            }
                        }
                    }
                    break;
                case 0x29://get font character
                    index = FONT_OFFSET + (v[x] & 0xf)*5;
                    break;
                case 0x33://binary coded decimal (ugh)
                    mem[index] = v[x]/100;
                    mem[index+1] = (v[x]%100)/10;
                    mem[index+2] = (v[x]%10);
                    break;
                case 0x55://store
                    for (int i = 0; i <= x; ++i) {
                        mem[index+i] = v[i];
                    }
                    if(!chipConfig->tempstoreload){
                        index = index + x + 1;
                    }
                    break;
                case 0x65://load
                    for (int i = 0; i <= x; ++i) {
                        v[i] = mem[index+i];
                    }
                    if(!chipConfig->tempstoreload){
                        index = index + x + 1;
                    }
                    break;
                default:
                    std::cout << "UNKNOWN 0xF INSTRUCTION!\n";
                    break;
            }
            break;

        default:
            //unknown instruction!
            std::cout << "UNKNOWN INSTRUCTION!\n";
            break;

    }

    /*
    std::cout << "V: ";
    for (int i = 0; i < 16; ++i) {
        std::cout << (int)v[i] << " ";
    }
    std::cout << "Index: " << index << std::endl;
    */
}
