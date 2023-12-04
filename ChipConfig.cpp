#include "ChipConfig.h"
#include <iostream>
#include <fstream>
#include <cstdio>

ChipConfig::ChipConfig(const std::string& filename) {
    LoadConfig(filename);
}

void ChipConfig::LoadConfig(const std::string& filename) {
	std::string filename_fixed = "Configs/";
	filename_fixed.append(filename);
	filename_fixed.append(".txt");
	std::cout << filename_fixed << std::endl;
	configInput.open(filename_fixed,std::ios::in);

    if(configInput.good()){
		std::cout << "config file is good." << std::endl;
        int paramnumber = 0;
        bool getnextline = false;
        while(!configInput.eof()){
			//std::cout << "Not eof" << std::endl;

            std::string line;
            getline(configInput, line);
			//std::cout << line << std::endl;
            if(!getnextline){
                if(line.find(":") != std::string::npos){
                    //std::cout << line << std::endl;
                    getnextline = true;
                }
            } else {
                getnextline = false;
                //std::cout << line << std::endl;
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
	configInput.close();
	std::cout << "Done???" << std::endl;
}

ChipConfig::ChipConfig() {
    LoadConfig("common");
}
