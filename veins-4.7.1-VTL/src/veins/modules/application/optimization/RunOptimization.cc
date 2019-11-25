#include <veins/modules/application/optimization/RunOptimization.h>


std::vector<std::vector<Car>> runOptimization(std::vector<int> Evehicles, std::vector<int> Esignals,
                                              std::vector<int> Nvehicles, std::vector<int> Nsignals,
                                              std::vector<int> Wvehicles, std::vector<int> Wsignals,
                                              std::vector<int> Svehicles, std::vector<int> Ssignals,
                                              std::map<std::array<double, 4>, std::vector<std::array<std::pair<int, int>, 4>>> mapDataset)
{
	/*******************************************************
	*					Time Test
	********************************************************/
	/*
	clock_t time = clock();
	time = clock() - time;
	std::cout << "execute in: " << time / CLOCKS_PER_SEC << "s" << std::endl;
	*/

	//Chess myChess;
	//std::map<std::array<double, 4>, std::vector<std::array<std::pair<int, int>, 4>>> mapDataset; // { (array heading , vector<array <pair<int,int>, 4>>)
	//std::cout << "find first position responde = " << myChess.findFirstPosition(-3.14) << std::endl;
	/*******************************************************
	*				Create mapDataset
	********************************************************/
	//mapFun::testAllPossibility(myChess, mapDataset, 4, "xmlType", "C:/Users/marce/Desktop/Output_test_chess/OutputXML4Signal.xml");

	/*******************************************************
	*				Initialize mapDataset
	********************************************************/

	//mapDataset = rxml::readfileXMLSignals("C:/Users/marce/Desktop/Output_test_chess/OutputXML4Signal.xml");

	//maptype::iterator it = mapDataset.begin();
	//std::cout << "size = " << it->second.size() << std::endl;


	/*******************************************************
	*				Initialize vehicle data
	********************************************************/
	std::map<double, std::vector<Car>> inputVehicles;
	//std::vector<int> Evehicles = { 1,2,3,4 };
	//std::vector<int> Esignals = { 2,4,3,4 };

	//std::vector<int> Nvehicles = { 1,2,3,4 };
	//std::vector<int> Nsignals = { 2,4,3,2 };

	//std::vector<int> Wvehicles = { 1,2,3 };
	//std::vector<int> Wsignals = { 4,4, 2 };

	//std::vector<int> Svehicles = { 1,2 };
	//std::vector<int> Ssignals = { 4,2 };

	if(Evehicles.size() == 0) { Evehicles = {}; }
    if(Esignals.size() == 0) { Esignals = {}; }
    if(Nvehicles.size() == 0) {Nvehicles = {}; }
    if(Nsignals.size() == 0) {Nsignals = {}; }
    if(Wvehicles.size() == 0) {Wvehicles = {}; }
    if(Wsignals.size() == 0) {Wsignals = {}; }
    if(Svehicles.size() == 0) {Svehicles = {}; }
    if(Ssignals.size() == 0) {Ssignals = {}; }

	inputVehicles = opt::carInMap(Evehicles, Esignals, Nvehicles, Nsignals, Wvehicles, Wsignals, Svehicles, Ssignals);

	/*************************************************************************************************************************************
	*												Test with iteration the
	*										updating of the queue and solutions test
	*************************************************************************************************************************************/


	std::map<int, std::vector<Car>> iterativeVehicleMap = opt::mapVehicleByCircle(inputVehicles);
	std::vector<std::vector<Car>> testedSolution;

	std::map<int, std::vector<std::vector<std::vector<Car>>>> fullSolutions;
	/*************************************************************************************************************************************
	* Compute the Recursion to find out the solutions that allow the flow of the maximum number of vehicles. The output is the FullSolution map which contains the configuration for each circle,
	*    those solutions are stored into the map so that depending on how many staps I take to empty the intersection
	*
	* The solutions that rapresents the maximum number of passing vehicls are those contained into the first key of the map
	*************************************************************************************************************************************/
	bool escape = false;
    double time = omnetpp::simTime().dbl();
	
	opt::recursive(iterativeVehicleMap, testedSolution, fullSolutions, mapDataset, escape, time);
	
	//Setting the start and stop for each solution finded in the previous recursive
	opt::startAndStopUpdate(fullSolutions);


	
	//Choose the solution
	std::vector<std::vector<Car>> chosenSolution = opt::chooseMinStartStop(fullSolutions);

	return chosenSolution;


	

/*




	std::string path = "C:/Users/marce/Desktop/Output_test_chess/AllSolutions.xml";
	std::ofstream myfile(path, std::ios::app);

	myfile << "Chosen solution:" << std::endl;
	opt::printVectorVector(chosenSolution, path);
	myfile << "Own Start & Stop" << std::endl;
	opt::printVectorVector(chosenSolution, path, "ss");


	myfile << std::endl;
	// Counting the number of solutions
	int SolCounter = 0;
	for (std::map<int, std::vector<std::vector<std::vector<Car>>>>::iterator it = fullSolutions.begin(); it != fullSolutions.end(); ++it) {
		SolCounter += static_cast<int>(it->second.size());
	}
	myfile << "Founded Solutions: " << SolCounter << std::endl;

	// Printing outputs on a file
	for (std::map<int, std::vector<std::vector<std::vector<Car>>>>::iterator it = fullSolutions.begin(); it != fullSolutions.end(); ++it)
	{
		myfile << "Number of steps = " << it->first << std::endl;
		for (std::vector<std::vector<std::vector<Car>>>::iterator sit = it->second.begin(); sit != it->second.end(); ++sit)
		{
			opt::printVectorVector(*sit, path);
			opt::printVectorVector(*sit, path, "ss");
			myfile << std::endl;
		}

	}
	*/
}
