#include <iostream>
#include <fstream>
#include "HostText.h"
#include <dirent.h>

void HostText::Init() {
    std::cout << "Text init" << std::endl;
    border = '.';
    borderLine = std::string(CHIPDISPLAYWIDTH+2,border);
    remainingSteps = 0;
    state = SELECT_PROGRAM;
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
    if(state == RUN_PROGRAM){
        chip->Step(input,((double)1/(double)60));
    }
}

uint16_t HostText::GetInput() {
    if(remainingSteps > 0){
        remainingSteps--;
        return -1;
    }

    std::cout <<"input X to step X times, input !X to step once while pressing down X, or stop to return to menu: ";
    std::string input;
    std::getline(std::cin, input);
    if(input.empty()) {
        return 0;
    }else if(input == "stop") {
        state = SELECT_PROGRAM;
        InitMenu();
        return 0;
    }else if(input[0] == '!'){
            std::cout << "inputting " << std::stoi(std::string(1,input[1]),nullptr,16) << std::endl;
            return 1<<std::stoi(std::string(1,input[1]),nullptr,16);
    } else{
        remainingSteps = std::stoi(input) - 1;
        return 0;
    }
}

void HostText::Exit() {
    std::cout << "Exiting program..." << std::endl;
}

void HostText::UpdateMenu(Chip *chip) {
    //Host::UpdateMenu(chip);
    std::cout << "--------SELECT PROGRAM--------" << std::endl;
    std::cout << "Type the name of a program in the Programs/ directory (with the extension), or type \"stop\" to stop." << std::endl;
    std::string infile;
    std::getline(std::cin, infile);

    if(infile == "stop"){
        state = STOP;
    } else {
        std::ifstream f(PROGRAMDIRECTORY + infile);
        if(f.good()){
            chip->Init();
            std::cout << "Loading " << PROGRAMDIRECTORY << infile << std::endl;
            LoadProgram(PROGRAMDIRECTORY+infile, chip);
            state = RUN_PROGRAM;
        }else{
            std::cout <<"Error while loading " << PROGRAMDIRECTORY << infile << std::endl;
        }
        f.close();
    }


}

void HostText::DrawMenu() {
    Host::DrawMenu();

}
