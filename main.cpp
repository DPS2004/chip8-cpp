#include <iostream>

#include "Host.h"
#include "Chip.h"

#if HOST_GRAPHIC
    #include "Hosts/HostGraphic.h"
#endif
#if HOST_TEXT
    #include "Hosts/HostText.h"
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

    chip->Init();

    host->Init();
    host->LoadProgram("Programs/ibm.ch8", chip);

    while(!host->GetStop()){
        host->Update(chip);
        host->Draw(chip->GetDisplay());
    }

    host->Exit();

    return 0;
}
