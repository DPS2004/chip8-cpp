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
#pragma once

#include <cstdint>

#define CHIPDISPLAYWIDTH 64
#define CHIPDISPLAYHEIGHT 32

//Stores the current display state, and functions relating to it.
class Display {
public:
    Display(int w, int h);
    void Clear();
    uint8_t Draw(uint8_t x,uint8_t y, uint8_t n, uint16_t index, uint8_t* mem);
    bool updated;

    bool* data;
    int width;
    int height;
private:
};
