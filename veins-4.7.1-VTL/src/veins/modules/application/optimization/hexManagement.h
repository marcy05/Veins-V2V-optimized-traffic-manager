#ifndef HEXMAAGEMENT_H
#define HEXMAAGEMENT_H

#include <string>
#include <string.h>
#include <vector>
#include <iterator>
#include <math.h>
#include <map>
#include <algorithm>
#include <bitset>
#include "VehicleMainCharacteristics.h"


std::string hexRem(int rem);
int decEquivalent(const char* value);
std::string dec2hex(int value, int prefix = 0);
int hex2dec(std::string value);
bool isEqualLeadersStringMap(std::map<int, std::string> leadersMap);

//bool isIdPresent(std::string ids, int myId);

std::string vmc2bit(VehicleMainChar veh);
std::string vmcVector2bit(std::vector<VehicleMainChar> vector);
std::string vmcMap2bit(std::map<int, VehicleMainChar> mappa);
std::vector<VehicleMainChar> bitString2vmc(std::string inputstring);
bool isMyIdInString(std::string inputstring, int myId);

/*
std::vector<int> hexStrigSequence2intVector(std::string ids);
std::vector<VehicleMainChar> hexStrigSequence2MainCharVector(std::string id_QueuePosition_Signal_Heading);

*/
#endif // !HEXMAAGEMENT_H


