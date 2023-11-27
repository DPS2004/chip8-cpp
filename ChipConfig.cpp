#include "ChipConfig.h"
#include <iostream>
#include <fstream>

ChipConfig::ChipConfig(const std::string& filename) {
    LoadConfig(filename);
}

void ChipConfig::LoadConfig(const std::string& filename) {
    std::ifstream input("Configs/"+filename+".txt");
    if(input.good()){
        int paramnumber = 0;
        bool getnextline = false;
        while(!input.eof()){

            std::string line;
            getline(input, line);
            if(!getnextline){

                if(line.back() == ':'){
                    //std::cout << line << std::endl;
                    getnextline = true;
                }
            } else {
                getnextline = false;
                //std:: cout << line << std::endl;
                int lineInt = std::stoi(line);
                bool lineBool = lineInt == 1;
                switch (paramnumber) {
                    case 0:
                        screenwidth = lineInt;
                        break;
                    case 1:
                        screenheight = lineInt;
                        break;
                    case 2:
                        ips = lineInt;
                        break;
                    case 3:
                        memsize = lineInt;
                        break;
                    case 4:
                        vyshift = lineBool;
                        break;
                    case 5:
                        vxoffsetjump = lineBool;
                        break;
                    case 6:
                        indexoverflow = lineBool;
                        break;
                    case 7:
                        tempstoreload = lineBool;
                        break;
                    case 8:
                        waitforrelease = lineBool;
                        break;
                    case 9:
                        dotimedupdate = lineBool;
                        break;
                    case 10:
                        pagesize = lineInt;
                        break;
                    default:
                        std::cout <<"TOO MANY PARAMS " << std::endl;
                        break;
                }
                paramnumber++;

            }
        }
    }else{
        throw std::runtime_error("Could not load file Configs/" + filename + ".txt");
    }
}

ChipConfig::ChipConfig() {
    LoadConfig("common");
}
