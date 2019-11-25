/*
* Project           : VTL
* Author            : Marcello Sgarbi
* Date              : Nov 29, 2018
* Purpose           : Log variable flow in a structured way
*/

#ifndef SRC_VEINS_MODULES_APPLICATION_DATA_STRUCTURE_WRITE_OUT_H
#define SRC_VEINS_MODULES_APPLICATION_DATA_STRUCTURE_WRITE_OUT_H

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include "VehicleData.h"
#include <iomanip>


namespace wrt
{
    // Write a text to in a predefine path
    void wout(std::string &text);
    // Write a text to a predefined file called CarInternalStorage
    void w2Storage(std::string &text, int id, std::string type = "");
    // Write a text to a predefined file called CarInternalStorage without a predefined path
    void w2StoragePhase(std::string &text, std::string type, std::string path);
    // Write a text into a path
    void w2path(std::string text, std::string path);
    /*
        The function allow to print the "storage" of each vehicle in the simulation by passing as parameter
            the ID of the vehicle
        Arguments:
            storage     -> The described datastructure
            path        -> The folder in which the file(s) has(have) to be stored
            id          -> Id of the vehicle to be considered
            mobilityID  -> Allow to print other options. See the write_out.cc for more details
            type        -> If "text" create a file .xml
                           If "csv" create a file .csv 
    */
    void printStorage(std::map<int, VehicleData> storage, std::string path, int id, int mobilityID = -1, std::string type = "text");
}


#endif
