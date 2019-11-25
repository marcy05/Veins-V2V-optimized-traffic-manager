/*
	@author Marcello Sgarbi
	@date 07-Feb-2019
*/

#include "Car.h"

Car::Car()
{
}

Car::Car(double heading)
{
	m_heading = heading;
}

Car::Car(double heading, int position)
{
	m_heading = heading;
	m_queuePosition = position;
}
Car::Car(double heading, int position, int signal)
{
	m_heading = heading;
	m_queuePosition = position;
	m_signal = signal;
}

Car::~Car()
{
}

void Car::setHeading(double heading) { m_heading = heading; }

double Car::getHeading() { return m_heading; }

void Car::setQueuePosition(int position) { m_queuePosition = position; }

int Car::getQueuePosition() { return m_queuePosition; }

void Car::setSignal(int signal) { m_signal = signal; }

int Car::getSignal() { return m_signal; }

void Car::printAttributes() { 
	std::cout << "heading = " << m_heading << " queue position = " << m_queuePosition << " signal = " << m_signal << std::endl;
}





void Car::setSettedSignal(int signal)
{
	m_settedSignal = signal;
	if (signal == 1) { setStop(signal); }
	if (signal != 1) { setStart(1); }
}

int Car::getSettedSignal()
{
	return m_settedSignal;
}

void Car::setStart(int StartStop) {
	if (m_start == 0 && m_stop == 1) {
		m_start = 1;
		m_stop = 0;
		m_startCounter += 1;
	}
}

int Car::getStart() { 
	return m_start; 
}

void Car::setStartCounter(int startCounter) {
	m_startCounter = startCounter;
}

int Car::getStartCounter() {
	return m_startCounter;
}

void Car::setStop(int Stop) {
	if (m_stop == 0 && m_start == 1) {
		m_stop = 1;
		m_start = 0;
		m_stopCounter += 1;
	}
}

int Car::getStop() {
	return m_stop;
}

void Car::setStopCounter(int stopCounter) {
	m_stopCounter = stopCounter;
}

int Car::getStopCounter() {
	return m_stopCounter;
}

void Car::printStartStop()
{
	std::cout << "\t\theading = " << m_heading << " Queue Position = " << m_queuePosition << std::endl;
	std::cout << "\t\tStart Counter = " << m_startCounter << " Stop Counter = " << m_stopCounter << std::endl;
}


void Car::setId(int id)
{
    m_id = id;
}

int Car::getId(){
    return m_id;
}






/**************************************************************************************************************************
														NAMESPACE carUtility
***************************************************************************************************************************/


int carUtility::checkHeading(double heading)
{
	if (heading > -3.15 && heading < -3.13) return 1; // East
	if (heading > -1.6 && heading < -1.4) return 2; // Nord
	if (heading > -0.1 && heading < 0.1) return 3; // West
	if (heading > 1.4 && heading < 1.6) return 4; // South
	return -1;

}

double carUtility::toHeading(int value)
{
	if (value == 1) { return -3.14; }
	if (value == 2) { return -1.57; }
	if (value == 3) { return 0.0; }
	if (value == 4) { return 1.57; }
}

bool carUtility::checkToHeading(int value)
{
	if (value == 1 || value == 2 || value == 3 || value == 4) {
		return true;
	}
	return false;
}

void carUtility::insertCarInVectorVoid(std::vector<Car>& myVector, Car& Ins)
{
	int headingResponse = static_cast<int>(carUtility::checkHeading(Ins.getHeading()));
	std::vector<Car> aux = {};

	std::array<Car, 4> auxarr;

	if (myVector.size() > 0)
	{
		for (std::vector<Car>::iterator it = myVector.begin(); it != myVector.end(); ++it)
		{
			if (carUtility::checkHeading(it->getHeading()) == 1) {
				auxarr.at(0) = *it;
			}
			if (carUtility::checkHeading(it->getHeading()) == 2) {
				auxarr.at(1) = *it;
			}
			if (carUtility::checkHeading(it->getHeading()) == 3) {
				auxarr.at(2) = *it;
			}
			if (carUtility::checkHeading(it->getHeading()) == 4) {
				auxarr.at(3) = *it;
			}
		}

		auxarr.at(headingResponse - 1) = Ins;
		for (std::array<Car, 4>::iterator it = auxarr.begin(); it != auxarr.end(); ++it)
		{
			if (it->getSignal() != 0) {
				aux.push_back(*it);
			}
		}
	}
	if (myVector.size() == 0)
	{
		aux.push_back(Ins);
	}
	myVector = aux;
}

std::vector<Car> carUtility::insertCarInVector(std::vector<Car>& myVector, Car& Ins)
{
	int headingResponse = static_cast<int>(carUtility::checkHeading(Ins.getHeading()));
	std::vector<Car> aux = {};

	std::array<Car, 4> auxarr;

	if (myVector.size() > 0)
	{
		for (std::vector<Car>::iterator it = myVector.begin(); it != myVector.end(); ++it)
		{
			if (carUtility::checkHeading(it->getHeading()) == 1) {
				auxarr.at(0) = *it;
			}
			if (carUtility::checkHeading(it->getHeading()) == 2) {
				auxarr.at(1) = *it;
			}
			if (carUtility::checkHeading(it->getHeading()) == 3) {
				auxarr.at(2) = *it;
			}
			if (carUtility::checkHeading(it->getHeading()) == 4) {
				auxarr.at(3) = *it;
			}
		}

		auxarr.at(headingResponse - 1) = Ins;
		for (std::array<Car, 4>::iterator it = auxarr.begin(); it != auxarr.end(); ++it)
		{
			aux.push_back(*it);
		}
	}
	myVector = aux;
	return myVector;
}



void carUtility::addUniqueCarInVector(std::vector<Car>& myVector, Car newCar)
{
    std::vector<Car> foud = {};
    for(std::vector<Car>::iterator it = myVector.begin(); it != myVector.end(); ++it)
    {
        if(newCar.getId() == it->getId()){
            foud.push_back(*it);
        }
    }

    if(foud.size() == 0){
        myVector.push_back(newCar);
    }

}
