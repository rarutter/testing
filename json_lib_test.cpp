

#include <iostream>
#include <json/writer.h>
#include <cstdlib>
#include <random>
#include <functional> //for std::bind
#include <fstream>

int main(){

    Json::Value data;

    srand (time(NULL));

    std::default_random_engine generator;
    std::uniform_int_distribution<int> distribution(1,20);
    auto roll = std::bind(distribution, generator);

    std::ofstream out_stream("output.json", std::ofstream::out);

    for(int ii=0; ii<1; ii++){
   
        //Monthly Thermal information 
        data["TempAir"] = roll();
        data["TempOrganicLayer"] = roll();
        data["TempMineralLayer"] = roll(); 
        data["PAR"] = roll();
        data["ActiveLayerDepth"] = roll();

        //Monthly Hydrodynamic information
        //etc...

        out_stream << data << std::endl;

    }

    out_stream.close();

    return 0;
}
