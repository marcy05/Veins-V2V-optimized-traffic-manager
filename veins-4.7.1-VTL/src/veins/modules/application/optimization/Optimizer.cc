/*
	@author Marcello Sgarbi
	@date 15-Feb-2019
	@updated 19-Feb-2019
	@updated 11-March-2019
*/

#include "Optimizer.h"


//		CarInMap
std::map<double, std::vector<Car>> opt::carInMap(std::vector<int> Evehicles, std::vector<int> Esignals, std::vector<int> Nvehicles, std::vector<int> Nsignals, std::vector<int> Wvehicles, std::vector<int> Wsignals, std::vector<int> Svehicles, std::vector<int> Ssignals)
{
	std::map<double, std::vector<Car>> inputVehciles;
	for (std::vector<int>::iterator it = Evehicles.begin(); it != Evehicles.end(); ++it) {
		double heading = -3.14;
		Car vehicle = Car(heading, *it);
		vehicle.setSignal(Esignals.at(std::distance(Evehicles.begin(), it)));
		inputVehciles[heading].push_back(vehicle);
	}
	for (std::vector<int>::iterator it = Nvehicles.begin(); it != Nvehicles.end(); ++it) {
		double heading = -1.57;
		Car vehicle = Car(heading, *it);
		vehicle.setSignal(Nsignals.at(std::distance(Nvehicles.begin(), it)));
		inputVehciles[heading].push_back(vehicle);
	}
	for (std::vector<int>::iterator it = Wvehicles.begin(); it != Wvehicles.end(); ++it) {
		double heading = 0.0;
		Car vehicle = Car(heading, *it);
		vehicle.setSignal(Wsignals.at(std::distance(Wvehicles.begin(), it)));
		inputVehciles[heading].push_back(vehicle);
	}
	for (std::vector<int>::iterator it = Svehicles.begin(); it != Svehicles.end(); ++it) {
		double heading = 1.57;
		Car vehicle = Car(heading, *it);
		vehicle.setSignal(Ssignals.at(std::distance(Svehicles.begin(), it)));
		inputVehciles[heading].push_back(vehicle);
	}
	return inputVehciles;
}

//		CarInMap2Chess
void opt::carInMap2Chess(Chess& myChess, std::map<double, std::vector<Car>> inputVehciles)
{
	for (std::map<double, std::vector<Car>>::iterator it = inputVehciles.begin(); it != inputVehciles.end(); ++it)
	{
		for (std::vector<Car>::iterator sit = it->second.begin(); sit != it->second.end(); ++sit)
		{
			myChess.setCarStart(sit->getHeading(), sit->getQueuePosition());
			//std::cout << "heading = " << sit->getHeading() << " position = " << sit->getQueuePosition() << " signal = " << sit->getSignal() << std::endl;
		}
	}
}

//		mapVehicleByCircle
std::map<int, std::vector<Car>> opt::mapVehicleByCircle(std::map<double, std::vector<Car>>& inputVector, std::string print)
{
	int row = 1;
	std::map<int, std::vector<Car>> mapVehByCircle;
	std::vector<Car> east;
	std::vector<Car> nord;
	std::vector<Car> west;
	std::vector<Car> south;

	for (std::map<double, std::vector<Car>>::iterator it = inputVector.begin(); it != inputVector.end(); ++it)
	{
		if (carUtility::checkHeading(it->first) == 1) { east = it->second; }
		if (carUtility::checkHeading(it->first) == 2) { nord = it->second; }
		if (carUtility::checkHeading(it->first) == 3) { west = it->second; }
		if (carUtility::checkHeading(it->first) == 4) { south = it->second; }
	}

	int maxSize = 0;
	if (east.size() > maxSize) { maxSize = static_cast<int>(east.size()); }
	if (nord.size() > maxSize) { maxSize = static_cast<int>(nord.size()); }
	if (west.size() > maxSize) { maxSize = static_cast<int>(west.size()); }
	if (south.size() > maxSize) { maxSize = static_cast<int>(south.size()); }

	for (int i = 0; i < maxSize; ++i)
	{
		if (east.size() >= (i + 1)) {
			if (mapVehByCircle.find(i + 1) == mapVehByCircle.end()) 
			{
				std::vector<Car> aux;
				aux.push_back(east.at(i));
				mapVehByCircle[i + 1] = aux;
			}
			else { mapVehByCircle[i + 1].push_back(east.at(i)); }
		}
		if (nord.size() >= (i + 1)) {
			if (mapVehByCircle.find(i + 1) == mapVehByCircle.end())
			{
				std::vector<Car> aux;
				aux.push_back(nord.at(i));
				mapVehByCircle[i + 1] = aux;
			}
			else { mapVehByCircle[i + 1].push_back(nord.at(i)); }
		}
		if (west.size() >= (i + 1))
		{
			if (mapVehByCircle.find(i + 1) == mapVehByCircle.end())
			{
				std::vector<Car> aux;
				aux.push_back(west.at(i));
				mapVehByCircle[i + 1] = aux;
			}
			else { mapVehByCircle[i + 1].push_back(west.at(i)); }
		}
		if (south.size() >= (i + 1))
		{
			if (mapVehByCircle.find(i + 1) == mapVehByCircle.end())
			{
				std::vector<Car> aux;
				aux.push_back(south.at(i));
				mapVehByCircle[i + 1] = aux;
			}
			else { mapVehByCircle[i + 1].push_back(south.at(i)); }
		}

	}

	//Printing opions, disabled by default
	if (print == "console")
	{
		for (std::map<int, std::vector<Car>>::iterator pit = mapVehByCircle.begin(); pit != mapVehByCircle.end(); ++pit)
		{
			std::cout << "queue = " << pit->first << std::endl;
			for (std::vector<Car>::iterator spit = pit->second.begin(); spit != pit->second.end(); ++spit)
			{
				std::cout << "\theading = " << spit->getHeading() << " position = " << spit->getQueuePosition() << " signal = " << spit->getSignal() << std::endl;
			}
		}
	}
	return mapVehByCircle;
}



//		possibleSolXCircle
std::map<int, std::vector<std::vector<Car>>> opt::possibleSolXCircle(std::vector<Car> circle, std::map<std::array<double, 4>, std::vector<std::array<std::pair<int, int>, 4>>> mapDataset, std::string printOption)
{
	std::array<double, 4> key = { -3.14, -1.57, 0.0, 1.57 };

	int maxqueuepos = 0;
	for (std::vector<Car>::iterator it = circle.begin(); it != circle.end(); ++it)
	{
		if (it->getQueuePosition() > maxqueuepos) maxqueuepos = it->getQueuePosition();
	}
	std::map<int, std::vector<std::vector<Car>>> solutionMap;

	for (std::vector<std::array<std::pair<int, int>, 4>>::iterator datait = mapDataset[key].begin(); datait != mapDataset[key].end(); ++datait)
	{
		int counter = 0;
		int ones = 0;
		// Check that the position of my vehicles is the same of the one in the Dataset
		switch (circle.size())
		{
		case 1:
			if (circle.at(0).getQueuePosition() == datait->at(carUtility::checkHeading(circle.at(0).getHeading()) - 1).first) {
				for (std::vector<Car>::iterator sit = circle.begin(); sit != circle.end(); ++sit) {
					std::vector<Car> sol1;
					if (sit->getSignal() == datait->at(carUtility::checkHeading(sit->getHeading()) - 1).second) {
						counter += 1;
					}
					if (sit == (circle.end() - 1) && counter > 0) {
						//Test signals equaliti or 1 in mapped
						std::vector<double> headings = { -3.14, -1.57, 0.0, 1.57 };
						opt::possibleHeading(headings, circle.at(0).getHeading());
						if ((circle.at(0).getSignal() == datait->at(carUtility::checkHeading(circle.at(0).getHeading()) - 1).second || datait->at(carUtility::checkHeading(circle.at(0).getHeading()) - 1).second == 1) && (datait->at(carUtility::checkHeading(headings.at(0)) - 1).second == 1) && (datait->at(carUtility::checkHeading(headings.at(1)) - 1).second == 1) && (datait->at(carUtility::checkHeading(headings.at(2)) - 1).second == 1))
						{
							if (datait->at(0).first <= maxqueuepos && datait->at(1).first <= maxqueuepos && datait->at(2).first <= maxqueuepos && datait->at(3).first <= maxqueuepos && datait->at(carUtility::checkHeading(headings.at(0)) - 1).first == 1 && datait->at(carUtility::checkHeading(headings.at(1)) - 1).first == 1 && datait->at(carUtility::checkHeading(headings.at(2)) - 1).first == 1)
							{
								//sol1 = { datait->at(0).first, datait->at(0).second, datait->at(1).first, datait->at(1).second, datait->at(2).first, datait->at(2).second, datait->at(3).first, datait->at(3).second };
								Car aux0(-3.14, datait->at(0).first, datait->at(0).second);
								Car aux1(-1.57, datait->at(1).first, datait->at(1).second);
								Car aux2(0.0, datait->at(2).first, datait->at(2).second);
								Car aux3(1.57, datait->at(3).first, datait->at(3).second);

								sol1 = { aux0, aux1, aux2, aux3 };
								std::map<int, std::vector<std::vector<Car>>>::iterator fit = solutionMap.find(counter);
								if (fit == solutionMap.end()) {
									std::vector<std::vector<Car>> sol2 = { sol1 };
									solutionMap[counter] = sol2;
								}
								else { fit->second.push_back(sol1); }
							}
						}
					}
				}
			}
			break;
		case 2:
			if (circle.at(0).getQueuePosition() == datait->at(carUtility::checkHeading(circle.at(0).getHeading()) - 1).first && circle.at(1).getQueuePosition() == datait->at(carUtility::checkHeading(circle.at(1).getHeading()) - 1).first)
			{
				for (std::vector<Car>::iterator sit = circle.begin(); sit != circle.end(); ++sit) {
					std::vector<Car> sol1;
					if (sit->getSignal() == datait->at(carUtility::checkHeading(sit->getHeading()) - 1).second) {
						counter += 1;
					}
					if (sit == (circle.end() - 1) && counter > 0) {
						//Test signals equaliti or 1 in mapped
						std::vector<double> headings = { -3.14, -1.57, 0.0, 1.57 };
						opt::possibleHeading(headings, circle.at(0).getHeading(), circle.at(1).getHeading());
						if ((circle.at(0).getSignal() == datait->at(carUtility::checkHeading(circle.at(0).getHeading()) - 1).second || datait->at(carUtility::checkHeading(circle.at(0).getHeading()) - 1).second == 1) && (circle.at(1).getSignal() == datait->at(carUtility::checkHeading(circle.at(1).getHeading()) - 1).second || datait->at(carUtility::checkHeading(circle.at(1).getHeading()) - 1).second == 1) && (datait->at(carUtility::checkHeading(headings.at(0)) - 1).second == 1) && (datait->at(carUtility::checkHeading(headings.at(1)) - 1).second == 1))
						{
							if (datait->at(0).first <= maxqueuepos && datait->at(1).first <= maxqueuepos && datait->at(2).first <= maxqueuepos && datait->at(3).first <= maxqueuepos && datait->at(carUtility::checkHeading(headings.at(0)) - 1).first == 1 && datait->at(carUtility::checkHeading(headings.at(1)) - 1).first == 1)
							{
								//sol1 = { datait->at(0).first, datait->at(0).second, datait->at(1).first, datait->at(1).second, datait->at(2).first, datait->at(2).second, datait->at(3).first, datait->at(3).second };
								Car aux0(-3.14, datait->at(0).first, datait->at(0).second);
								Car aux1(-1.57, datait->at(1).first, datait->at(1).second);
								Car aux2(0.0, datait->at(2).first, datait->at(2).second);
								Car aux3(1.57, datait->at(3).first, datait->at(3).second);

								sol1 = { aux0, aux1, aux2, aux3 };
								std::map<int, std::vector<std::vector<Car>>>::iterator fit = solutionMap.find(counter);
								if (fit == solutionMap.end()) {
									std::vector<std::vector<Car>> sol2 = { sol1 };
									solutionMap[counter] = sol2;
								}
								else { fit->second.push_back(sol1); }
							}
						}
					}
				}
			}
			break;
		case 3:
			if (circle.at(0).getQueuePosition() == datait->at(carUtility::checkHeading(circle.at(0).getHeading()) - 1).first && circle.at(1).getQueuePosition() == datait->at(carUtility::checkHeading(circle.at(1).getHeading()) - 1).first && circle.at(2).getQueuePosition() == datait->at(carUtility::checkHeading(circle.at(2).getHeading()) - 1).first)
			{
				for (std::vector<Car>::iterator sit = circle.begin(); sit != circle.end(); ++sit) {
					std::vector<Car> sol1;
					if (sit->getSignal() == datait->at(carUtility::checkHeading(sit->getHeading()) - 1).second) {
						counter += 1;
					}
					if (sit == (circle.end() - 1) && counter > 0) {
						//Test signals equaliti or 1 in mapped
						std::vector<double> headings = { -3.14, -1.57, 0.0, 1.57 };
						opt::possibleHeading(headings, circle.at(0).getHeading(), circle.at(1).getHeading(), circle.at(2).getHeading());
						if ((circle.at(0).getSignal() == datait->at(carUtility::checkHeading(circle.at(0).getHeading()) - 1).second || datait->at(carUtility::checkHeading(circle.at(0).getHeading()) - 1).second == 1) && (circle.at(1).getSignal() == datait->at(carUtility::checkHeading(circle.at(1).getHeading()) - 1).second || datait->at(carUtility::checkHeading(circle.at(1).getHeading()) - 1).second == 1) && (circle.at(2).getSignal() == datait->at(carUtility::checkHeading(circle.at(2).getHeading()) - 1).second || datait->at(carUtility::checkHeading(circle.at(2).getHeading()) - 1).second == 1) && (datait->at(carUtility::checkHeading(headings.at(0)) - 1).second == 1))
						{
							if (datait->at(0).first <= maxqueuepos && datait->at(1).first <= maxqueuepos && datait->at(2).first <= maxqueuepos && datait->at(3).first <= maxqueuepos && datait->at(carUtility::checkHeading(headings.at(0)) - 1).first == 1)
							{
								//sol1 = { datait->at(0).first, datait->at(0).second, datait->at(1).first, datait->at(1).second, datait->at(2).first, datait->at(2).second, datait->at(3).first, datait->at(3).second };
								Car aux0(-3.14, datait->at(0).first, datait->at(0).second);
								Car aux1(-1.57, datait->at(1).first, datait->at(1).second);
								Car aux2(0.0, datait->at(2).first, datait->at(2).second);
								Car aux3(1.57, datait->at(3).first, datait->at(3).second);

								sol1 = { aux0, aux1, aux2, aux3 };
								std::map<int, std::vector<std::vector<Car>>>::iterator fit = solutionMap.find(counter);
								if (fit == solutionMap.end()) {
									std::vector<std::vector<Car>> sol2 = { sol1 };
									solutionMap[counter] = sol2;
								}
								else { fit->second.push_back(sol1); }
							}
						}
					}
				}
			}
			break;
		case 4:
			if (circle.at(0).getQueuePosition() == datait->at(carUtility::checkHeading(circle.at(0).getHeading()) - 1).first && circle.at(1).getQueuePosition() == datait->at(carUtility::checkHeading(circle.at(1).getHeading()) - 1).first && circle.at(2).getQueuePosition() == datait->at(carUtility::checkHeading(circle.at(2).getHeading()) - 1).first && circle.at(3).getQueuePosition() == datait->at(carUtility::checkHeading(circle.at(3).getHeading()) - 1).first)
			{
				for (std::vector<Car>::iterator sit = circle.begin(); sit != circle.end(); ++sit) {
					std::vector<Car> sol1;
					if (sit->getSignal() == datait->at(carUtility::checkHeading(sit->getHeading()) - 1).second && sit->getSignal() != 1) {
						counter += 1;
					}
					if (sit == (circle.end() - 1) && counter > 0) {
						//Test signals equaliti or 1 in mapped
						if ((circle.at(0).getSignal() == datait->at(carUtility::checkHeading(circle.at(0).getHeading()) - 1).second || datait->at(carUtility::checkHeading(circle.at(0).getHeading()) - 1).second == 1) && (circle.at(1).getSignal() == datait->at(carUtility::checkHeading(circle.at(1).getHeading()) - 1).second || datait->at(carUtility::checkHeading(circle.at(1).getHeading()) - 1).second == 1) && (circle.at(2).getSignal() == datait->at(carUtility::checkHeading(circle.at(2).getHeading()) - 1).second || datait->at(carUtility::checkHeading(circle.at(2).getHeading()) - 1).second == 1) && (circle.at(3).getSignal() == datait->at(carUtility::checkHeading(circle.at(3).getHeading()) - 1).second || datait->at(carUtility::checkHeading(circle.at(3).getHeading()) - 1).second == 1))
						{
							if (datait->at(0).first <= maxqueuepos && datait->at(1).first <= maxqueuepos && datait->at(2).first <= maxqueuepos && datait->at(3).first <= maxqueuepos)
							{
								//sol1 = { datait->at(0).first, datait->at(0).second, datait->at(1).first, datait->at(1).second, datait->at(2).first, datait->at(2).second, datait->at(3).first, datait->at(3).second };
								Car aux0(-3.14, datait->at(0).first, datait->at(0).second);
								Car aux1(-1.57, datait->at(1).first, datait->at(1).second);
								Car aux2(0.0, datait->at(2).first, datait->at(2).second);
								Car aux3(1.57, datait->at(3).first, datait->at(3).second);

								sol1 = { aux0, aux1, aux2, aux3 };
								std::map<int, std::vector<std::vector<Car>>>::iterator fit = solutionMap.find(counter);
								if (fit == solutionMap.end()) {
									std::vector<std::vector<Car>> sol2 = { sol1 };
									solutionMap[counter] = sol2;
								}
								else { fit->second.push_back(sol1); }
							}
						}
					}
					if (sit->getSignal() == datait->at(carUtility::checkHeading(sit->getHeading()) - 1).second && sit->getSignal() == 1) {
						ones += 1;
					}
					if (sit == (circle.end() - 1) && ones == 4) {
						//Test signals equaliti or 1 in mapped
						sol1 = {};
						if ((circle.at(0).getSignal() == datait->at(carUtility::checkHeading(circle.at(0).getHeading()) - 1).second && datait->at(carUtility::checkHeading(circle.at(0).getHeading()) - 1).second == 1) && (circle.at(1).getSignal() == datait->at(carUtility::checkHeading(circle.at(1).getHeading()) - 1).second && datait->at(carUtility::checkHeading(circle.at(1).getHeading()) - 1).second == 1) && (circle.at(2).getSignal() == datait->at(carUtility::checkHeading(circle.at(2).getHeading()) - 1).second && datait->at(carUtility::checkHeading(circle.at(2).getHeading()) - 1).second == 1) && (circle.at(3).getSignal() == datait->at(carUtility::checkHeading(circle.at(3).getHeading()) - 1).second && datait->at(carUtility::checkHeading(circle.at(3).getHeading()) - 1).second == 1))
						{
							if (datait->at(0).first <= maxqueuepos && datait->at(1).first <= maxqueuepos && datait->at(2).first <= maxqueuepos && datait->at(3).first <= maxqueuepos)
							{
								//sol1 = { datait->at(0).first, datait->at(0).second, datait->at(1).first, datait->at(1).second, datait->at(2).first, datait->at(2).second, datait->at(3).first, datait->at(3).second };
								Car aux0(-3.14, datait->at(0).first, datait->at(0).second);
								Car aux1(-1.57, datait->at(1).first, datait->at(1).second);
								Car aux2(0.0, datait->at(2).first, datait->at(2).second);
								Car aux3(1.57, datait->at(3).first, datait->at(3).second);

								sol1 = { aux0, aux1, aux2, aux3 };
								std::map<int, std::vector<std::vector<Car>>>::iterator fit = solutionMap.find(0);
								if (fit == solutionMap.end()) {
									std::vector<std::vector<Car>> sol2 = { sol1 };
									solutionMap[0] = sol2;
								}
								else { fit->second.push_back(sol1); }
							}
						}
					}
				}
			}
			break;
		}
	}


	if (printOption == "") { return solutionMap; }

	if (printOption == "console") {
		for (std::map<int, std::vector<std::vector<Car>>>::iterator it = solutionMap.begin(); it != solutionMap.end(); ++it) {
			std::cout << "vehicle passing = " << it->first << std::endl;
			for (std::vector<std::vector<Car>>::iterator sit = it->second.begin(); sit != it->second.end(); ++sit) {
				std::cout << "\t{" << sit->at(0).getQueuePosition() << "," << sit->at(0).getSignal() << "},{"
					<< sit->at(1).getQueuePosition() << "," << sit->at(1).getSignal() << "},{"
					<< sit->at(2).getQueuePosition() << "," << sit->at(2).getSignal() << "},{"
					<< sit->at(3).getQueuePosition() << "," << sit->at(3).getSignal() << "}" << std::endl;
			}
		}
	}

	if (printOption != "" && printOption != "console") {
		std::ofstream myfile(printOption, std::ios::app);
		for (std::map<int, std::vector<std::vector<Car>>>::iterator it = solutionMap.begin(); it != solutionMap.end(); ++it) {
			myfile << "vehicle passing = " << it->first << std::endl;
			for (std::vector<std::vector<Car>>::iterator sit = it->second.begin(); sit != it->second.end(); ++sit) {
				myfile << "\t{" << sit->at(0).getQueuePosition() << "," << sit->at(0).getSignal() << "},{"
					<< sit->at(1).getQueuePosition() << "," << sit->at(1).getSignal() << "},{"
					<< sit->at(2).getQueuePosition() << "," << sit->at(2).getSignal() << "},{"
					<< sit->at(3).getQueuePosition() << "," << sit->at(3).getSignal() << "}" << std::endl;
			}
		}
		myfile.close();
	}

	return solutionMap;
}


void opt::recursive(std::map<int, std::vector<Car>> vehicleMap, std::vector<std::vector<Car>> testedSolutions, std::map<int, std::vector<std::vector<std::vector<Car>>>>& fullSolutions, std::map<std::array<double, 4>, std::vector<std::array<std::pair<int, int>, 4>>> mapDataset, bool& escape, double& time)
{
    if (escape == true) {
        return;
    }
    if (opt::isEmpty(vehicleMap) == true) {

        std::map<int, std::vector<std::vector<std::vector<Car>>>>::iterator it = fullSolutions.find(static_cast<int>(testedSolutions.size()));

        if (it == fullSolutions.end()) {
            std::vector<std::vector<std::vector<Car>>> aux = { testedSolutions };
            fullSolutions[static_cast<int>(testedSolutions.size())] = aux;
            time = omnetpp::simTime().dbl();
        }
        else {
            fullSolutions[static_cast<int>(testedSolutions.size())].push_back(testedSolutions);
        }
        if ((omnetpp::simTime().dbl() - time) > 2 ) {
            escape = true;
        }
    }
    else
    {
        //The first circle is always tested in order to find out the possible configurations
        std::map<int, std::vector<std::vector<Car>>> solutionMap = opt::possibleSolXCircle(vehicleMap.at(1), mapDataset);
        // The last element of the map is choosen in order to not consider the solutions with the max number of vehicles passing
        std::map<int, std::vector<std::vector<Car>>>::reverse_iterator it = solutionMap.rbegin();
        //for (std::map<int, std::vector<std::vector<Car>>>::iterator forit = solutionMap.begin(); forit != solutionMap.end(); ++forit) {
        //  std::cout << "# " << forit->first << std::endl;
        //  opt::printVectorVector(forit->second);
        //}


        std::vector<std::vector<Car>> aux = {};
        if (it->second.size() > 2) {
            aux = it->second;

            aux = { aux.rbegin(), std::next(aux.rbegin()) };

            for (std::vector<std::vector<Car>>::iterator sit = aux.begin(); sit != aux.end(); ++sit)
            {
                //Saving the actual configuration for the next iteration
                std::vector<std::vector<Car>> testedSolutionsBPB = testedSolutions;

                //Store the actual solution for the current iteration
                testedSolutions.push_back(*sit);

                //Saving the actual configuration for the next iteration
                std::map<int, std::vector<Car>> vehicleMapCopyBU = vehicleMap;
                //Updating the current configuration
                opt::updateMap2(vehicleMap, *sit);

                recursive(vehicleMap, testedSolutions, fullSolutions, mapDataset, escape, time);

                //Resetting the configuratons for the actual iteration
                vehicleMap = vehicleMapCopyBU;
                testedSolutions = testedSolutionsBPB;

            }
        }

        else {


            for (std::vector<std::vector<Car>>::iterator sit = it->second.begin(); sit != it->second.end(); ++sit)
            {
                //Saving the actual configuration for the next iteration
                std::vector<std::vector<Car>> testedSolutionsBPB = testedSolutions;

                //Store the actual solution for the current iteration

                testedSolutions.push_back(*sit);

                //Saving the actual configuration for the next iteration
                std::map<int, std::vector<Car>> vehicleMapCopyBU = vehicleMap;
                //Updating the current configuration
                opt::updateMap2(vehicleMap, *sit);

                recursive(vehicleMap, testedSolutions, fullSolutions, mapDataset, escape, time);

                //Resetting the configuratons for the actual iteration
                vehicleMap = vehicleMapCopyBU;
                testedSolutions = testedSolutionsBPB;

            }
        }
    }
}

/*
void opt::recursive(std::map<int, std::vector<Car>> vehicleMap, std::vector<std::vector<Car>> testedSolutions, std::map<int, std::vector<std::vector<std::vector<Car>>>>& fullSolutions, std::map<std::array<double, 4>, std::vector<std::array<std::pair<int, int>, 4>>> mapDataset)
{

	if (opt::isEmpty(vehicleMap) == true) {
		std::map<int, std::vector<std::vector<std::vector<Car>>>>::iterator it = fullSolutions.find(static_cast<int>(testedSolutions.size()));

		if (it == fullSolutions.end()) {
			std::vector<std::vector<std::vector<Car>>> aux = { testedSolutions };
			fullSolutions[static_cast<int>(testedSolutions.size())] = aux;
		}
		else {
			fullSolutions[static_cast<int>(testedSolutions.size())].push_back(testedSolutions);
		}
	}
	else
	{
		//The first circle is always tested in order to find out the possible configurations
		std::map<int, std::vector<std::vector<Car>>> solutionMap = opt::possibleSolXCircle(vehicleMap.at(1), mapDataset);
		// The last element of the map is choosen in order to not consider the solutions with the max number of vehicles passing
		std::map<int, std::vector<std::vector<Car>>>::reverse_iterator it = solutionMap.rbegin();
		std::vector<std::vector<Car>> aux = {};
		if (it->second.size() > 2) {
			aux = it->second;
			
			aux = { aux.rbegin(), std::next(aux.rbegin()) };
			

			for (std::vector<std::vector<Car>>::iterator sit = aux.begin(); sit != aux.end(); ++sit)
			{
				//Saving the actual configuration for the next iteration
				std::vector<std::vector<Car>> testedSolutionsBPB = testedSolutions;

				//Store the actual solution for the current iteration

				testedSolutions.push_back(*sit);

				//Saving the actual configuration for the next iteration
				std::map<int, std::vector<Car>> vehicleMapCopyBU = vehicleMap;
				//Updating the current configuration
				opt::updateMap2(vehicleMap, *sit);

				recursive(vehicleMap, testedSolutions, fullSolutions, mapDataset);

				//Resetting the configuratons for the actual iteration
				vehicleMap = vehicleMapCopyBU;
				testedSolutions = testedSolutionsBPB;

			}
		}
		
		else {


			for (std::vector<std::vector<Car>>::iterator sit = it->second.begin(); sit != it->second.end(); ++sit)
			{
				//Saving the actual configuration for the next iteration
				std::vector<std::vector<Car>> testedSolutionsBPB = testedSolutions;

				//Store the actual solution for the current iteration

				testedSolutions.push_back(*sit);

				//Saving the actual configuration for the next iteration
				std::map<int, std::vector<Car>> vehicleMapCopyBU = vehicleMap;
				//Updating the current configuration
				opt::updateMap2(vehicleMap, *sit);

				recursive(vehicleMap, testedSolutions, fullSolutions, mapDataset);

				//Resetting the configuratons for the actual iteration
				vehicleMap = vehicleMapCopyBU;
				testedSolutions = testedSolutionsBPB;

			}
		}
	}
}*/




//		StartAndStopUpdate
void opt::startAndStopUpdate(std::map<int, std::vector<std::vector<std::vector<Car>>>>& fullSolutions)
{
    for (std::map<int, std::vector<std::vector<std::vector<Car>>>>::iterator mit = fullSolutions.begin(); mit != fullSolutions.end(); ++mit) {
        //solution
        for (std::vector<std::vector<std::vector<Car>>>::iterator vit1 = mit->second.begin(); vit1 != mit->second.end(); ++vit1)
        {
            //Solution's row
            for (std::vector<std::vector<Car>>::iterator vit2 = vit1->begin(); vit2 != vit1->end(); ++vit2)
            {
                int signal0 = vit2->at(0).getSignal();
                int signal1 = vit2->at(1).getSignal();
                int signal2 = vit2->at(2).getSignal();
                int signal3 = vit2->at(3).getSignal();


                vit2->at(0).setSettedSignal(signal0);
                vit2->at(1).setSettedSignal(signal1);
                vit2->at(2).setSettedSignal(signal2);
                vit2->at(3).setSettedSignal(signal3);


                for (std::vector<std::vector<Car>>::iterator sit = vit2 + 1; sit != vit1->end(); ++sit)
                {
                    sit->at(0).setSettedSignal(signal0);
                    sit->at(1).setSettedSignal(signal1);
                    sit->at(2).setSettedSignal(signal2);
                    sit->at(3).setSettedSignal(signal3);
                }
            }
        }
    }

    //THIS SECTION ALLOW TO ASSIGN TO THE Car ELEMENTS IN THE SOLUTION THAT ARE (1,1), DUE TO THE FACT THAT ALL VEHICLES IN THAT QUEUE ARE PASSED, THE VALUES OF StartCounter AND StopCounter OF THE LAST VEHICLE IN ORDER
    //      TO PERFORM THE COMPUTATION OF THE SOLUTION WITH THE MAX NUMBER OF START AND STOPS CORRECTLY

    for (std::map<int, std::vector<std::vector<std::vector<Car>>>>::iterator mit = fullSolutions.begin(); mit != fullSolutions.end(); ++mit) {
		//solution
		for (std::vector<std::vector<std::vector<Car>>>::iterator vit1 = mit->second.begin(); vit1 != mit->second.end(); ++vit1)
		{
			//Solution's row
			std::vector<std::vector<Car>>::reverse_iterator rvit2 = vit1->rbegin();


			if (rvit2->at(0).getSignal() == 1) {
				std::vector<std::vector<Car>>::reverse_iterator rit3 = vit1->rbegin();
				if (vit1->size() > 1)
				{
					std::vector<std::vector<Car>>::reverse_iterator ritPositon0 = vit1->rbegin();

					while (rit3->at(0).getQueuePosition() == 1) {
						if (std::next(rit3) != vit1->rend()) {
							ritPositon0 = rit3;
							rit3++;
						}
						else {
							break;
						}
					}
					//Last real vehicle
					ritPositon0 += 1;

					int CounterStart = ritPositon0->at(0).getStartCounter();
					int CounterStop = ritPositon0->at(0).getStopCounter();
					//Solution's row
					for (std::vector<std::vector<Car>>::reverse_iterator rvit4 = vit1->rbegin(); rvit4 != ritPositon0; ++rvit4) {
						rvit4->at(0).setStartCounter(CounterStart);
						rvit4->at(0).setStopCounter(CounterStop);
					}
				}
				else
				{
					std::vector<std::vector<Car>>::reverse_iterator ritPositon0 = vit1->rbegin();

					while (rit3->at(0).getQueuePosition() == 1) {
						if (std::next(rit3) != vit1->rend()) {
							ritPositon0 = rit3;
							rit3++;
						}
						else {
							break;
						}
					}
					//Last real vehicle
					//ritPositon0 += 1;

					int CounterStart = ritPositon0->at(0).getStartCounter();
					int CounterStop = ritPositon0->at(0).getStopCounter();
					//Solution's row
					for (std::vector<std::vector<Car>>::reverse_iterator rvit4 = vit1->rbegin(); rvit4 != ritPositon0; ++rvit4) {
						rvit4->at(0).setStartCounter(CounterStart);
						rvit4->at(0).setStopCounter(CounterStop);
					}
				}
			}

			if (rvit2->at(1).getSignal() == 1) {
				std::vector<std::vector<Car>>::reverse_iterator rit4 = vit1->rbegin();
				if (vit1->size() > 1)
				{
					std::vector<std::vector<Car>>::reverse_iterator ritPositon1 = vit1->rbegin();
					//std::cout << "iteration n: " << mit->first << std::endl;
					//std::cout << "size:" << vit1->size() << std::endl;
					while (rit4->at(1).getQueuePosition() == 1) {
						if (std::next(rit4) != vit1->rend()) {
							ritPositon1 = rit4;
							rit4++;
						}
						else {
							break;
						}
					}
					//Last real vehicle
					ritPositon1 += 1;

					int CounterStart = ritPositon1->at(1).getStartCounter();
					int CounterStop = ritPositon1->at(1).getStopCounter();
					//Solution's row
					for (std::vector<std::vector<Car>>::reverse_iterator rvit4 = vit1->rbegin(); rvit4 != ritPositon1; ++rvit4) {
						rvit4->at(1).setStartCounter(CounterStart);
						rvit4->at(1).setStopCounter(CounterStop);
					}
				}
				else {
					std::vector<std::vector<Car>>::reverse_iterator ritPositon1 = vit1->rbegin();
					//std::cout << "iteration n: " << mit->first << std::endl;
					//std::cout << "size:" << vit1->size() << std::endl;
					while (rit4->at(1).getQueuePosition() == 1) {
						if (std::next(rit4) != vit1->rend()) {
							ritPositon1 = rit4;
							rit4++;
						}
						else {
							break;
						}
					}
					//Last real vehicle
					//ritPositon1 += 1;


					int CounterStart = ritPositon1->at(1).getStartCounter();
					int CounterStop = ritPositon1->at(1).getStopCounter();
					//Solution's row
					for (std::vector<std::vector<Car>>::reverse_iterator rvit4 = vit1->rbegin(); rvit4 != ritPositon1; ++rvit4) {
						rvit4->at(1).setStartCounter(CounterStart);
						rvit4->at(1).setStopCounter(CounterStop);
					}
				}
			}

			if (rvit2->at(2).getSignal() == 1) {
				std::vector<std::vector<Car>>::reverse_iterator rit4 = vit1->rbegin();
				if (vit1->size() > 1) {
					std::vector<std::vector<Car>>::reverse_iterator ritPositon2 = vit1->rbegin();

					while (rit4->at(2).getQueuePosition() == 1) {
						if (std::next(rit4) != vit1->rend()) {
							ritPositon2 = rit4;
							rit4++;
						}
						else {
							break;
						}
					}
					//Last real vehicle
					ritPositon2 += 1;

					int CounterStart = ritPositon2->at(2).getStartCounter();
					int CounterStop = ritPositon2->at(2).getStopCounter();
					//Solution's row
					for (std::vector<std::vector<Car>>::reverse_iterator rvit4 = vit1->rbegin(); rvit4 != ritPositon2; ++rvit4) {
						rvit4->at(2).setStartCounter(CounterStart);
						rvit4->at(2).setStopCounter(CounterStop);
					}
				}
				else
				{
					std::vector<std::vector<Car>>::reverse_iterator ritPositon2 = vit1->rbegin();

					while (rit4->at(2).getQueuePosition() == 1) {
						if (std::next(rit4) != vit1->rend()) {
							ritPositon2 = rit4;
							rit4++;
						}
						else {
							break;
						}
					}
					//Last real vehicle
					//ritPositon2 += 1;

					int CounterStart = ritPositon2->at(2).getStartCounter();
					int CounterStop = ritPositon2->at(2).getStopCounter();
					//Solution's row
					for (std::vector<std::vector<Car>>::reverse_iterator rvit4 = vit1->rbegin(); rvit4 != ritPositon2; ++rvit4) {
						rvit4->at(2).setStartCounter(CounterStart);
						rvit4->at(2).setStopCounter(CounterStop);
					}
				}
			}

			if (rvit2->at(3).getSignal() == 1) {
				std::vector<std::vector<Car>>::reverse_iterator rit4 = vit1->rbegin();
				if (vit1->size() > 1)
				{
					std::vector<std::vector<Car>>::reverse_iterator ritPositon3 = vit1->rbegin();

					while (rit4->at(3).getQueuePosition() == 1) {
						if (std::next(rit4) != vit1->rend()) {
							ritPositon3 = rit4;
							rit4++;
						}
						else {
							break;
						}
					}
					//Last real vehicle
					ritPositon3 += 1;

					int CounterStart = ritPositon3->at(3).getStartCounter();
					int CounterStop = ritPositon3->at(3).getStopCounter();
					//Solution's row
					for (std::vector<std::vector<Car>>::reverse_iterator rvit4 = vit1->rbegin(); rvit4 != ritPositon3; ++rvit4) {
						rvit4->at(3).setStartCounter(CounterStart);
						rvit4->at(3).setStopCounter(CounterStop);
					}
				}
				else
				{
					std::vector<std::vector<Car>>::reverse_iterator ritPositon3 = vit1->rbegin();

					while (rit4->at(3).getQueuePosition() == 1) {
						if (std::next(rit4) != vit1->rend()) {
							ritPositon3 = rit4;
							rit4++;
						}
						else {
							break;
						}
					}
					//Last real vehicle
					//ritPositon3 += 1;

					int CounterStart = ritPositon3->at(3).getStartCounter();
					int CounterStop = ritPositon3->at(3).getStopCounter();
					//Solution's row
					for (std::vector<std::vector<Car>>::reverse_iterator rvit4 = vit1->rbegin(); rvit4 != ritPositon3; ++rvit4) {
						rvit4->at(3).setStartCounter(CounterStart);
						rvit4->at(3).setStopCounter(CounterStop);
					}
				}
			}
		}
	}

}


//ChooseMinStartStop
std::vector<std::vector<Car>> opt::chooseMinStartStop(std::map<int, std::vector<std::vector<std::vector<Car>>>>& fullSolutions)
{
	int mapkey = 0;
	std::vector<std::vector<std::vector<Car>>>::iterator solPosition;
	int numberStartStop = 0;

	//Considering the solutions with the lower number of steps that allows to empty the intersection
	std::map<int, std::vector<std::vector<std::vector<Car>>>>::iterator it = fullSolutions.begin();

	std::ofstream logfile ("C:/veins-4.7.1acc_id/doc/log.txt", std::ios::app);
	for (std::vector<std::vector<std::vector<Car>>>::iterator sit = it->second.begin(); sit != it->second.end(); ++sit)
	{
		int summ = 0;
		std::vector<std::vector<Car>>::reverse_iterator row = sit->rbegin();
		if ((row->at(0).getStartCounter() + row->at(0).getStopCounter()) % 2 == 0) {
			summ += (row->at(0).getStartCounter() + row->at(0).getStopCounter()) / 2;
		}
		else {
		    logfile << "[Error!]:\n\tCar .at(0) not restart." << std::endl;
		    logfile << "\tSolution: " << std::distance(it->second.begin(), sit) << " map position: " << it->first << std::endl;
		}

		if ((row->at(1).getStartCounter() + row->at(1).getStopCounter()) % 2 == 0) {
			summ += (row->at(1).getStartCounter() + row->at(1).getStopCounter()) / 2;
		}
		else {
		    logfile << "[Error!]:\n\tCar .at(1) not restart." << std::endl;
		    logfile << "\tSolution: " << std::distance(it->second.begin(), sit) << " map position: " << it->first << std::endl;
		}

		if ((row->at(2).getStartCounter() + row->at(2).getStopCounter()) % 2 == 0) {
			summ += (row->at(2).getStartCounter() + row->at(2).getStopCounter()) / 2;
		}
		else {
		    logfile << "[Error!]:\n\tCar .at(2) not restart." << std::endl;
		    logfile << "\tSolution: " << std::distance(it->second.begin(), sit) << " map position: " << it->first << std::endl;
		}

		if ((row->at(3).getStartCounter() + row->at(3).getStopCounter()) % 2 == 0) {
			summ += (row->at(3).getStartCounter() + row->at(3).getStopCounter()) / 2;
		}
		else {
		    logfile << "[Error!]:\n\tCar .at(3) not restart." << std::endl;
		    logfile << "\tSolution: " << std::distance(it->second.begin(), sit) << " map position: " << it->first << std::endl;
		}


		if (summ < numberStartStop && numberStartStop != 0) {
			numberStartStop = summ;
			mapkey = it->first;
			solPosition = sit;
		}
		if (numberStartStop == 0) {
			numberStartStop = summ;
			mapkey = it->first;
			solPosition = sit;
		}
	}

	std::vector<std::vector<Car>> solution = {};
	if (mapkey != 0)
	{
		int distance = static_cast<int>(std::distance(fullSolutions.begin()->second.begin(), solPosition));
		solution = fullSolutions[mapkey].at(distance);
	}
	else {
	    if (fullSolutions.begin()->second.size() == 1) {
			return *fullSolutions.begin()->second.begin();
		}
	}

	return solution;
}









/****************************************************************************************************************************************************************************************************************************
*																								UTILITY
****************************************************************************************************************************************************************************************************************************/


void opt::possibleHeading(std::vector<double>& heading, double head1)
{
	std::vector<double>::iterator reference;
	for (std::vector<double>::iterator it = heading.begin(); it != heading.end(); ++it) {
		if (*it == head1) {
			reference = it;
		}
	}
	heading.erase(reference);
}
void opt::possibleHeading(std::vector<double>& heading, double head1, double head2)
{
	std::vector<double>::iterator reference1;
	for (std::vector<double>::iterator it = heading.begin(); it != heading.end(); ++it) {
		if (*it == head1) {
			reference1 = it;
		}
	}
	heading.erase(reference1);

	std::vector<double>::iterator reference2;
	for (std::vector<double>::iterator it = heading.begin(); it != heading.end(); ++it) {
		if (*it == head2) {
			reference2 = it;
		}
	}
	heading.erase(reference2);

}
void opt::possibleHeading(std::vector<double>& heading, double head1, double head2, double head3)
{
	std::vector<double>::iterator reference1;
	for (std::vector<double>::iterator it = heading.begin(); it != heading.end(); ++it) {
		if (*it == head1) {
			reference1 = it;
		}
	}
	heading.erase(reference1);

	std::vector<double>::iterator reference2;
	for (std::vector<double>::iterator it = heading.begin(); it != heading.end(); ++it) {
		if (*it == head2) {
			reference2 = it;
		}
	}
	heading.erase(reference2);

	std::vector<double>::iterator reference3;
	for (std::vector<double>::iterator it = heading.begin(); it != heading.end(); ++it) {
		if (*it == head3) {
			reference3 = it;
		}
	}
	heading.erase(reference3);
}



void opt::eraseEmptyQueue(std::map<int, std::vector<Car>>& mapVehicle)
{
	int semaphore = 0;
	if (mapVehicle.size() != 0) {
		std::map<int, std::vector<Car>>::iterator position;
		for (std::map<int, std::vector<Car>>::iterator mit = mapVehicle.begin(); mit != mapVehicle.end(); ++mit)
		{
			if (mit->second.size() == 0) {
				position = mit;
				semaphore = 1;
				break;
			}
		}
		if (semaphore == 1) {
			mapVehicle.erase(position);
		}
	}
}


void opt::updateMap2(std::map<int, std::vector<Car>>& mapVehicle, std::vector<Car>& solution)
{
	for (std::vector<Car>::iterator sol = solution.begin(); sol != solution.end(); ++sol)
	{
		if (sol->getSignal() > 1)
		{
			std::vector<Car> auxVec = {};
			// Adding all vehicles with the same heading of the solution to the auxVec
			for (std::map<int, std::vector<Car>>::iterator mit = mapVehicle.begin(); mit != mapVehicle.end(); ++mit)
			{
				for (std::vector<Car>::iterator vit = mit->second.begin(); vit != mit->second.end(); ++vit)
				{
					if (sol->getHeading() == vit->getHeading())
					{
						auxVec.push_back(*vit);
					}
				}
			}

			//Searching the position of the solution in the created auxVec
			int semaphore = 0;
			std::vector<Car>::iterator it;
			for (std::vector<Car>::iterator search = auxVec.begin(); search != auxVec.end(); ++search)
			{
				if (search->getHeading() == sol->getHeading() && search->getSignal() == sol->getSignal() && search->getQueuePosition() == sol->getQueuePosition()) {
					it = search;
					semaphore = 1;
				}
			}
			//Delating the solution from the auxVec
			if (semaphore == 1) {
				auxVec.erase(it);
			}

			// Delating all vehicle from the map with the heading equal to the solution one
			for (std::map<int, std::vector<Car>>::iterator mit = mapVehicle.begin(); mit != mapVehicle.end(); ++mit)
			{
				std::vector<Car> Auxnew = {};
				for (std::vector<Car>::iterator sit = mit->second.begin(); sit != mit->second.end(); ++sit) {
					if (sit->getHeading() != sol->getHeading()) {
						Auxnew.push_back(*sit);
					}
				}
				mit->second = Auxnew;
			}

			//Refill the auxVec elements to the 
			std::map<int, std::vector<Car>>::iterator mit = mapVehicle.begin();
			for (std::vector<Car>::iterator vit = auxVec.begin(); vit != auxVec.end(); ++vit)
			{
				carUtility::insertCarInVectorVoid(mit->second, *vit);
				++mit;
			}

		}
	}

	// delate empty queue in case of multiple erases
	opt::eraseEmptyQueue(mapVehicle);
	opt::eraseEmptyQueue(mapVehicle);
	opt::eraseEmptyQueue(mapVehicle);
	opt::eraseEmptyQueue(mapVehicle);

}



void opt::printMap2(std::map<int, std::vector<Car>>& vehByCircle, std::string path, std::string ss)
{
	if (path == "") {
		for (std::map<int, std::vector<Car>>::iterator it = vehByCircle.begin(); it != vehByCircle.end(); ++it) {
			std::cout << "queue = " << it->first << std::endl;
			for (std::vector<Car>::iterator sit = it->second.begin(); sit != it->second.end(); ++sit) {
				std::cout << "\theading = " << sit->getHeading() << " position = " << sit->getQueuePosition() << " signal = " << sit->getSignal() << std::endl;
				if (ss == "ss") {
					sit->printStartStop();
				}
			}
		}
		if (vehByCircle.size() == 0) {
			std::cout << "!!  NO MORE VEHICLES  !!" << std::endl;
		}
	}
	if (path != "") {
		std::ofstream myfile(path, std::ios::app);
		for (std::map<int, std::vector<Car>>::iterator it = vehByCircle.begin(); it != vehByCircle.end(); ++it) {
			myfile << "queue = " << it->first << std::endl;
			for (std::vector<Car>::iterator sit = it->second.begin(); sit != it->second.end(); ++sit) {
				myfile << "\theading = " << sit->getHeading() << " position = " << sit->getQueuePosition() << " signal = " << sit->getSignal() << std::endl;
				if (ss == "ss") {
					sit->printStartStop();
				}
			}
		}
		if (vehByCircle.size() == 0) {
			myfile << "!!  NO MORE VEHICLES  !!" << std::endl;
		}
	}
}



void opt::printVector(std::vector<Car>& vector)
{
	for (std::vector<Car>::iterator it = vector.begin(); it != vector.end(); ++it) {
		std::cout << "\theading = " << it->getHeading() << " position = " << it->getQueuePosition() << " signal = " << it->getSignal() << std::endl;
	}
}


bool opt::signal0(std::map<int, std::vector<Car>> map)
{
	for (std::map<int, std::vector<Car>>::iterator mit = map.begin(); mit != map.end(); ++mit) {
		for (std::vector<Car>::iterator vit = mit->second.begin(); vit != mit->second.end(); ++vit) {
			if (vit->getSignal() == 0) {
				std::cout << "Zero is present" << std::endl;
				return true;
			}
		}
	}
	std::cout << "Zero is not present" << std::endl;
	return false;
}


double opt::leaderDir(std::map<double, std::vector<int>>& signalMap)
{
	std::vector<int> aux;
	for (std::map<double, std::vector<int>>::iterator it = signalMap.begin(); it != signalMap.end(); ++it) { aux.push_back(static_cast<int>(it->second.size())); }
	int max = 0;
	for (std::vector<int>::iterator it = aux.begin(); it != aux.end(); ++it) {
		if (*it == max) { std::cout << "ATTENTION 2 QUEUES HAVE THE SAME SIZE,  FIRST WILL BE CONSIDERED AS LEADER DIRECTION IF ELIGIBLE" << std::endl; }
		if (*it > max) { max = *it; }
	}
	for (std::map<double, std::vector<int>>::iterator it = signalMap.begin(); it != signalMap.end(); ++it) {
		if (it->second.size() == max) {
			return it->first;
			break;
		}
	}
}



bool opt::isEmpty(std::map<int, std::vector<Car>> &vehByCircle)
{
	if (vehByCircle.size() == 0) { return true; }
	else { return false; }
}


void opt::printTestedSolution(std::vector<Car> sol, std::string path)
{
	if (path == "") {
		std::cout << "Tested solution" << std::endl;
		for (std::vector<Car>::iterator it = sol.begin(); it != sol.end(); ++it)
		{
			std::cout << "{" << it->getQueuePosition() << "," << it->getSignal() << "}";
		}
		std::cout << std::endl;
	}
	if (path != "") {
		std::ofstream myfile(path, std::ios::app);
		myfile << "Tested solution" << std::endl;
		for (std::vector<Car>::iterator it = sol.begin(); it != sol.end(); ++it)
		{
			myfile << "{" << it->getQueuePosition() << "," << it->getSignal() << "}";
		}
		myfile << std::endl;
	}
}


void opt::printVectorVector(std::vector<std::vector<Car>> testedSolutions, std::string path, std::string type)
{
	if (type == "") {
		if (path == "") {
			for (std::vector<std::vector<Car>>::iterator it = testedSolutions.begin(); it != testedSolutions.end(); ++it)
			{
				for (std::vector<Car>::iterator sit = it->begin(); sit != it->end(); ++sit)
				{
					std::cout << "{" << sit->getQueuePosition() << "," << sit->getSignal() << "}";
				}
				std::cout << std::endl;
			}
			//std::cout << "\n" << std::endl;
		}
		if (path != "") {
			std::ofstream myfile(path, std::ios::app);
			myfile << "{id, QueuePosition, signal, passing or not}" << std::endl;
			for (std::vector<std::vector<Car>>::iterator it = testedSolutions.begin(); it != testedSolutions.end(); ++it)
			{
				for (std::vector<Car>::iterator sit = it->begin(); sit != it->end(); ++sit)
				{
					myfile << "{" << sit->getId() << "," << sit->getQueuePosition() << "," << sit->getSettedSignal() << ",";
					if(sit->getSignal() == 1){
					    myfile << sit->getSignal() << " stop}";
					}
					else{
					    myfile << sit->getSignal() << " go}";
					}
				}
				myfile << std::endl;
			}
			//myfile << "\n" << std::endl;
		}
	}

	if (type == "ss") {
		if (path == "") {
			for (std::vector<std::vector<Car>>::iterator it = testedSolutions.begin(); it != testedSolutions.end(); ++it)
			{
				for (std::vector<Car>::iterator sit = it->begin(); sit != it->end(); ++sit)
				{
					std::cout << "{" << sit->getStartCounter() << "," << sit->getStopCounter() << "}";
				}
				std::cout << std::endl;
			}
			//std::cout << "\n" << std::endl;
		}
		if (path != "") {
			std::ofstream myfile(path, std::ios::app);
			myfile << std::endl;
			for (std::vector<std::vector<Car>>::iterator it = testedSolutions.begin(); it != testedSolutions.end(); ++it)
			{
				for (std::vector<Car>::iterator sit = it->begin(); sit != it->end(); ++sit)
				{
					myfile << "{" << sit->getStartCounter() << "," << sit->getStopCounter() << "}";
				}
				myfile << std::endl;
			}
			//myfile << "\n" << std::endl;
		}
	}
}

void opt::delCarFromVecVec(std::vector<std::vector<Car>>& myvec, Car todel)
{
	if (myvec.size() > 0)
	{
		std::vector<Car>::iterator delit;
		std::vector<std::vector<Car>>::iterator delVV = myvec.end();
		int position;
		int s = 0;

		for (std::vector<std::vector<Car>>::iterator it = myvec.begin(); it != myvec.end(); ++it) {
			if (s == 1) {
				break;
			}
			for (std::vector<Car>::iterator sit = it->begin(); sit != it->end(); ++sit) {
				if (sit->getQueuePosition() == todel.getQueuePosition() && sit->getSignal() == todel.getSignal()) {
					delit = sit;
					delVV = it;
					s = 1;
					break;
				}
			}
		}

		if (delVV != myvec.end()) {
			position = static_cast<int>(std::distance(myvec.begin(), delVV));
			myvec.at(position).erase(delit);
			std::cout << position << std::endl;
		}
	}
}



void opt::delVecFromVecVec(std::vector<std::vector<Car>>& myvec, std::vector<Car> todel)
{
	if (myvec.size() > 0) {
		std::vector<std::vector<Car>>::iterator delVV = myvec.end();
		for (std::vector<std::vector<Car>>::iterator it = myvec.begin(); it != myvec.end(); ++it) {			
			if (opt::isEqual(*it, todel) == true) {
				delVV = it;
				break;
			}
		}
		if (delVV != myvec.end()) { myvec.erase(delVV); }
	}
}



bool opt::isEqual(std::vector<Car> c1, std::vector<Car> c2)
{
	bool var = false;

	if (c1.size() == c2.size())
	{
		int i = 0;
		while (i < c1.size()) {
			var = false;
			if (c1.at(i).getQueuePosition() == c2.at(i).getQueuePosition() && c1.at(i).getSignal() == c2.at(i).getSignal()) { var = true; }
			i++;
		}
	}
	return var;
}


bool opt::isEqual(std::vector<int> v1, std::vector<int> v2)
{
    if(v1.size() == v2.size()){
        int counter = 0;
        for(int i = 0; i<v1.size(); ++i)
        {
            if(v1.at(i) == v2.at(i)){
                counter += 1;
            }
        }
        if(counter == v1.size()){
            return true;
        }
    }

    return false;
}





// return true if the vehicle has to stop otherwise return false
bool opt::fromChoosenToVehicleSignal(std::vector<std::vector<Car>> chosSol, double heading, int queuePos)
{
    int solSize = chosSol.size();


    for (int i = 0; i < solSize - 1; ++i) {
        if (chosSol.at(i).at(carUtility::checkHeading(heading) - 1).getQueuePosition() == queuePos && chosSol.at(i).at(carUtility::checkHeading(heading) - 1).getSignal() != 1) {
            return false;
        }
        if (chosSol.at(i).at(carUtility::checkHeading(heading) - 1).getQueuePosition() == queuePos && chosSol.at(i).at(carUtility::checkHeading(heading) - 1).getSignal() == 1) {
            return true;
        }
    }




}



















/****************************************************************************************************************************************************************************************************************************
*																					NOT USED FUNCTIONS (Working problems or old)
****************************************************************************************************************************************************************************************************************************/


//OLD DO NOT USE, REFERE TO mapVehicleByCircle
/*/
std::vector<std::vector<Car>> opt::VehiclebyCircle(std::map<double, std::vector<Car>>& inputVector)
{
	for (std::map<double, std::vector<Car>>::iterator it = inputVector.begin(); it != inputVector.end(); ++it)
	{
		int start = static_cast<int>(it->second.size());
		while (it->second.size() < 7) {
			Car aux(it->first, start+1, 1);
			it->second.push_back(aux);
			start += 1;
		}
	}
	std::vector<std::vector<Car>> Vehbycircle;
	for (int i = 0; i < 6; ++i) {
		std::vector<Car> aux;
		for (std::map<double, std::vector<Car>>::iterator it = inputVector.begin(); it != inputVector.end(); ++it) {
			if (it->second.size() > i) { aux.push_back(it->second.at(i)); }
		}
		Vehbycircle.push_back(aux);
	}
	
	return Vehbycircle;
}
*/






//VehNumberPerSolution
// DO NOT USE! Refere to  possibleSolXCircle
/*
std::vector<std::map<int, std::vector<std::vector<int>>>> opt::VehNumberPerSolution(std::vector<std::vector<Car>> vByC, std::map<std::array<double, 4>, std::vector<std::array<std::pair<int, int>, 4>>> mapDataset, std::string printOption)
{
	std::array<double, 4> key = { -3.14, -1.57, 0.0, 1.57 };
	std::vector<std::map<int, std::vector<std::vector<int>>>> solutionMapVect;
	for (std::vector<std::vector<Car>>::iterator it = vByC.begin(); it != vByC.end(); ++it)
	{
		std::map<int, std::vector<std::vector<int>>> solutionMap;
		if (it == vByC.begin())
		{
			for (std::vector<std::array<std::pair<int, int>, 4>>::iterator datait = mapDataset[key].begin(); datait != mapDataset[key].end(); ++datait)
			{
				int counter = 0;
				// Check that the position of my vehicles is the same of the one in the Dataset
				switch (it->size())
				{
				case 1:
					if (it->at(0).getQueuePosition() == datait->at(carUtility::checkHeading(it->at(0).getHeading()) - 1).first) {
						for (std::vector<Car>::iterator sit = it->begin(); sit != it->end(); ++sit) {
							std::vector<int> Sol1;
							if (sit->getSignal() == datait->at(carUtility::checkHeading(sit->getHeading()) - 1).second) {
								counter += 1;
							}
							if (sit == (it->end() - 1) && counter > 0) {
								//Test signals equaliti or 1 in mapped
								if ((it->at(0).getSignal() == datait->at(carUtility::checkHeading(it->at(0).getHeading()) - 1).second || datait->at(carUtility::checkHeading(it->at(0).getHeading()) - 1).second == 1))
								{
									Sol1 = { datait->at(0).first, datait->at(0).second, datait->at(1).first, datait->at(1).second, datait->at(2).first, datait->at(2).second, datait->at(3).first, datait->at(3).second };
									std::map<int, std::vector<std::vector<int>>>::iterator fit = solutionMap.find(counter);
									if (fit == solutionMap.end()) {
										std::vector<std::vector<int>> Sol2 = { Sol1 };
										solutionMap[counter] = Sol2;
									}
									else { fit->second.push_back(Sol1); }
								}
							}
						}
					}
					break;
				case 2:
					if (it->at(0).getQueuePosition() == datait->at(carUtility::checkHeading(it->at(0).getHeading()) - 1).first && it->at(1).getQueuePosition() == datait->at(carUtility::checkHeading(it->at(1).getHeading()) - 1).first)
					{
						for (std::vector<Car>::iterator sit = it->begin(); sit != it->end(); ++sit) {
							std::vector<int> Sol1;
							if (sit->getSignal() == datait->at(carUtility::checkHeading(sit->getHeading()) - 1).second) {
								counter += 1;
							}
							if (sit == (it->end() - 1) && counter > 0) {
								//Test signals equaliti or 1 in mapped
								if ((it->at(0).getSignal() == datait->at(carUtility::checkHeading(it->at(0).getHeading()) - 1).second || datait->at(carUtility::checkHeading(it->at(0).getHeading()) - 1).second == 1) && (it->at(1).getSignal() == datait->at(carUtility::checkHeading(it->at(1).getHeading()) - 1).second || datait->at(carUtility::checkHeading(it->at(1).getHeading()) - 1).second == 1))
								{
									Sol1 = { datait->at(0).first, datait->at(0).second, datait->at(1).first, datait->at(1).second, datait->at(2).first, datait->at(2).second, datait->at(3).first, datait->at(3).second };
									std::map<int, std::vector<std::vector<int>>>::iterator fit = solutionMap.find(counter);
									if (fit == solutionMap.end()) {
										std::vector<std::vector<int>> Sol2 = { Sol1 };
										solutionMap[counter] = Sol2;
									}
									else { fit->second.push_back(Sol1); }
								}
							}
						}
					}
					break;
				case 3:
					if (it->at(0).getQueuePosition() == datait->at(carUtility::checkHeading(it->at(0).getHeading()) - 1).first && it->at(1).getQueuePosition() == datait->at(carUtility::checkHeading(it->at(1).getHeading()) - 1).first && it->at(2).getQueuePosition() == datait->at(carUtility::checkHeading(it->at(2).getHeading()) - 1).first)
					{
						for (std::vector<Car>::iterator sit = it->begin(); sit != it->end(); ++sit) {
							std::vector<int> Sol1;
							if (sit->getSignal() == datait->at(carUtility::checkHeading(sit->getHeading()) - 1).second ) {
								counter += 1;
							}
							if (sit == (it->end() - 1) && counter > 0) {
								//Test signals equaliti or 1 in mapped
								if ((it->at(0).getSignal() == datait->at(carUtility::checkHeading(it->at(0).getHeading()) - 1).second || datait->at(carUtility::checkHeading(it->at(0).getHeading()) - 1).second == 1) && (it->at(1).getSignal() == datait->at(carUtility::checkHeading(it->at(1).getHeading()) - 1).second || datait->at(carUtility::checkHeading(it->at(1).getHeading()) - 1).second == 1) && (it->at(2).getSignal() == datait->at(carUtility::checkHeading(it->at(2).getHeading()) - 1).second || datait->at(carUtility::checkHeading(it->at(2).getHeading()) - 1).second == 1))
								{
									Sol1 = { datait->at(0).first, datait->at(0).second, datait->at(1).first, datait->at(1).second, datait->at(2).first, datait->at(2).second, datait->at(3).first, datait->at(3).second };
									std::map<int, std::vector<std::vector<int>>>::iterator fit = solutionMap.find(counter);
									if (fit == solutionMap.end()) {
										std::vector<std::vector<int>> Sol2 = { Sol1 };
										solutionMap[counter] = Sol2;
									}
									else { fit->second.push_back(Sol1); }
								}
							}
						}
					}
					break;
				case 4:
					if (it->at(0).getQueuePosition() == datait->at(carUtility::checkHeading(it->at(0).getHeading()) - 1).first && it->at(1).getQueuePosition() == datait->at(carUtility::checkHeading(it->at(1).getHeading()) - 1).first && it->at(2).getQueuePosition() == datait->at(carUtility::checkHeading(it->at(2).getHeading()) - 1).first && it->at(3).getQueuePosition() == datait->at(carUtility::checkHeading(it->at(3).getHeading()) - 1).first)
					{
						for (std::vector<Car>::iterator sit = it->begin(); sit != it->end(); ++sit) {
							std::vector<int> Sol1;
							if (sit->getSignal() == datait->at(carUtility::checkHeading(sit->getHeading()) - 1).second) {
								counter += 1;
							}
							if (sit == (it->end() - 1) && counter > 0) {
								//Test signals equaliti or 1 in mapped
								if ((it->at(0).getSignal() == datait->at(carUtility::checkHeading(it->at(0).getHeading()) - 1).second || datait->at(carUtility::checkHeading(it->at(0).getHeading()) - 1).second == 1) && (it->at(1).getSignal() == datait->at(carUtility::checkHeading(it->at(1).getHeading()) - 1).second || datait->at(carUtility::checkHeading(it->at(1).getHeading()) - 1).second == 1) && (it->at(2).getSignal() == datait->at(carUtility::checkHeading(it->at(2).getHeading()) - 1).second || datait->at(carUtility::checkHeading(it->at(2).getHeading()) - 1).second == 1) && (it->at(3).getSignal() == datait->at(carUtility::checkHeading(it->at(3).getHeading()) - 1).second || datait->at(carUtility::checkHeading(it->at(3).getHeading()) - 1).second == 1))
								{
									Sol1 = { datait->at(0).first, datait->at(0).second, datait->at(1).first, datait->at(1).second, datait->at(2).first, datait->at(2).second, datait->at(3).first, datait->at(3).second };

									std::map<int, std::vector<std::vector<int>>>::iterator fit = solutionMap.find(counter);
									if (fit == solutionMap.end()) {
										std::vector<std::vector<int>> Sol2 = { Sol1 };
										solutionMap[counter] = Sol2;
									}
									else { fit->second.push_back(Sol1); }
								}
							}
						}
					}
					break;
				}
			}
			solutionMapVect.push_back(solutionMap);
		}		
	}

	if (printOption == "") { return solutionMapVect; }

	if (printOption == "console") {
		for (std::vector< std::map<int, std::vector<std::vector<int>>>>::iterator it = solutionMapVect.begin(); it != solutionMapVect.end(); ++it) {
			std::cout << "queue = " << std::distance(solutionMapVect.begin(), it) + 1 << std::endl;
			for (std::map<int, std::vector<std::vector<int>>>::iterator sit = it->begin(); sit != it->end(); ++sit) {
				std::cout << "\tvehicle passing = " << sit->first << std::endl;
				for (std::vector<std::vector<int>>::iterator tit = sit->second.begin(); tit != sit->second.end(); ++tit) {
					std::cout << "\t\t{" << tit->at(0) << "," << tit->at(1) << "},{" << tit->at(2) << "," << tit->at(3) << "},{" << tit->at(4) << "," << tit->at(5) << "},{" << tit->at(6) << "," << tit->at(7) << "}" << std::endl;
				}
			}
		}
	}

	if (printOption != "" && printOption != "console") {
		std::ofstream myfile(printOption, std::ios::app);
		for (std::vector< std::map<int, std::vector<std::vector<int>>>>::iterator it = solutionMapVect.begin(); it != solutionMapVect.end(); ++it) 	{
			myfile << "queue = " << std::distance(solutionMapVect.begin(), it) + 1 << std::endl;
			for (std::map<int, std::vector<std::vector<int>>>::iterator sit = it->begin(); sit != it->end(); ++sit) {
				myfile << "\tvehicle passing = " << sit->first << std::endl;
				for (std::vector<std::vector<int>>::iterator tit = sit->second.begin(); tit != sit->second.end(); ++tit) {
					myfile << "\t\t{" << tit->at(0) << "," << tit->at(1) << "},{" << tit->at(2) << "," << tit->at(3) << "},{" << tit->at(4) << "," << tit->at(5) << "},{" << tit->at(6) << "," << tit->at(7) << "}" << std::endl;
				}
			}
		}
		myfile.close();
	}

	return solutionMapVect;
}
*/



//			OLD!!! REFERE TO possibleSolXCircle
/*
std::map<int, std::vector<std::vector<int>>> opt::VehNumber1Circle(std::vector<Car> circle, std::map<std::array<double, 4>, std::vector<std::array<std::pair<int, int>, 4>>> mapDataset, std::string printOption)
{
	std::array<double, 4> key = { -3.14, -1.57, 0.0, 1.57 };

	int maxqueuepos = 0;
	for (std::vector<Car>::iterator it = circle.begin(); it != circle.end(); ++it)
	{
		if (it->getQueuePosition() > maxqueuepos) maxqueuepos = it->getQueuePosition();
	}
	std::map<int, std::vector<std::vector<int>>> solutionMap;

	for (std::vector<std::array<std::pair<int, int>, 4>>::iterator datait = mapDataset[key].begin(); datait != mapDataset[key].end(); ++datait)
	{
		int counter = 0;
		int ones = 0;
		// Check that the position of my vehicles is the same of the one in the Dataset
		switch (circle.size())
		{
		case 1:
			if (circle.at(0).getQueuePosition() == datait->at(carUtility::checkHeading(circle.at(0).getHeading()) - 1).first) {
				for (std::vector<Car>::iterator sit = circle.begin(); sit != circle.end(); ++sit) {
					std::vector<int> Sol1;
					if (sit->getSignal() == datait->at(carUtility::checkHeading(sit->getHeading()) - 1).second) {
						counter += 1;
					}
					if (sit == (circle.end() - 1) && counter > 0) {
						//Test signals equaliti or 1 in mapped
						if ((circle.at(0).getSignal() == datait->at(carUtility::checkHeading(circle.at(0).getHeading()) - 1).second || datait->at(carUtility::checkHeading(circle.at(0).getHeading()) - 1).second == 1))
						{
							if (datait->at(0).first <= maxqueuepos && datait->at(1).first <= maxqueuepos && datait->at(2).first <= maxqueuepos && datait->at(3).first <= maxqueuepos)
							{
								Sol1 = { datait->at(0).first, datait->at(0).second, datait->at(1).first, datait->at(1).second, datait->at(2).first, datait->at(2).second, datait->at(3).first, datait->at(3).second };
								std::map<int, std::vector<std::vector<int>>>::iterator fit = solutionMap.find(counter);
								if (fit == solutionMap.end()) {
									std::vector<std::vector<int>> Sol2 = { Sol1 };
									solutionMap[counter] = Sol2;
								}
								else { fit->second.push_back(Sol1); }
							}
						}
					}
				}
			}
			break;
		case 2:
			if (circle.at(0).getQueuePosition() == datait->at(carUtility::checkHeading(circle.at(0).getHeading()) - 1).first && circle.at(1).getQueuePosition() == datait->at(carUtility::checkHeading(circle.at(1).getHeading()) - 1).first)
			{
				for (std::vector<Car>::iterator sit = circle.begin(); sit != circle.end(); ++sit) {
					std::vector<int> Sol1;
					if (sit->getSignal() == datait->at(carUtility::checkHeading(sit->getHeading()) - 1).second) {
						counter += 1;
					}
					if (sit == (circle.end() - 1) && counter > 0) {
						//Test signals equaliti or 1 in mapped
						if ((circle.at(0).getSignal() == datait->at(carUtility::checkHeading(circle.at(0).getHeading()) - 1).second || datait->at(carUtility::checkHeading(circle.at(0).getHeading()) - 1).second == 1) && (circle.at(1).getSignal() == datait->at(carUtility::checkHeading(circle.at(1).getHeading()) - 1).second || datait->at(carUtility::checkHeading(circle.at(1).getHeading()) - 1).second == 1))
						{
							if (datait->at(0).first <= maxqueuepos && datait->at(1).first <= maxqueuepos && datait->at(2).first <= maxqueuepos && datait->at(3).first <= maxqueuepos)
							{
								Sol1 = { datait->at(0).first, datait->at(0).second, datait->at(1).first, datait->at(1).second, datait->at(2).first, datait->at(2).second, datait->at(3).first, datait->at(3).second };
								std::map<int, std::vector<std::vector<int>>>::iterator fit = solutionMap.find(counter);
								if (fit == solutionMap.end()) {
									std::vector<std::vector<int>> Sol2 = { Sol1 };
									solutionMap[counter] = Sol2;
								}
								else { fit->second.push_back(Sol1); }
							}
						}
					}
				}
			}
			break;
		case 3:
			if (circle.at(0).getQueuePosition() == datait->at(carUtility::checkHeading(circle.at(0).getHeading()) - 1).first && circle.at(1).getQueuePosition() == datait->at(carUtility::checkHeading(circle.at(1).getHeading()) - 1).first && circle.at(2).getQueuePosition() == datait->at(carUtility::checkHeading(circle.at(2).getHeading()) - 1).first)
			{
				for (std::vector<Car>::iterator sit = circle.begin(); sit != circle.end(); ++sit) {
					std::vector<int> Sol1;
					if (sit->getSignal() == datait->at(carUtility::checkHeading(sit->getHeading()) - 1).second) {
						counter += 1;
					}
					if (sit == (circle.end() - 1) && counter > 0) {
						//Test signals equaliti or 1 in mapped
						if ((circle.at(0).getSignal() == datait->at(carUtility::checkHeading(circle.at(0).getHeading()) - 1).second || datait->at(carUtility::checkHeading(circle.at(0).getHeading()) - 1).second == 1) && (circle.at(1).getSignal() == datait->at(carUtility::checkHeading(circle.at(1).getHeading()) - 1).second || datait->at(carUtility::checkHeading(circle.at(1).getHeading()) - 1).second == 1) && (circle.at(2).getSignal() == datait->at(carUtility::checkHeading(circle.at(2).getHeading()) - 1).second || datait->at(carUtility::checkHeading(circle.at(2).getHeading()) - 1).second == 1))
						{
							if (datait->at(0).first <= maxqueuepos && datait->at(1).first <= maxqueuepos && datait->at(2).first <= maxqueuepos && datait->at(3).first <= maxqueuepos)
							{
								Sol1 = { datait->at(0).first, datait->at(0).second, datait->at(1).first, datait->at(1).second, datait->at(2).first, datait->at(2).second, datait->at(3).first, datait->at(3).second };
								std::map<int, std::vector<std::vector<int>>>::iterator fit = solutionMap.find(counter);
								if (fit == solutionMap.end()) {
									std::vector<std::vector<int>> Sol2 = { Sol1 };
									solutionMap[counter] = Sol2;
								}
								else { fit->second.push_back(Sol1); }
							}
						}
					}
				}
			}
			break;
		case 4:
			if (circle.at(0).getQueuePosition() == datait->at(carUtility::checkHeading(circle.at(0).getHeading()) - 1).first && circle.at(1).getQueuePosition() == datait->at(carUtility::checkHeading(circle.at(1).getHeading()) - 1).first && circle.at(2).getQueuePosition() == datait->at(carUtility::checkHeading(circle.at(2).getHeading()) - 1).first && circle.at(3).getQueuePosition() == datait->at(carUtility::checkHeading(circle.at(3).getHeading()) - 1).first)
			{
				for (std::vector<Car>::iterator sit = circle.begin(); sit != circle.end(); ++sit) {
					std::vector<int> Sol1;
					if (sit->getSignal() == datait->at(carUtility::checkHeading(sit->getHeading()) - 1).second && sit->getSignal() != 1) {
						counter += 1;
					}
					if (sit == (circle.end() - 1) && counter > 0) {
						//Test signals equaliti or 1 in mapped
						if ((circle.at(0).getSignal() == datait->at(carUtility::checkHeading(circle.at(0).getHeading()) - 1).second || datait->at(carUtility::checkHeading(circle.at(0).getHeading()) - 1).second == 1) && (circle.at(1).getSignal() == datait->at(carUtility::checkHeading(circle.at(1).getHeading()) - 1).second || datait->at(carUtility::checkHeading(circle.at(1).getHeading()) - 1).second == 1) && (circle.at(2).getSignal() == datait->at(carUtility::checkHeading(circle.at(2).getHeading()) - 1).second || datait->at(carUtility::checkHeading(circle.at(2).getHeading()) - 1).second == 1) && (circle.at(3).getSignal() == datait->at(carUtility::checkHeading(circle.at(3).getHeading()) - 1).second || datait->at(carUtility::checkHeading(circle.at(3).getHeading()) - 1).second == 1))
						{
							if (datait->at(0).first <= maxqueuepos && datait->at(1).first <= maxqueuepos && datait->at(2).first <= maxqueuepos && datait->at(3).first <= maxqueuepos)
							{
								Sol1 = { datait->at(0).first, datait->at(0).second, datait->at(1).first, datait->at(1).second, datait->at(2).first, datait->at(2).second, datait->at(3).first, datait->at(3).second };
								std::map<int, std::vector<std::vector<int>>>::iterator fit = solutionMap.find(counter);
								if (fit == solutionMap.end()) {
									std::vector<std::vector<int>> Sol2 = { Sol1 };
									solutionMap[counter] = Sol2;
								}
								else { fit->second.push_back(Sol1); }
							}
						}
					}
					if (sit->getSignal() == datait->at(carUtility::checkHeading(sit->getHeading()) - 1).second && sit->getSignal() == 1) {
						ones += 1;
					}
					if (sit == (circle.end() - 1) && ones == 4) {
						//Test signals equaliti or 1 in mapped
						if ((circle.at(0).getSignal() == datait->at(carUtility::checkHeading(circle.at(0).getHeading()) - 1).second && datait->at(carUtility::checkHeading(circle.at(0).getHeading()) - 1).second == 1) && (circle.at(1).getSignal() == datait->at(carUtility::checkHeading(circle.at(1).getHeading()) - 1).second && datait->at(carUtility::checkHeading(circle.at(1).getHeading()) - 1).second == 1) && (circle.at(2).getSignal() == datait->at(carUtility::checkHeading(circle.at(2).getHeading()) - 1).second && datait->at(carUtility::checkHeading(circle.at(2).getHeading()) - 1).second == 1) && (circle.at(3).getSignal() == datait->at(carUtility::checkHeading(circle.at(3).getHeading()) - 1).second && datait->at(carUtility::checkHeading(circle.at(3).getHeading()) - 1).second == 1))
						{
							if (datait->at(0).first <= maxqueuepos && datait->at(1).first <= maxqueuepos && datait->at(2).first <= maxqueuepos && datait->at(3).first <= maxqueuepos)
							{
								Sol1 = { datait->at(0).first, datait->at(0).second, datait->at(1).first, datait->at(1).second, datait->at(2).first, datait->at(2).second, datait->at(3).first, datait->at(3).second };
								std::map<int, std::vector<std::vector<int>>>::iterator fit = solutionMap.find(0);
								if (fit == solutionMap.end()) {
									std::vector<std::vector<int>> Sol2 = { Sol1 };
									solutionMap[0] = Sol2;
								}
								else { fit->second.push_back(Sol1); }
							}
						}
					}
				}
			}
			break;
		}
	}


	if (printOption == "") { return solutionMap; }

	if (printOption == "console") {
		for (std::map<int, std::vector<std::vector<int>>>::iterator sit = solutionMap.begin(); sit != solutionMap.end(); ++sit) {
			std::cout << "vehicle passing = " << sit->first << std::endl;
			for (std::vector<std::vector<int>>::iterator tit = sit->second.begin(); tit != sit->second.end(); ++tit) {
				std::cout << "\t{" << tit->at(0) << "," << tit->at(1) << "},{" << tit->at(2) << "," << tit->at(3) << "},{" << tit->at(4) << "," << tit->at(5) << "},{" << tit->at(6) << "," << tit->at(7) << "}" << std::endl;
			}
		}
	}

	if (printOption != "" && printOption != "console") {
		std::ofstream myfile(printOption, std::ios::app);
		for (std::map<int, std::vector<std::vector<int>>>::iterator sit = solutionMap.begin(); sit != solutionMap.end(); ++sit) {
			myfile << "vehicle passing = " << sit->first << std::endl;
			for (std::vector<std::vector<int>>::iterator tit = sit->second.begin(); tit != sit->second.end(); ++tit) {
				myfile << "\t{" << tit->at(0) << "," << tit->at(1) << "},{" << tit->at(2) << "," << tit->at(3) << "},{" << tit->at(4) << "," << tit->at(5) << "},{" << tit->at(6) << "," << tit->at(7) << "}" << std::endl;
			}
		}
		myfile.close();
	}

	return solutionMap;
}
*/


/*
void opt::updateMap(std::map<int, std::vector<Car>>& mapVehicle, std::vector<Car>& solution)
{
	// this allow to take care of the start and stop of vehicles
	for (std::map<int, std::vector<Car>>::iterator it = mapVehicle.begin(); it != mapVehicle.end(); ++it)
	{
		for (std::vector<Car>::iterator sit = it->second.begin(); sit != it->second.end(); ++sit)
		{
			for (std::vector<Car>::iterator sol = solution.begin(); sol != solution.end(); ++sol)
			{
				if (sit->getHeading() == sol->getHeading())
				{
					sit->setSettedSignal(sol->getSignal());
				}
			}
		}
	}
	// Start of the map shifting given a certain solution
	for (std::vector<Car>::iterator sol = solution.begin(); sol != solution.end(); ++sol)
	{
		if (sol->getSignal() > 1) {
			// aux contains all the Car which has the same heading of the tested solution but different queue position
			std::vector<Car> aux;
			for (std::map<int, std::vector<Car>>::iterator mit = mapVehicle.begin(); mit != mapVehicle.end(); ++mit)
			{
				for (std::vector<Car>::iterator smit = mit->second.begin(); smit != mit->second.end(); ++smit)
				{
					if (smit->getHeading() == sol->getHeading()) {
						if (smit->getQueuePosition() == sol->getQueuePosition()) {
							//mit->second.erase(smit);
						}
						if (smit->getQueuePosition() != sol->getQueuePosition() && smit->getSignal() != 0)
						{
							aux.push_back(*smit);

						}
					}
				}
			}
			//once the aux vector is filled, its headint is taken as reference and the map is updated with all Car in the aux heading removed
			if (aux.size() > 0)
			{
				double heading = aux.begin()->getHeading();
				for (std::map<int, std::vector<Car>>::iterator mit = mapVehicle.begin(); mit != mapVehicle.end(); ++mit)
				{
					std::vector<Car> aux2;
					for (std::vector<Car>::iterator smit = mit->second.begin(); smit != mit->second.end(); ++smit)
					{
						if (smit->getHeading() != heading) {
							aux2.push_back(*smit);
						}
					}
					mit->second = aux2;
				}
				
				//the map is updated setting all the Car contained in the aux vector
				std::map<int, std::vector<Car>>::iterator mit = mapVehicle.begin();
				for (std::vector<Car>::iterator vit = aux.begin(); vit != aux.end(); ++vit)
				{

					std::vector<Car> aux3 = carUtility::insertCarInVector(mit->second, *vit);
					
					mit->second = aux3;
					
					mit++;

				}
			}
		}
	}
}
*/

//Not used
/*
void opt::Rec(std::vector<std::vector<Car>>& vByC, std::map<std::array<double, 4>, std::vector<std::array<std::pair<int, int>, 4>>>& mapDataset, Chess& myChess, std::vector<Car>& solVector, std::vector<std::vector<Car>>& vecSolVector)
{

	if (solVector.size() > 0 && solVector.at(0).getQueuePosition() == 6 && solVector.at(1).getQueuePosition() == 6 && solVector.at(2).getQueuePosition() == 6 && solVector.at(3).getQueuePosition() == 6)
	{
		for (std::vector<std::vector<Car>>::iterator it = vecSolVector.begin(); it != vecSolVector.end(); ++it)
		{
			std::cout << "\n" << std::endl;
			for (std::vector<Car>::iterator sit = it->begin(); sit != it->end(); ++sit)
			{
				std::cout << "heading = " << sit->getHeading() << " position = " << sit->getQueuePosition() << " signal = " << sit->getSignal() << std::endl;
			}
		}
	}

	else
	{
		std::map<int, std::vector<std::vector<int>>> solMap;

		solMap = opt::VehNumber1Circle(vByC.at(0), mapDataset, "Console");
		//printMap(solMap);
		//std::vector<Car> solVector = {};
		//std::vector<std::vector<Car>> vecSolVector;
		for (std::map<int, std::vector<std::vector<int>>>::reverse_iterator it = solMap.rbegin(); it != solMap.rend(); ++it)
		{
			solVector = {};
			for (std::vector<std::vector<int>>::reverse_iterator vit = it->second.rbegin(); vit != it->second.rend(); ++vit)
			{
				//check del segnale partedo dal basso delle soluzioni e queindi da quelle con il maggior numero di veicoli
				std::cout << "soluzione in aggiornamento:" << std::endl;
				std::cout << "{" << vit->at(0) << "," << vit->at(1) << "},{" << vit->at(2) << "," << vit->at(3) << "},{" << vit->at(4) << "," << vit->at(5) << "},{" << vit->at(6) << "," << vit->at(7) << "}" << std::endl;
				if (vit->at(1) == 1) {
					int position = vit->at(0);
					Car nexCircle = vByC.at(position - 1).at(0);
					solVector.push_back(nexCircle);

				}
				if (vit->at(1) != 1) {
					if (vit->at(0) < 6) {
						int position = vit->at(0);
						Car nexcircle = vByC.at(position).at(0);
						solVector.push_back(nexcircle);
					}
				}
				if (vit->at(3) == 1) {
					int position = vit->at(2);
					Car nexCircle = vByC.at(position - 1).at(1);
					solVector.push_back(nexCircle);
				}
				if (vit->at(3) != 1) {
					if (vit->at(2) < 6) {
						int position = vit->at(2);
						Car nexcircle = vByC.at(position).at(1);
						solVector.push_back(nexcircle);
					}
				}
				if (vit->at(5) == 1) {
					int position = vit->at(4);
					Car nexCircle = vByC.at(position - 1).at(2);
					solVector.push_back(nexCircle);
				}
				if (vit->at(5) != 1) {
					if (vit->at(4) < 6) {
						int position = vit->at(4);
						Car nexcircle = vByC.at(position).at(2);
						solVector.push_back(nexcircle);
					}
				}
				if (vit->at(7) == 1) {
					int position = vit->at(6);
					Car nexCircle = vByC.at(position - 1).at(3);
					solVector.push_back(nexCircle);
				}
				if (vit->at(7) != 1) {
					if (vit->at(6) < 6) {
						int position = vit->at(6);
						Car nexcircle = vByC.at(position).at(3);
						solVector.push_back(nexcircle);
					}
				}
				std::cout << "nuova soluzione di veicoli all'inizio: " << std::endl;
				for (std::vector<Car>::iterator pit = solVector.begin(); pit != solVector.end(); ++pit)
				{
					std::cout << "heading = " << pit->getHeading() << " position = " << pit->getQueuePosition() << " signal = " << pit->getSignal() << std::endl;
				}
				vecSolVector.push_back(solVector);
				std::vector<Car> newsolvector;


				//Rec(vecSolVector, mapDataset, myChess, newsolvector, vecSolVector);
			}
		}
	}
}
*/

/*
void opt::recursive(std::vector<Car>& newLine, std::map<int, std::vector<std::vector<int>>>& solMap, std::vector<std::vector<Car>>& vByC, Chess myChess, std::map<std::array<double, 4>, std::vector<std::array<std::pair<int, int>, 4>>>& mapDataset)
{
	myChess.printChess();
	while (myChess.findFirstPosition(-3.14) != 0 && myChess.findFirstPosition(-1.57) != 0 && myChess.findFirstPosition(0.0) != 0 && myChess.findFirstPosition(1.57) != 0)
	{
		for (std::map<int, std::vector<std::vector<int>>>::reverse_iterator it = solMap.rbegin(); it != solMap.rend(); ++it) {
			for (std::vector<std::vector<int>>::reverse_iterator sit = it->second.rbegin(); sit != it->second.rend(); ++sit) {
				std::cout << "tested solution : {" << sit->at(0) << "," << sit->at(1) << "},{" << sit->at(2) << "," << sit->at(3) << "},{" << sit->at(4) << "," << sit->at(5) << "},{" << sit->at(6) << "," << sit->at(7) << "}" << std::endl;
				if (sit->at(1) != 1) { myChess.delCarStart(-3.14, sit->at(0)); }
				if (sit->at(3) != 1) { myChess.delCarStart(-1.57, sit->at(2)); }
				if (sit->at(5) != 1) { myChess.delCarStart(0.0, sit->at(4)); }
				if (sit->at(7) != 1) { myChess.delCarStart(1.57, sit->at(6)); }
				if (myChess.findFirstPosition(-3.14) != 0) {
					if (myChess.findFirstPosition(-3.14) == sit->at(0)) {
						Car aux(-3.14, vByC.at(myChess.findFirstPosition(-3.14) - 1).at(0).getQueuePosition(), vByC.at(myChess.findFirstPosition(-3.14) - 1).at(0).getSignal());
						newLine.push_back(aux);
					}
					if (myChess.findFirstPosition(-3.14) != sit->at(0)) {
						Car aux(-3.14, myChess.findFirstPosition(-3.14), vByC.at(myChess.findFirstPosition(-3.14) - 1).at(0).getSignal());
						newLine.push_back(aux);
					}
				}
				if (myChess.findFirstPosition(-1.57) != 0) {
					if (myChess.findFirstPosition(-1.57) == sit->at(2)) {
						Car aux(-1.57, vByC.at(myChess.findFirstPosition(-1.57) - 1).at(1).getQueuePosition(), vByC.at(myChess.findFirstPosition(-1.57) - 1).at(1).getSignal());
						newLine.push_back(aux);
					}
					if (myChess.findFirstPosition(-1.57) != sit->at(2)) {
						Car aux(-1.57, myChess.findFirstPosition(-1.57), vByC.at(myChess.findFirstPosition(-1.57) - 1).at(1).getSignal());
						newLine.push_back(aux);
					}
				}
				if (myChess.findFirstPosition(0.0) != 0) {
					if (myChess.findFirstPosition(0.0) == sit->at(4)) {
						Car aux(0.0, vByC.at(myChess.findFirstPosition(0.0) - 1).at(2).getQueuePosition(), vByC.at(myChess.findFirstPosition(0.0) - 1).at(2).getSignal());
						newLine.push_back(aux);
					}
					if (myChess.findFirstPosition(0.0) != sit->at(4)) {
						Car aux(0.0, myChess.findFirstPosition(0.0), vByC.at(myChess.findFirstPosition(0.0) - 1).at(2).getSignal());
						newLine.push_back(aux);
					}
				}
				if (myChess.findFirstPosition(1.57) != 0) {
					if (myChess.findFirstPosition(1.57) == sit->at(6)) {
						Car aux(1.57, vByC.at(myChess.findFirstPosition(1.57) - 1).at(3).getQueuePosition(), vByC.at(myChess.findFirstPosition(1.57) - 1).at(3).getSignal());
						newLine.push_back(aux);
					}
					if (myChess.findFirstPosition(1.57) != sit->at(6)) {
						Car aux(1.57, myChess.findFirstPosition(1.57), vByC.at(myChess.findFirstPosition(1.57) - 1).at(3).getSignal());
						newLine.push_back(aux);
					}
				}
				std::cout << "\n";
				for (std::vector<Car>::iterator cit = newLine.begin(); cit != newLine.end(); ++cit) {
					std::cout << "heading = " << cit->getHeading() << " position = " << cit->getQueuePosition() << " signal = " << cit->getSignal() << std::endl;
				}
				std::map<int, std::vector<std::vector<int>>> newMap = opt::VehNumber1Circle(newLine, mapDataset, "console");
				newLine = {};

				Recursive(newLine, newMap, vByC, myChess, mapDataset);
			}
		}
	}
}
*/
