/*
Author        : Dimitri Sophinos
Class         : CSI - 240 : Advanced Programming
Assignment    : Final project
Due Date      : 12/5/23 11:59PM
*/
/*
Project Description :
Create an interpreter for the CHIP-8 system.

Certification of Authenticity :

I certify that this is entirely my own work, except where I have given
fully-documented references to the work of others. I understand the
definition and consequences of plagiarism and acknowledge that the assessor
of this assignment may, for the purpose of assessing this assignment:
- Reproduce this assignment and provide a copy to another member of
academic staff; and/or
- Communicate a copy of this assignment to a plagiarism checking
service (which may then retain a copy of this assignment on its
database for the purpose of future plagiarism checking)
*/
#include <iostream>
#include <cmath>
#include "Display.h"


Display::Display::Display(int w, int h) {
    width = w;
    height = h;
    data = new bool[width*height];
    updated = true;
    Clear();
}

void Display::Clear() {
    for (int i = 0; i < width*height; i++) {
        data[i] = false;
    }
    updated = true;
}

uint8_t Display::Draw(uint8_t x,uint8_t y, uint8_t n, uint16_t index, uint8_t* mem) {
    //std::cout << "running draw!\n";
    uint8_t vf = 0;
    for (int row = 0; row < n; row++) {
        for (int sx = 0; sx < 8; sx++) {
            int px = (x % width) + sx;
            int py = (y % height) + row;
            if(px < width && py < height){
                //std::cout << ((mem[index+row] & (128 >> sx))>>(7-sx)) ;
                if(((mem[index+row] & (128 >> sx))>>(7-sx)) == 1){
                    if(data[py*width + px]){
                        data[py*width + px] = false;
                        vf = 1;
                    }else{
                        data[py*width + px] = true;
                    }
                }
            }
        }
    }
    updated = true;
    return vf;
}

