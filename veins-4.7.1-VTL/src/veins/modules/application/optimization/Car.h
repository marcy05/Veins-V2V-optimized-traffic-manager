#ifndef CAR_H
#define CAR_H


/*
	@author Marcello Sgarbi
	@date 07-Feb-2019
*/


#include <iostream>
#include <vector>
#include <array>


class Car
{
public:
	Car();
	Car(double heading);
	Car(double heading, int position);
	Car(double heading, int position, int signal);
	~Car();

	void setHeading(double heading);
	double getHeading();

	void setQueuePosition(int position);
	int getQueuePosition();

	void setSignal(int signal);
	int getSignal();

	void printAttributes();

public:
	void setSettedSignal(int signal);
	int getSettedSignal();

	void setStart(int StartStop);
	int getStart();
	void setStartCounter(int startCounter);
	int getStartCounter();

	void setStop(int Stop);
	int getStop();
	void setStopCounter(int stopCounter);
	int getStopCounter();

	void printStartStop();
	
	void setId(int id);
	int getId();


private:
	double m_heading;
	std::vector<int> m_possibleCommand = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11 };
	int m_queuePosition;
	int m_signal = 0;
	int m_start = 1;
	int m_stop = 0;
	int m_settedSignal = 0;
	int m_stopCounter = 0;
	int m_startCounter = 0;
	int m_id = -1;
	
};


namespace carUtility
{
	int checkHeading(double heading);
	double toHeading(int value);
	bool checkToHeading(int value);
	// InsertCarInVector test the heading response and insert the Car in the position depending on the CheckHeading function. If already preset it is overwritten
	std::vector<Car> insertCarInVector(std::vector<Car>& myVector, Car& Ins);
	void insertCarInVectorVoid(std::vector<Car>& myVector, Car& Ins);
	
	void addUniqueCarInVector(std::vector<Car>& myVector, Car newCar);

}

#endif // !CAR_H
