

#include <iostream>
#include <json/writer.h>
#include <cstdlib> //Unnecessary in real version?
#include <random> //Unnecessary in real version
#include <fstream>
#include <unistd.h> //For Sleep(). Unnecessary in real version.
#include <sstream>


int main(){

    Json::Value data;

    srand (time(NULL));

    std::ofstream out_stream;

    for(int year=1000; year<2000; year++){//to guarantee 4-digit year values
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
        std::cout << year << " " << month << std::endl;

        std::stringstream filename;
        filename << year << "_" << month << ".json";
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
