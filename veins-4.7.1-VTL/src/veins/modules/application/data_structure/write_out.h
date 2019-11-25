#ifndef SRC_VEINS_MODULES_APPLICATION_DATA_STRUCTURE_WRITE_OUT_H
#define SRC_VEINS_MODULES_APPLICATION_DATA_STRUCTURE_WRITE_OUT_H

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include "VehicleData.h"
#include <iomanip>
//#include <ctime>

/*
 * #include "veins/modules/messages/BasicSafetyMessage_m.h"
 * #include "veins/modules/messages/WaveShortMessage_m.h"
*/


namespace wrt
{
    void wout(std::string &text);
    void w2Storage(std::string &text, int id, std::string type = "");
    void w2StoragePhase(std::string &text, std::string type, std::string path);
    void w2path(std::string text, std::string path);

    void printStorage(std::map<int, VehicleData> storage, std::string path, int id, int mobilityID = -1, std::string type = "text");
}


#endif
