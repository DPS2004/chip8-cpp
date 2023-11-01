#include <iostream>
#include <cmath>
#include "Display.h"


Display::Display() {
    data = new bool[CHIPDISPLAYWIDTH*CHIPDISPLAYHEIGHT];
    updated = true;
    Clear();
}

void Display::Clear() {
    for (int i = 0; i < CHIPDISPLAYWIDTH*CHIPDISPLAYHEIGHT; i++) {
        data[i] = false;
    }
    updated = true;
}

uint8_t Display::Draw(uint8_t x,uint8_t y, uint8_t n, uint16_t index, uint8_t* mem) {
    //std::cout << "running draw!\n";
    uint8_t vf = 0;
    for (int row = 0; row < n; row++) {
        for (int sx = 0; sx < 8; sx++) {
            int px = (x % CHIPDISPLAYWIDTH) + sx;
            int py = (y % CHIPDISPLAYHEIGHT) + row;
            if(px < CHIPDISPLAYWIDTH && py < CHIPDISPLAYHEIGHT){
                //std::cout << ((mem[index+row] & (128 >> sx))>>(7-sx)) ;
                if(((mem[index+row] & (128 >> sx))>>(7-sx)) == 1){
                    if(data[py*CHIPDISPLAYWIDTH + px]){
                        data[py*CHIPDISPLAYWIDTH + px] = false;
                        vf = 1;
                    }else{
                        data[py*CHIPDISPLAYWIDTH + px] = true;
                    }
                }
            }
        }
    }
    updated = true;
    return vf;
}
