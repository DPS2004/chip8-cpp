#pragma once


#include <string>

class ChipConfig {
public:
    ChipConfig();
    ChipConfig(const std::string& filename);
    void LoadConfig(const std::string& filename);

    int screenwidth;
    int screenheight;
    int ips;
    int memsize;
    bool vyshift;
    bool vxoffsetjump;
    bool indexoverflow;
    bool tempstoreload;
    bool waitforrelease;
    bool dotimedupdate;
    int pagesize;
};
