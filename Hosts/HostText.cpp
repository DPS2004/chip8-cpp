#include <iostream>
#include <fstream>
#include "HostText.h"

void HostText::Init() {
    std::cout << "Text init" << std::endl;
    border = '.';
    borderLine = std::string(CHIPDISPLAYWIDTH+2,border);
    remainingSteps = 0;
}

void HostText::Draw(Display* display) {
    if(!display->updated){
        return;
    }
    //system ("cls");
    std::cout << borderLine << std::endl;
    for (int y = 0; y < CHIPDISPLAYHEIGHT; y++) {
        std::cout << border;
        for (int x = 0; x < CHIPDISPLAYWIDTH; x++) {
            if(display->data[y*CHIPDISPLAYWIDTH+x]){
                std::cout << CELL_ON;
            } else{
                std::cout << CELL_OFF;
            }
        }
        std::cout << border << std::endl;
    }
    std::cout << borderLine;
    std::cout<< std::endl;
    display->updated=false;
}

void HostText::LoadProgram(std::string filename, Chip* chip) {
    std::ifstream programFile(filename,std::ios::in | std::ios::binary);
    uint8_t *program;
    program = new uint8_t[4096-PROGRAM_OFFSET]();
    int size = 0;
    while(programFile.peek() != EOF){
        uint8_t byte = programFile.get();
        program[size] = byte;
        size++;
    }
    chip->LoadProgram(program,size);
}

void HostText::Update(Chip *chip) {
    int input = GetInput();
    if(!stop){
        chip->Step(input);
    }
}

int HostText::GetInput() {
    if(remainingSteps > 0){
        remainingSteps--;
        return -1;
    }

    std::cout <<"input X to step X times, input !X to step once while pressing down X: ";
    std::string input;
    std::cin >> input;
    if(input.empty()) {
        return -1;
    }else if(input == "stop") {
        stop = true;
        return -1;
    }else if(input[0] == '!'){
            std::cout << "inputting " << std::stoi(std::string(1,input[1]),nullptr,16) << std::endl;
            return std::stoi(std::string(1,input[1]),nullptr,16);
    } else{
        remainingSteps = std::stoi(input) - 1;
        return -1;
    }
}

void HostText::Exit() {
    std::cout << "Exiting program..." << std::endl;
}
