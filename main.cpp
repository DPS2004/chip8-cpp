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

#include "Host.h"
#include "Chip.h"

#if HOST_GRAPHIC
    #include "Hosts/HostGraphic.h"
#include "ChipConfig.h"

#endif
#if HOST_TEXT
    #include "Hosts/HostText.h"
#endif

#if HOST_3DS
#include "Hosts/3ds/Host3ds.h"
#endif

int main(int argc, char* args[]) {

    Chip* chip = new Chip;

    //set up host
    Host* host;

#if HOST_GRAPHIC
    host = new HostGraphic;

#endif

#if HOST_TEXT
    host = new HostText;
#endif


#if HOST_3DS
    host = new Host3ds;
#endif

    //chip->Init();

    host->Init();
    //note to self: maybe just make it a CLI program if a menu is too hard.
    //host->LoadProgram("Programs/slipperyslope.ch8", chip);

    host->InitMenu();
    while(host->GetState() != STOP){
        switch (host->GetState()) {

            case SELECT_PROGRAM:
                host->UpdateMenu(chip);
                host->DrawMenu();
                break;
            case RUN_PROGRAM:
                host->Update(chip);
                host->Draw(chip->GetDisplay());
                break;
            case STOP:
                break;
        }
    }

    host->Exit();

    return 0;
}
