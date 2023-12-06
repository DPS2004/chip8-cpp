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
#include "Display.h"
#include "Chip.h"

enum HostState{
    SELECT_PROGRAM,
    RUN_PROGRAM,
    STOP
};

//A "host" is a class that controls rendering and input, and file management.
class Host {

public:
    virtual void Init();
    virtual void Update(Chip* chip);
    virtual void Draw(Display* display);

    virtual uint16_t GetInput();

    virtual void LoadProgram(std::string filename, Chip* chip);

    virtual void InitMenu();
    virtual void UpdateMenu(Chip* chip);
    virtual void DrawMenu();

    virtual void Exit();

    void GetPrograms(std::vector<std::string> *programlist, const std::string& dirpath);

    HostState GetState();

protected:
    //bool stop;
    HostState state;
    std::vector<std::string> programs;


};

