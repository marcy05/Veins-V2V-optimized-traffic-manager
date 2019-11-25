/*
	@author Marcello Sgarbi
	@date 15-Feb-2019
	@updated 19-Feb-2019
*/
#ifndef OPTIMIZER_H
#define OPTIMIZER_H


#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <array>
#include "Car.h"
#include "Chess.h" // per carInMap2Chess
#include <time.h>
#include "C:/omnetpp-5.4.1/include/omnetpp/csimulation.h"

namespace opt
{
	/* Given vehicles queue position and theri signal, they are organized in Car objects into a map by directions */
	std::map<double, std::vector<Car>> carInMap(std::vector<int> Evehicles, std::vector<int> Esignals, std::vector<int> Nvehicles, std::vector<int> Nsignals, std::vector<int> Wvehicles, std::vector<int> Wsignals, std::vector<int> Svehicles, std::vector<int> Ssignals);

	/* Set Car defined by direction into the intersection. Optional see ReadMe. */
	void carInMap2Chess(Chess& myChess, std::map<double, std::vector<Car>> inputVehciles);

	/* Takes as input the vehiclebyCircle output and the map dataset generated from the xml reading
		print options: ""->does not print out anything
					   "console" -> print the output on the console
					   "PUT_YOUR_OUTPUT_PATH" -> using a path it save the output in the desired path, no control on its validity are done.
	*/
	std::map<int, std::vector<Car>> mapVehicleByCircle(std::map<double, std::vector<Car>>& inputVector, std::string print = "");

	/* given the vehicles to be tested in a vector<Car>, the function search into the solution dataset loaded from the xml */
	std::map<int, std::vector<std::vector<Car>>> possibleSolXCircle(std::vector<Car> circle, std::map<std::array<double, 4>, std::vector<std::array<std::pair<int, int>, 4>>> mapDataset, std::string printOption = "");



	

	/*Recursive
		Takes several input:
			vehicleMap ------> is the output from mapVehicleByCircle
			testedsolutions -> is the solution tested eachiteration (pass it as empty vector)
			fullSolutions ---> is the output of the recursive function, collecting all solutions. (pass it as empty variable)
			mapDataset ------> is the dataset of all possible solutions for the intersection
	*/
	void recursive(std::map<int, std::vector<Car>> vehicleMap, std::vector<std::vector<Car>> testedSolutions, std::map<int, std::vector<std::vector<std::vector<Car>>>>& fullSolutions, std::map<std::array<double, 4>, std::vector<std::array<std::pair<int, int>, 4>>> mapDataset, bool& escape, double& time);
	/* Unpdate the output of the Recursive() function with the Start&Stop for each Car */
	void startAndStopUpdate(std::map<int, std::vector<std::vector<std::vector<Car>>>>& fullSolutions);
	/* Selecting the solution with the minimum number of start and stop */
	std::vector<std::vector<Car>> chooseMinStartStop(std::map<int, std::vector<std::vector<std::vector<Car>>>>& fullSolutions);


	/****************************************************************************************************************************************************************************************************************************
	*																								UTILITY
	****************************************************************************************************************************************************************************************************************************/
	/* Check among the heading vector, which are the remaining, after deleting the declared */
	void possibleHeading(std::vector<double>& heading, double head1);
	void possibleHeading(std::vector<double>& heading, double head1, double head2);
	void possibleHeading(std::vector<double>& heading, double head1, double head2, double head3);

	/* Used in updateMap2 to delate empty vector */
	void eraseEmptyQueue(std::map<int, std::vector<Car>>& mapVehicle);

	/*	Update the output map of mapVehicleByCircle with passing a chosen solution	*/
	void updateMap2(std::map<int, std::vector<Car>>& mapVehicle, std::vector<Car>& solution);
	
	/* Printing vehicle by circle.
		path = "" -----> console printing
			ss = "" ---> start&stop not printed
			ss = "ss" -> print start&stop
		path = "file_path.txt" -> print to a file
			ss = "" ------------> start&stop not printed
			ss = "ss" ----------> print start&stop */
	void printMap2(std::map<int, std::vector<Car>>& vehByCircle, std::string path = "", std::string ss = "");

	/* Print heading, position, signal for each Car in the vector*/
	void printVector(std::vector<Car>& vector);
	/* Check for 0 signal in the map of Vehicle. If founded it means that no signal it's been assigned to a Car */
	bool signal0(std::map<int, std::vector<Car>> map);
	/* Given vehicles ordered by direction, it detect which one contains more vehicles */
	double leaderDir(std::map<double, std::vector<int>>& signalMap);
	/* Given vehicles devided by circles, it detect if vehicles the map is empty*/
	bool isEmpty(std::map<int, std::vector<Car>> &vehByCircle);
	/* Print queue position and signal for each Car in a circle solution */
	void printTestedSolution(std::vector<Car> sol, std::string path = "");

	/* Given a complete solution for the intersection it print queue position and signal for each Car
		if type = "" ---------> print queue position and signal of each Car
			path = "" --------> print it to the console
			path = "my_path" -> print it to file
		if type = "ss" -------> print start counter and stop counter of each Car
			path = "" --------> print it to the console
			path = "my_path" -> print it to file
	*/
	void printVectorVector(std::vector<std::vector<Car>> testedSolutions, std::string path = "", std::string type = "");
	/* Given a complete solution for the intersection and a Car to be deleted, it search for it and delete it */
	void delCarFromVecVec(std::vector<std::vector<Car>>& myvec, Car todel);
	/* Given a complete solution for the intersection and a solution for one circle to be deleted, it search for it and delete it */
	void delVecFromVecVec(std::vector<std::vector<Car>>& myvec, std::vector<Car> todel);
	/* Check if two "Car" are equal */
	bool isEqual(std::vector<Car> t1, std::vector<Car> t2);
	bool isEqual(std::vector<int> v1, std::vector<int> v2);
	

	bool fromChoosenToVehicleSignal(std::vector<std::vector<Car>> chosSol, double heading, int queuePos) ;






	/****************************************************************************************************************************************************************************************************************************
	*																			NOT USED FUNCTIONS (Working problems or old)
	****************************************************************************************************************************************************************************************************************************/

	/* Given the output of carInMap function collecto vehicles that are in the same queue position into a vector
		OLD DO NOT USE, REFERE TO mapVehicleByCircle	
	*/
	//std::vector<std::vector<Car>> VehiclebyCircle(std::map<double, std::vector<Car>>& inputVector);
	
	// DO NOT USE! Refere to  possibleSolXCircle
	/*		
	Takes as input the vehiclebyCircle output and the map dataset generated from the xml reading
		print options: ""->does not print out anything
					   "console" -> print the output on the console
					   "PUT_YOUR_OUTPUT_PATH" -> using a path it save the output in the desired path, no control on its validity are done.
		the output vector is so generated:
		(queue1(number_of_vehicles_passing_per_solution(solution(xxxxxxxx),
														solution(yyyyyyyy),
														...),
				number_of_vehicles_passing_per_solution(solution(xxxxxxxx),
														solution(yyyyyyyy),
														...),
				...),
		 queue2(number_of_vehicles_passing_per_solution(solution(xxxxxxxx),
														solution(yyyyyyyy),
														...),
				number_of_vehicles_passing_per_solution(solution(xxxxxxxx),
														solution(yyyyyyyy),
														...),
				...),
		 ...,
		 queue6(...)
		 )
		 The solution(xxxxxxxx) are intended to be (heading1, signal1, heading2, signal2, heading3, signal3, heading4, signal4)
	*/
	//std::vector<std::map<int, std::vector<std::vector<int>>>> VehNumberPerSolution(std::vector<std::vector<Car>> vByC, std::map<std::array<double, 4>, std::vector<std::array<std::pair<int, int>, 4>>> mapDataset, std::string printOption = "");

	/* OLD!!! REFERE TO possibleSolXCircle */
	//std::map<int, std::vector<std::vector<int>>> VehNumber1Circle(std::vector<Car> circle, std::map<std::array<double, 4>, std::vector<std::array<std::pair<int, int>, 4>>> mapDataset, std::string printOption = "");

	//void updateMap(std::map<int, std::vector<Car>>& mapVehicle, std::vector<Car>& solution);

	//void Rec(std::vector<std::vector<Car>>& vByC, std::map<std::array<double, 4>, std::vector<std::array<std::pair<int, int>, 4>>>& mapDataset, Chess& myChess, std::vector<Car>& solVector, std::vector<std::vector<Car>>& vecSolVector);
	//void Recursive(std::vector<Car>& newLine, std::map<int, std::vector<std::vector<int>>>& solMap, std::vector<std::vector<Car>>& vByC, Chess myChess, std::map<std::array<double, 4>, std::vector<std::array<std::pair<int, int>, 4>>>& mapDataset);

}





















#endif // !OPTIMIZER_H

