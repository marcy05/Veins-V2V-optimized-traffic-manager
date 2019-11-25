/*
	@author Marcello Sgarbi
	@date 14-Feb-2019
	@update 19-March-2019
*/
#ifndef READINGXML_H
#define READINGXML_H

/*
***************************************************************************************************************************************************************************
*																			INCLUDE FILES
***************************************************************************************************************************************************************************
*/

#include "rapidxml/rapidxml.hpp"
#include "rapidxml/rapidxml_utils.hpp"
#include "../MapFunctions.h"


/*
***************************************************************************************************************************************************************************
*																			FUNCTION PROTOTYPE
***************************************************************************************************************************************************************************
*/
namespace rxml 
{
	/*
		Starting from the output of rapidxml value readed, it allows to convert easely to integer
	*/
	int returnInt(char* value);
	/*
		Starting from the output of rapidxml value readed, it allows to convert easely to double
	*/
	double returnDouble(char* value);
	/*
		Read and store variables form .xml to a std::map that has the same structure of the once that generate the .xml
	*/
	std::map<std::array<double, 4>, std::vector<std::array<std::pair<int, int>, 4>>> readfileXMLSignals(const char* filepath);

	/*
		Read routes from *.rou.xml and based on that get signals (Right = 2, Left = 1, Straight = 0) In order to get them available at a certain distance from the intersection
	*/
	std::map<int, int> vehicleSignals(const char* path);

}




#endif // !READINGXML_H

