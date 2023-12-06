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
