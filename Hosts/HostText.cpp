#include <iostream>
#include "HostText.h"

void HostText::Init() {
    std::cout << "Text init" << std::endl;
    border = '.';
    borderLine = std::string(CHIPDISPLAYWIDTH+2,border);
}

void HostText::Draw(Display* display) {
    std::cout << borderLine << std::endl;
    for (int y = 0; y < CHIPDISPLAYHEIGHT; y++) {
        std::cout << border;
        for (int x = 0; x < CHIPDISPLAYWIDTH; x++) {
            if(display->data[y*CHIPDISPLAYHEIGHT+x]){
                std::cout << CELL_ON;
            } else{
                std::cout << CELL_OFF;
            }
        }
        std::cout << border << std::endl;
    }
    std::cout << borderLine;
}
