#include "hexManagement.h"

std::string hexRem(int rem)
{
	if (rem < 10) {
		return std::to_string(rem);
	}
	else
	{
		switch (rem)
		{
		case 10:
			return "A";
			break;
		case 11:
			return "B";
			break;
		case 12:
			return "C";
			break;
		case 13:
			return "D";
			break;
		case 14:
			return "E";
			break;
		case 15:
			return "F";
			break;
		}
	}
}


int decEquivalent(const char* value)
{
	if (*value == '0') { return 0; }
	if (*value == '1') { return 1; }
	if (*value == '2') { return 2; }
	if (*value == '3') { return 3; }
	if (*value == '4') { return 4; }
	if (*value == '5') { return 5; }
	if (*value == '6') { return 6; }
	if (*value == '7') { return 7; }
	if (*value == '8') { return 8; }
	if (*value == '9') { return 9; }
	if (*value == 'A') { return 10; }
	if (*value == 'B') { return 11; }
	if (*value == 'C') { return 12; }
	if (*value == 'D') { return 13; }
	if (*value == 'E') { return 14; }
	if (*value == 'F') { return 15; }

}

std::string dec2hex(int value, int prefix)
{
	// If prefix = 0 no prefix is setted to the returned value, otherwise 0x is added
	std::string rem;
	if (value < 16) {
		if (prefix == 0) {
			return hexRem(value);
		}
		else {
			return "0x" + hexRem(value);
		}
	}
	else {
		while (value / 16 != 0) {
			rem += hexRem(value % 16);
			value /= 16;
		}
		rem += hexRem(value % 16);
	}
	std::string aux = "";
	for (int i = rem.size() - 1; i >= 0; i--) {
		aux += rem.at(i);
	}
	if (prefix == 0) {
		rem = aux;
	}
	else {
		rem = "0x" + aux;
	}
	return rem;
}

int hex2dec(std::string value)
{
	int output = 0;
	int counter = 0;
	for (int i = (value.size() - 1); i >= 0; i--)
	{
		output += decEquivalent(&value.at(i)) * static_cast<int>(std::pow(16, counter));
		counter += 1;
	}

	return output;

}


bool isEqualLeadersStringMap(std::map<int, std::string> leadersMap)
{
    int maxsize = 0;
    for (std::map<int, std::string>::iterator it = leadersMap.begin(); it != leadersMap.end(); ++it)
    {
        if (maxsize < strlen(it->second.c_str())) {
            maxsize = strlen(it->second.c_str());
        }
    }

    int mapsize = leadersMap.size();
    int equalityCounter = 0;
    std::map<int, std::string>::iterator first = leadersMap.begin();
    for (std::map<int, std::string>::iterator it = leadersMap.begin(); it != leadersMap.end(); ++it)
    {
        if (strncmp(first->second.c_str(), it->second.c_str(), maxsize) == 0) {
            equalityCounter += 1;
        }
    }

    if (mapsize == equalityCounter) {
        return true;
    }
    return false;
}

/*
bool isIdPresent(std::string ids, int myId)
{
    std::string received = ids;

    std::vector<int> receivedVect = hexStrigSequence2intVector(received);

    if (std::find(receivedVect.begin(), receivedVect.end(), myId) != receivedVect.end()) {
        return true;
    }
    return false;
}
*/



std::string vmc2bit(VehicleMainChar veh)
{
    /*
        The bit string that will be transmittet is formatted as follow:
            16bit -> id
            3bit  -> queue position of the vehicle
            3bit  -> signaling of the vehicle
            9bit  -> heading without sign
            1bit  -> sign of the heading for positive or negative angles

            id-queuePosition-Signal-Heading-headingSign
    */

    //Convert in bit the vehicle characteristics
    std::bitset<16> bitId(veh.m_id);
    std::bitset<3> bitQueue(veh.m_queuePosition);
    std::bitset<3> bitSignal(veh.m_signal);
    std::bitset<9> bitHeadingValue(abs(veh.m_heading * 100));
    std::bitset<1> bitHeadingSign;
    std::string outputString = "";

    //Check if the heading has a minus sign or not and set 0 if it is positive otherwise 1
    if (veh.m_heading >= 0) {
        bitHeadingSign = 0;
    }
    if (veh.m_heading < 0) {
        bitHeadingSign = 1;
    }

    //Convert the id into bit string
    std::string finalBitString = bitId.to_string();

    //Convert the queue position in string bit and append it to the final string
    std::string queueStr = bitQueue.to_string();
    finalBitString += queueStr;

    //Convert the signaling in string bit and append it to the final string
    std::string signalStr = bitSignal.to_string();
    finalBitString += signalStr;

    //Convert the heading in string bit and append it to the final string
    std::string headingValueStr = bitHeadingValue.to_string();
    finalBitString += headingValueStr;
    finalBitString += bitHeadingSign.to_string();


    return finalBitString;
}



std::string vmcVector2bit(std::vector<VehicleMainChar> vector)
{
    std::string outString = "";

    for (std::vector<VehicleMainChar>::iterator it = vector.begin(); it != vector.end(); ++it)
    {
        outString += vmc2bit(*it);
    }

    return outString;
}


std::string vmcMap2bit(std::map<int, VehicleMainChar> mappa)
{
    std::string outString = "";
    for(std::map<int, VehicleMainChar>::iterator it = mappa.begin(); it != mappa.end(); ++it)
    {
        outString += vmc2bit(it->second);
    }

    return outString;
}


std::vector<VehicleMainChar> bitString2vmc(std::string inputstring)
{
    std::vector<VehicleMainChar> outputVector = {};
    std::vector<std::string> extractedString = {};

    //Devide all the strigns
    for (int i = 0; i < inputstring.length(); i += 32)
    {
        extractedString.push_back(inputstring.substr(i, i+32));
    }

    //Create a vector of structure based on the input string
    for (std::vector<std::string>::iterator it = extractedString.begin(); it != extractedString.end(); ++it)
    {
        //Extraction of the id
        std::bitset<16> id(it->substr(0, 16));
        //Extraction of the queue position
        std::bitset<3> queuePosition(it->substr(16, 3));
        //Extraction of the signal
        std::bitset<3> signal(it->substr(19, 3));
        // heading multiplier based on heading sign
        int headingSign = std::stoi(it->substr(31, 1));
        std::bitset<9> heading(it->substr(22, 9));

        VehicleMainChar aux;

        if (headingSign == 0) {
            aux.initializer(id.to_ulong(), queuePosition.to_ulong(), signal.to_ulong(), static_cast<double>(heading.to_ulong()) / 100);
        }
        else {
            aux.initializer(id.to_ulong(), queuePosition.to_ulong(), signal.to_ulong(), static_cast<double>(heading.to_ulong())*(-1) / 100);
        }

        outputVector.push_back(aux);

    }

    return outputVector;
}



bool isMyIdInString(std::string inputstring, int myId)
{
    std::vector<VehicleMainChar> received = bitString2vmc(inputstring);

    for(std::vector<VehicleMainChar>::iterator it = received.begin(); it != received.end(); ++it)
    {
        if(myId == it->m_id){
            return true;
        }
    }
    return false;
}

/*
std::vector<int> hexStrigSequence2intVector(std::string ids)
{
    // This function is thought to be used to insert a string of hexadeciml as: std::string ids = "0x50x80xF";
    //      and give as output a vector containing all the ids coded in hexadecimal format

    // 1) Search for the first character position after 0x
    std::vector<int> beginnings = {};
    for (int i = 0; i < ids.size() - 1; i++) {
        if (ids.at(i) == '0' && ids.at(i + 1) == 'x') {
            if (i + 2 <= ids.size()) {
                beginnings.push_back(i + 2);
            }
        }
    }

    // 2) Collect all the hexadecimal, convert them into integer values and store them into a vector
    std::string aux = "";
    std::vector<int> idsVector = {};
    for (int i = 0; i < beginnings.size() - 1; ++i)
    {
        aux = ids.substr(beginnings.at(i), beginnings.at(i + 1) - 2 - beginnings.at(i));
        idsVector.push_back(hex2dec(aux));

    }
    aux = ids.substr(beginnings.back(), ids.size() - 1);
    idsVector.push_back(hex2dec(aux));

    return idsVector;
}
*/

/*
std::vector<VehicleMainChar> hexStrigSequence2MainCharVector(std::string id_QueuePosition_Signal_Heading)
{
    // This function is thought to be used to insert a string of hexadeciml as: std::string ids = "0x50x80xF";
    //      and give as output a vector containing all the id_QueuePosition_Signal_Heading coded in hexadecimal format

    // 1) Search for the first character position after 0x
    std::vector<int> beginnings = {};
    for (int i = 0; i < id_QueuePosition_Signal_Heading.size() - 1; i++) {
        if (id_QueuePosition_Signal_Heading.at(i) == '0' && id_QueuePosition_Signal_Heading.at(i + 1) == 'x') {
            if (i + 2 <= id_QueuePosition_Signal_Heading.size()) {
                beginnings.push_back(i + 2);
            }
        }
    }

    // 2) Collect all the hexadecimal, convert them into integer values and store them into a vector
    std::string aux = "";
    std::vector<int> idsVector = {};
    std::vector<VehicleMainChar> codifiedVector = {};
    for (int i = 0; i < beginnings.size() - 1; ++i)
    {
        if(idsVector.size() == 4)
        {
            VehicleMainChar aux(idsVector.at(0), idsVector.at(1), idsVector.at(2), (static_cast<double>(idsVector.at(3))/100) );
            codifiedVector.push_back(aux);
            idsVector = {};
        }
        aux = id_QueuePosition_Signal_Heading.substr(beginnings.at(i), beginnings.at(i + 1) - 2 - beginnings.at(i));
        idsVector.push_back(hex2dec(aux));

    }
    aux = id_QueuePosition_Signal_Heading.substr(beginnings.back(), id_QueuePosition_Signal_Heading.size() - 1);
    idsVector.push_back(hex2dec(aux));
    VehicleMainChar aux2(idsVector.at(0), idsVector.at(1), idsVector.at(2), (static_cast<double>(idsVector.at(3))/100) );
    codifiedVector.push_back(aux2);

    return codifiedVector;
}
*/
