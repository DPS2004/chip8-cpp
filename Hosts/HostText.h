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

#include "../Host.h"
#include "../Display.h"

#define CELL_OFF ' '
#define CELL_ON '#'

#define PROGRAMDIRECTORY "Programs/"

class HostText: public Host {
public:
    void Init() override;
    void Update(Chip* chip) override;
    void Draw(Display* display) override;

    void UpdateMenu(Chip* chip) override;
    void DrawMenu() override;

    uint16_t GetInput() override;
    void LoadProgram(std::string filename, Chip* chip)  override;
    void Exit() override;
private:
    int remainingSteps;
    char border;
    std::string borderLine;
};

