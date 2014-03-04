

#include <iostream>
#include <json/writer.h>
#include <cstdlib> //Unnecessary in real version?
#include <random> //Unnecessary in real version
#include <fstream>
#include <unistd.h> //For Sleep(). Unnecessary in real version.

//for output filename stuff
#include <iomanip>
#include <sstream>


int main(){

    Json::Value data;

    srand (time(NULL));

    std::ofstream out_stream;

    for(int year=0; year<5000; year++){
    for(int month=0; month<12; month++){
   
        //Monthly Thermal information 
        data["TempAir"] = rand()%100;
        data["TempOrganicLayer"] = rand()%100;
        data["TempMineralLayer"] = rand()%100;
        data["PAR"] = rand()%100;
        data["ActiveLayerDepth"] = rand()%100;

        //Monthly Hydrodynamic information
        //etc...

        //std::cout << data << std::endl;
        std::cout << "year: "<<year<<", month: "<<month<<std::endl;

        std::stringstream filename;
        filename.fill('0');
        filename << std::setw(4) << year << "_" << std::setw(2) << month << ".json";
        //std::string filename = year.itoa() + "_" + month.itoa() + ".json";
        out_stream.open(filename.str(), std::ofstream::out);

        out_stream << data << std::endl;

        out_stream.close();

        sleep(1);
    }
    }

    std::cout<<std::endl;

    return 0;
}
