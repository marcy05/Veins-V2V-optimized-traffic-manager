
#include "MapFunctions.h"




//using keytype = std::array<double, 4>;
//using soltype = std::vector<std::array<std::pair<int, int>, 4>>;
//using solElementType = std::array<std::pair<int, int>, 4>;
//using maptype = std::map<std::array<double, 4>, std::vector<std::array<std::pair<int, int>, 4>>>;


void mapFun::printMap(std::map<std::array<double, 4>, std::vector<std::array<std::pair<int, int>, 4>>>& mymap)
{
	for (std::map<std::array<double, 4>, std::vector<std::array<std::pair<int, int>, 4>>>::iterator it = mymap.begin(); it != mymap.end(); ++it)
	{
		std::cout << "(" << it->first.at(0) << ", " \
			<< it->first.at(1) << ", " \
			<< it->first.at(2) << ", " \
			<< it->first.at(3) << ")" << std::endl;
		for (std::vector<std::array<std::pair<int, int>, 4>>::iterator sit = it->second.begin(); sit != it->second.end(); ++sit)
		{
			std::cout << "\t(" << sit->at(0).first << "," << sit->at(0).second << "),(" \
				<< sit->at(1).first << "," << sit->at(1).second << "),(" \
				<< sit->at(2).first << "," << sit->at(2).second << "),(" \
				<< sit->at(3).first << "," << sit->at(3).second << ")" << std::endl;
		}

	}
}

void mapFun::printMap2File(std::map<std::array<double, 4>, std::vector<std::array<std::pair<int, int>, 4>>>& mymap, std::string destination)
{
	std::ofstream myfile(destination, std::ios::app);
	for (std::map<std::array<double, 4>, std::vector<std::array<std::pair<int, int>, 4>>>::iterator it = mymap.begin(); it != mymap.end(); ++it)
	{
		myfile << "(" << it->first.at(0) << ", " \
			<< it->first.at(1) << ", " \
			<< it->first.at(2) << ", " \
			<< it->first.at(3) << ")" << std::endl;
		for (std::vector<std::array<std::pair<int, int>, 4>>::iterator sit = it->second.begin(); sit != it->second.end(); ++sit)
		{
			myfile << "\t{{ {" << sit->at(0).first << "," << sit->at(0).second << "},{" \
				<< sit->at(1).first << "," << sit->at(1).second << "},{" \
				<< sit->at(2).first << "," << sit->at(2).second << "},{" \
				<< sit->at(3).first << "," << sit->at(3).second << "} }}," << std::endl;
		}

	}
	myfile.close();
}

void mapFun::printMap2XML(std::map<std::array<double, 4>, std::vector<std::array<std::pair<int, int>, 4>>>& mymap, std::string destination)
{
	std::ofstream myfile(destination, std::ios::app);
	myfile << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>" << std::endl;
	myfile << "<mapkey>" << std::endl;
	for (std::map<std::array<double, 4>, std::vector<std::array<std::pair<int, int>, 4>>>::iterator it = mymap.begin(); it != mymap.end(); ++it)
	{
		myfile << "\t<key1>" << it->first.at(0) << "</key1>" << std::endl;
		myfile << "\t<key2>" << it->first.at(1) << "</key2>" << std::endl;
		myfile << "\t<key3>" << it->first.at(2) << "</key3>" << std::endl;
		myfile << "\t<key4>" << it->first.at(3) << "</key4>" << std::endl;
		for (std::vector<std::array<std::pair<int, int>, 4>>::iterator sit = it->second.begin(); sit != it->second.end(); ++sit)
		{
			myfile << "\t<element>" << std::endl;
			myfile << "\t\t<h1>" << sit->at(0).first << "</h1>" << std::endl;
			myfile << "\t\t<s1>" << sit->at(0).second << "</s1>" << std::endl;
			myfile << "\t\t<h2>" << sit->at(1).first << "</h2>" << std::endl;
			myfile << "\t\t<s2>" << sit->at(1).second << "</s2>" << std::endl;
			myfile << "\t\t<h3>" << sit->at(2).first << "</h3>" << std::endl;
			myfile << "\t\t<s3>" << sit->at(2).second << "</s3>" << std::endl;
			myfile << "\t\t<h4>" << sit->at(3).first << "</h4>" << std::endl;
			myfile << "\t\t<s4>" << sit->at(3).second << "</s4>" << std::endl;
			myfile << "\t</element>" << std::endl;
		}
	}
	myfile << "</mapkey>" << std::endl;
	myfile.close();
}

void mapFun::setMapElement(std::map<std::array<double, 4>, std::vector<std::array<std::pair<int, int>, 4>>>& mymap, std::array<double, 4> key, std::array<std::pair<int, int>, 4> solution)
{
	if (mapSearch(mymap, key, solution) == false && headingSearch(mymap, key) == true)
	{
		for (std::map<std::array<double, 4>, std::vector<std::array<std::pair<int, int>, 4>>>::iterator it = mymap.begin(); it != mymap.end(); ++it)
		{
			if (it->first == key) {
				it->second.push_back(solution);
				break;
			}
		}
	}
	if (mapSearch(mymap, key, solution) == false && headingSearch(mymap, key) == false) //I have a new value
	{
		std::vector<std::array<std::pair<int, int>, 4>> aux;
		aux.push_back(solution);
		mymap.insert(std::make_pair(key, aux));

	}


}

bool mapFun::mapSearch(std::map<std::array<double, 4>, std::vector<std::array<std::pair<int, int>, 4>>>& mymap, std::array<double, 4> key, std::array<std::pair<int, int>, 4> solution)
{
	for (std::map<std::array<double, 4>, std::vector<std::array<std::pair<int, int>, 4>>>::iterator it = mymap.begin(); it != mymap.end(); ++it)
	{
		if (it->first == key)
		{
			for (std::vector<std::array<std::pair<int, int>, 4>>::iterator sit = it->second.begin(); sit != it->second.end(); ++sit)
			{
				if (*sit == solution) {
					return true;
					break;
				}
			}
		}
	}
	return false;
}

bool  mapFun::headingSearch(std::map<std::array<double, 4>, std::vector<std::array<std::pair<int, int>, 4>>>& mymap, std::array<double, 4> key)
{
	for (std::map<std::array<double, 4>, std::vector<std::array<std::pair<int, int>, 4>>>::iterator it = mymap.begin(); it != mymap.end(); ++it)
	{
		if (it->first == key) {
			return true;
			break;
		}
	}
	return false;
}

void mapFun::testAllPossibility(Chess &myChess, std::map<std::array<double, 4>, std::vector<std::array<std::pair<int, int>, 4>>>& mapDataset, int signals, std::string mode, std::string destination)
{
	using heRecType = std::vector<std::array<double, 4>>;
	using vecInt = std::vector<int>;



	heRecType headingRec = { {-3.14, -1.57, 0, 1.57} };
	vecInt signalVector;
	if (signals == 7) { signalVector = { 1, 2, 3, 4, 5, 6, 7 }; }
	if (signals == 4) { signalVector = { 1, 2, 3, 4 }; }

	vecInt queuepos1 = { 1,2,3,4,5,6 };
	vecInt queuepos2 = { 1,2,3,4,5,6 };
	vecInt queuepos3 = { 1,2,3,4,5,6 };
	vecInt queuepos4 = { 1,2,3,4,5,6 };
	std::array<std::pair<int, int>, 4> testedSol = { std::make_pair(0,0), std::make_pair(0,0), std::make_pair(0,0), std::make_pair(0,0) };
	int flag4 = 0;
	int flag3 = 0;
	int flag2 = 0;
	int flag1 = 0;

	for (vecInt::iterator it = queuepos1.begin(); it != queuepos1.end(); ++it)
	{
		myChess.setCarStart(headingRec.at(0).at(0), *it);
		myChess.setCarStart(headingRec.at(0).at(1), *it);
		myChess.setCarStart(headingRec.at(0).at(2), *it);
		myChess.setCarStart(headingRec.at(0).at(3), *it);
	}

	for (heRecType::iterator heit = headingRec.begin(); heit != headingRec.end(); ++heit) //heading
	{
		for (vecInt::iterator pi = queuepos1.begin(); pi != queuepos1.end(); ++pi) //pi position
		{
			if (mapDataset.begin() != mapDataset.end())
			{
				if (flag1 == 1 && mapDataset.find(*heit) != mapDataset.end()) {
					flag1 = 0;
					//myChess.printChess();
					//if(*pi == 6) { printMap(mapDataset); }

					//std::cout << mapDataset[*heit].rbegin()->at(0).first << std::endl;
					myChess.delCarStart(heit->at(0), mapDataset[*heit].rbegin()->at(0).first);
					//myChess.printChess();
				}
			}
			for (vecInt::iterator pj = queuepos2.begin(); pj != queuepos2.end(); ++pj) //pj position
			{
				if (mapDataset.begin() != mapDataset.end())
				{
					if (flag2 == 1 && mapDataset.find(*heit) != mapDataset.end()) {
						flag2 = 0;
						myChess.delCarStart(heit->at(1), mapDataset[*heit].rbegin()->at(1).first);
					}
				}
				for (vecInt::iterator pk = queuepos3.begin(); pk != queuepos3.end(); ++pk) //pk position
				{
					if (mapDataset.begin() != mapDataset.end()) {
						if (flag3 == 1 && mapDataset.find(*heit) != mapDataset.end()) {
							flag3 = 0;
							myChess.delCarStart(heit->at(2), mapDataset[*heit].rbegin()->at(2).first);
						}
					}

					for (vecInt::iterator pz = queuepos4.begin(); pz != queuepos4.end(); ++pz) //pz position
					{
						if (mapDataset.begin() != mapDataset.end()) {
							if (flag4 == 1 && mapDataset.find(*heit) != mapDataset.end()) {
								flag4 = 0;
								myChess.delCarStart(heit->at(3), mapDataset[*heit].rbegin()->at(3).first);
							}
						}

						for (vecInt::iterator si = signalVector.begin(); si != signalVector.end(); ++si) //si signal
						{

							if (testedSol.at(myChess.checkHeading(heit->at(0)) - 1).first != 0 && testedSol.at(myChess.checkHeading(heit->at(0)) - 1).second != 0) {
								myChess.checkAndRemoveSignal(heit->at(0), testedSol.at(myChess.checkHeading(heit->at(0)) - 1).second, testedSol.at(myChess.checkHeading(heit->at(0)) - 1).first);
								testedSol.at(myChess.checkHeading(heit->at(0)) - 1) = std::make_pair(0, 0);
							}
							if (myChess.isPossibleMovement(heit->at(0), *si, *pi)) {
								myChess.checkAndSetSignal(heit->at(0), *si, *pi);
								testedSol.at(myChess.checkHeading(heit->at(0)) - 1) = std::make_pair(*pi, *si);

								for (vecInt::iterator sj = signalVector.begin(); sj != signalVector.end(); ++sj) //sj signal
								{

									if (testedSol.at(myChess.checkHeading(heit->at(1)) - 1).first != 0 && testedSol.at(myChess.checkHeading(heit->at(1)) - 1).second != 0) {
										myChess.checkAndRemoveSignal(heit->at(1), testedSol.at(myChess.checkHeading(heit->at(1)) - 1).second, testedSol.at(myChess.checkHeading(heit->at(1)) - 1).first);
										testedSol.at(myChess.checkHeading(heit->at(1)) - 1) = std::make_pair(0, 0);
									}
									if (myChess.isPossibleMovement(heit->at(1), *sj, *pj)) {
										myChess.checkAndSetSignal(heit->at(1), *sj, *pj);
										testedSol.at(myChess.checkHeading(heit->at(1)) - 1) = std::make_pair(*pj, *sj);

										for (vecInt::iterator sk = signalVector.begin(); sk != signalVector.end(); ++sk) //sk signal
										{

											if (testedSol.at(myChess.checkHeading(heit->at(2)) - 1).first != 0 && testedSol.at(myChess.checkHeading(heit->at(2)) - 1).second != 0) {
												myChess.checkAndRemoveSignal(heit->at(2), testedSol.at(myChess.checkHeading(heit->at(2)) - 1).second, testedSol.at(myChess.checkHeading(heit->at(2)) - 1).first);
												testedSol.at(myChess.checkHeading(heit->at(2)) - 1) = std::make_pair(0, 0);
											}
											if (myChess.isPossibleMovement(heit->at(2), *sk, *pk)) {
												myChess.checkAndSetSignal(heit->at(2), *sk, *pk);
												testedSol.at(myChess.checkHeading(heit->at(2)) - 1) = std::make_pair(*pk, *sk);

												for (vecInt::iterator sz = signalVector.begin(); sz != signalVector.end(); ++sz) //sz signal 
												{

													if (testedSol.at(myChess.checkHeading(heit->at(3)) - 1).first != 0 && testedSol.at(myChess.checkHeading(heit->at(3)) - 1).second != 0) {
														myChess.checkAndRemoveSignal(heit->at(3), testedSol.at(myChess.checkHeading(heit->at(3)) - 1).second, testedSol.at(myChess.checkHeading(heit->at(3)) - 1).first);
														testedSol.at(myChess.checkHeading(heit->at(3)) - 1) = std::make_pair(0, 0);
													}
													if (myChess.isPossibleMovement(heit->at(3), *sz, *pz)) {
														//myChess.printChess();
														myChess.checkAndSetSignal(heit->at(3), *sz, *pz);
														testedSol.at(myChess.checkHeading(heit->at(3)) - 1) = std::make_pair(*pz, *sz);
														mapFun::setMapElement(mapDataset, *heit, testedSol);
														//myChess.printChess();
													}

													if (sz == signalVector.end() - 1)
													{
														myChess.checkAndRemoveSignal(heit->at(3), testedSol.at(myChess.checkHeading(heit->at(3)) - 1).second, testedSol.at(myChess.checkHeading(heit->at(3)) - 1).first);
														testedSol.at(myChess.checkHeading(heit->at(3)) - 1) = std::make_pair(0, 0);
													}
												} // sz signal end
											}

											if (sk == signalVector.end() - 1)
											{
												myChess.checkAndRemoveSignal(heit->at(2), testedSol.at(myChess.checkHeading(heit->at(2)) - 1).second, testedSol.at(myChess.checkHeading(heit->at(2)) - 1).first);
												testedSol.at(myChess.checkHeading(heit->at(2)) - 1) = std::make_pair(0, 0);
											}


										} //sk signal end

									}

									if (sj == signalVector.end() - 1)
									{
										myChess.checkAndRemoveSignal(heit->at(1), testedSol.at(myChess.checkHeading(heit->at(1)) - 1).second, testedSol.at(myChess.checkHeading(heit->at(1)) - 1).first);
										testedSol.at(myChess.checkHeading(heit->at(1)) - 1) = std::make_pair(0, 0);
									}


								}  //sj signal end

							}

							if (si == signalVector.end() - 1)
							{
								myChess.checkAndRemoveSignal(heit->at(0), testedSol.at(myChess.checkHeading(heit->at(0)) - 1).second, testedSol.at(myChess.checkHeading(heit->at(0)) - 1).first);
								testedSol.at(myChess.checkHeading(heit->at(0)) - 1) = std::make_pair(0, 0);
							}



						} //si signal end

						flag4 = 1;
						if (pz == queuepos4.end() - 1)
						{
							//myChess.printChess();
							myChess.setCarStart(heit->at(3), 1);
							myChess.setCarStart(heit->at(3), 2);
							myChess.setCarStart(heit->at(3), 3);
							myChess.setCarStart(heit->at(3), 4);
							myChess.setCarStart(heit->at(3), 5);
							myChess.setCarStart(heit->at(3), 6);
							//myChess.printChess();
						}


					}  //pz position end

					flag3 = 1;
					if (pk == queuepos3.end() - 1)
					{
						//myChess.printChess();
						myChess.setCarStart(heit->at(2), 1);
						myChess.setCarStart(heit->at(2), 2);
						myChess.setCarStart(heit->at(2), 3);
						myChess.setCarStart(heit->at(2), 4);
						myChess.setCarStart(heit->at(2), 5);
						myChess.setCarStart(heit->at(2), 6);
						//myChess.printChess();
					}

				} //pk position end

				flag2 = 1;
				if (pj == queuepos2.end() - 1)
				{
					//myChess.printChess();
					myChess.setCarStart(heit->at(1), 1);
					myChess.setCarStart(heit->at(1), 2);
					myChess.setCarStart(heit->at(1), 3);
					myChess.setCarStart(heit->at(1), 4);
					myChess.setCarStart(heit->at(1), 5);
					myChess.setCarStart(heit->at(1), 6);
					//myChess.printChess();
				}

			}  //pj position end

			flag1 = 1;
			if (pi == queuepos1.end() - 1)
			{
				//myChess.printChess();
				myChess.setCarStart(heit->at(0), 1);
				myChess.setCarStart(heit->at(0), 2);
				myChess.setCarStart(heit->at(0), 3);
				myChess.setCarStart(heit->at(0), 4);
				myChess.setCarStart(heit->at(0), 5);
				myChess.setCarStart(heit->at(0), 6);
				//myChess.printChess();
				//printMap(mapDataset);
			}
		} //pi position


	}

	if (mode == "xmlType") { mapFun::printMap2XML(mapDataset, destination); }
	if (mode == "mapType") { mapFun::printMap2File(mapDataset, destination); }
	if (mode == "terminal") { mapFun::printMap(mapDataset); }

}



