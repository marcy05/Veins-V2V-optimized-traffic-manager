#ifndef MAPFUNCTIONS_H
#define MAPFUNCTIONS_H
/*
	@author Marcello Sgarbi
	@date 07-Feb-2019
*/

/*
***************************************************************************************************************************************************************************
*																			INCLUDE FILES
***************************************************************************************************************************************************************************
*/

#include <iostream>
#include <fstream>
#include <array>
#include <map>
#include <vector>
#include "Chess.h"



/*
***************************************************************************************************************************************************************************
*																			FUNCTION PROTOTYPE
***************************************************************************************************************************************************************************
*/
/*
	DATA ORGANIZATION AND FUNCTIONS
	These functions are defined starting from the point that the output vector for the dataset will be organized into a map so defined
															heading1			   heading2			    heading3				heading4
		<(heading1, heading2, heading3, heading4), ( ((position1, signal1), (position2, signal2), (position3, signal3), (position4, signal4)) , ...)>

*/

namespace mapFun
{

	/*	Print the std::map content to command prompt */
	void printMap(std::map<std::array<double, 4>, std::vector<std::array<std::pair<int, int>, 4>>>& mymap);

	/* Print the std::map content to file using the content's structure */
	void printMap2File(std::map<std::array<double, 4>, std::vector<std::array<std::pair<int, int>, 4>>>& mymap, std::string destination);

	/* Print the std::map content to file formatting it as xml */
	void printMap2XML(std::map<std::array<double, 4>, std::vector<std::array<std::pair<int, int>, 4>>>& mymap, std::string destination);

	/* Insert a new array to the value of the map */
	void setMapElement(std::map<std::array<double, 4>, std::vector<std::array<std::pair<int, int>, 4>>>& mymap, std::array<double, 4> key, std::array<std::pair<int, int>, 4> solution);

	/* Search an array among all the stored solutions */
	bool mapSearch(std::map<std::array<double, 4>, std::vector<std::array<std::pair<int, int>, 4>>>& mymap, std::array<double, 4> key, std::array<std::pair<int, int>, 4> solution);

	/* Search for map's key */
	bool headingSearch(std::map<std::array<double, 4>, std::vector<std::array<std::pair<int, int>, 4>>>& mymap, std::array<double, 4> key);

	/* Test all the possible configurations. 
		Arguments: - Chess
				   - mapDataset
				   - destination: if selecting xmlType or mapType a destination myst be specified
				   - mode: 
				   ----xmlType -> print into xml format 
				   ----mapType -> print into readible map format 
				   ----terminal-> print to the terminal
				   ----   ""   -> does not print the result
				   - signal: default 4, it's also possible use 7 to test 7 signals (road side point of view)
		example:    mapFun::testAllPossibility(myChess, mapDataset, 4, "xmlType", "Test.xml");
	*/
	void testAllPossibility(Chess &myChess,	std::map<std::array<double, 4>, std::vector<std::array<std::pair<int, int>, 4>>>& mapDataset,
							int signals = 4, std::string mode = "", std::string destination = "");
}




#endif // !MAPFUNCTIONS_H