#include <iostream>

#include "Host.h"
#include "Chip.h"

#if HOST_GRAPHIC
    #include "Hosts/HostGraphic.h"
#endif
#if HOST_TEXT
    #include "Hosts/HostText.h"
#endif

int main() {

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

    host->Draw(chip->GetDisplay());

    return 0;
}
