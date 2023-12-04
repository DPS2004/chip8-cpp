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
