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
#include <dirent.h>

#include "Host.h"
#include "Chip.h"

void Host::Init() {
    std::cout << "empty host init" << std::endl;
}
//Handles running GetInput, decrementing timers, and stepping CHIP-8.
void Host::Update(Chip* chip) {

}

//Draws the Display class (and possibly more) to the screen.
void Host::Draw(Display* display) {

}

//Returns bitfield based on input
uint16_t Host::GetInput() {
    return 0;
}

//Load a binary program from a file into memory
void Host::LoadProgram(std::string filename, Chip* chip) {

}

//Get current state of the host
HostState Host::GetState() {
    return state;
}


void Host::Exit() {

}

void Host::UpdateMenu(Chip *chip) {

}

void Host::DrawMenu() {

}

//adapted from FAKE-08 listcarts routine
//https://github.com/jtothebell/fake-08/blob/d52e9ba89ca25e70b94cf8872aad7931f4184e5f/platform/3ds/source/3dsHost.cpp#L719
void Host::GetPrograms(std::vector<std::string> *programlist, const std::string& dirpath) {
    programlist->clear();
    DIR *dir = opendir(dirpath.c_str());
    struct dirent *ent;
    if(dir){
        while((ent = readdir(dir)) != nullptr){
            std::string filename = ent->d_name;
            if(filename.length() >= 4 && filename.substr(filename.length() - 4) == ".ch8"){
                programlist->push_back(dirpath + "/" + filename);
            }
        }
        closedir(dir);
    }
}

void Host::InitMenu() {

}
