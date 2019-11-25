/*
* Project           : VTL
* Author            : Marcello Sgarbi
* Date              : Nov 29, 2018
* Purpose           : Create a data structure to handle received messages
*/

#ifndef SRC_VEINS_MODULES_APPLICATION_DATA_STRUCTURE_VEHICLEDATA_H
#define SRC_VEINS_MODULES_APPLICATION_DATA_STRUCTURE_VEHICLEDATA_H

#include "veins/base/utils/Coord.h"
#include "../optimization/Car.h"
#include "../optimization/VehicleMainCharacteristics.h"
#include <iostream>
#include <fstream>
#include "math.h"
#include <vector>
#include <iterator>
#include <map>
#include <algorithm> //for find(iteratorBegin, iteratorEnd, ElementToFind)






class VehicleData
{
private:
    int m_idVD; //store the car ID

    Coord m_positionVD;
    simtime_t m_sendtimeVD;
    double m_velocityVD;
    double m_accelerationVD;
    double m_headingVD;
    double m_yawVD;
    double m_carLengthVD;
    double m_carWidthVD;
    std::pair<double, double> m_intersectionPointVD;
    double m_distance2IntersectionVD = 0;
    int m_intersectionFlagVD = 0 ;
    double m_time2IntersectionVD = 0;
    double m_minDistanceVD ;
    int m_leaderFlagVD = -1;
    int m_leaderCounterVD = 0;
    double m_lanePositionVD;

    int m_queuePositionVD = 0;

    int m_optimizationCouterVD = 0;
    std::vector<std::string> m_allOptimizBroadReceived = {};


    std::string m_roadIdVD;

    std::vector<double> m_headingVectorVD;
    std::vector<std::pair<int, double>> m_headingPairVD;

    // Data Timed
    double intervalUpdateTime = 3;
    std::map<double, std::vector<int>> m_seenVehicleMyDirVD;
    std::map<double, std::vector<int>> m_allSeenVehicleVD;

    //Optimization
    std::map<int, std::string> m_leadersMap;
    std::string m_broadcastIdSet = "";

    bool m_optimized = false;
    int m_crossingIntersection = 0;

    //Signal
    int m_signalMapXMLVD;
    int m_signalVD = -1;

    //Surpassed 100m semaphore, used to start checking for overpassing the intersection and set the m_intersectionFlagVD
    int m_sem100mVD = 0;


public:

    VehicleData();
    VehicleData(int id);
    VehicleData(VehicleMainChar veh);
    ~VehicleData();

    void setId(int id);
    int getId();

    void setPos(Coord position);
    Coord getPos();
;
    void setVelocity(double velocity);
    double getVelocity();


    void setAcceleration(double acceleration);
    double getAcceleration();

    void setHeading(double heading);
    double getHeading();

    void setYaw(double yaw);
    double getYaw();

    void setCarLength(double carLength);
    double getCarLength();

    void setCarWidth(double carWidth);
    double getCarWidth();

    void setTime(simtime_t time);
    simtime_t getTime();

    void setIntersectionPoint(std::pair<double, double> intersectionPoint);
    std::pair<double, double> getIntersectionPoint();

    void setDistance2Intersection(double distance);
    double getDistance2Intersection();

    void setIntersectionFlag(int intersFlag);
    int getIntersectionFlag();

    void setTime2Intersection(double time2intersection);
    double getTime2Intersection();

    void  setMinDistance(double distance);
    double getMinDistance();

    void setLeaderFlag(int leaderFlag);
    int getLeaderFlag();

    std::vector<double> getHeadingVector();
    void setHeadingVecElement(double heading);
    double getHeadingElement(double headingElement);
    bool isHeading(std::vector<double> vector, double headingElement);

;



    double getLanePosition();
    void    setLanePosition(double lanePos);

    void setLeaderCounter(int leder);
    int  getLeaderCounter();

    void setHeadingPair(int id, double heading);
    std::vector<std::pair<int, double>> getHeadingPair();




    void setData(int id, Coord position, double velocity, double heading, double yaw, double carLength, double carWidth, simtime_t time);

    //it takes care of the mismatch between the signal from the simulator and the one used into the optimization algorithm.
    // Simulator right = 1 or 9 -> optimizer 2
    // Simulator left = 2 or 10 -> optimizer 1
    void setSignal(int signal);
    void setBeaconSignal(int beaconSignal);
    int getSignal();

    int getSignalXML();
    void setSignalXML(int signalFromXMLMap);


    //Data Timed Functions

    //void cleaner(double time);

    void setAllSeenVehicle(double heading, int id);
    std::map<double, std::vector<int>> getAllSeenVehicle();

    void setVehicleMyDir(double myHeading, double headingBSM, int id);
    std::map<double, std::vector<int>> getVehicleMyDir();

    void setRoadId(std::string roadId);
    std::string getRoadId();

    //Optimization
    void setLeadersMapElement(int leaderId, std::string message);
    std::string getLeadersMapElement(int leaderId);
    std::map<int, std::string> getLeadersMap();
    void clearLeaderMap();
    void eraseLeaderMapElement(int id);
    void setLeadersMap(std::map<int, std::string> leadersMap);


    void setSem100(int sem);
    int getSem100();

    void setBroadcastIdSet(std::string setId);
    std::string getBroadcastIdSet();

    void setOptimized(bool val);
    bool getOptimized();

    void setCrossingIntersection(int value);
    int getCrossingIntersection();

    void setQueuePosition(int i);
    int getQueuePosition();

    void setOptimizationCounter(int i);
    int getOptimizationCounter();

    void setNewOptimBroad(std::string message);
    std::vector<std::string> getAllOptimBroad();
    void setAllOptimBroad(std::vector<std::string> allBroadMessages);
    bool isBroadMessagePresent(std::string message);

};


namespace storage
{
    //{queuePosition, {id, data}}
    std::map<int, std::map<int, VehicleData>> storageVehicleByCircle(std::map<int, VehicleData> m_storage);
    bool optimizationAlreadyHappened(std::map<int, VehicleData> m_storage);
    bool queueBeforeMePassedStop(std::map<int, VehicleData> m_storage, int myId);
    bool queueBeforeMePassedNoStop(std::map<int, VehicleData> m_storage, int myId);
    bool queueBeforeMe(std::map<int, VehicleData> m_storage, int myId);
    std::vector<VehicleData> remainingVehBeforeMe(std::map<int, VehicleData> m_storage, int myId);

    void setIdsInChosenSol(std::vector<std::vector<Car>>& chosenSolution, std::vector<VehicleMainChar> arrivedString);

    bool haveItoStop(std::vector<std::vector<Car>> chosenSol, int myId);
    bool canICross(std::map<int, VehicleData> m_storage, std::vector<std::vector<Car>> chosenSol, int myId);
    bool isCarInVec(std::vector<Car> myVec, Car myCar);
    bool previousOptimizationNotCrossed(std::map<int, VehicleData> m_storage,  int myId);

    bool amIOnlyLeader(std::map<int, VehicleData> storage, int myId);

    void printVectorVector(std::vector<std::vector<Car>> testedSolutions, std::map<int, VehicleData> storage, std::string path = "", std::string type = "");

    bool compareSize(const std::string& a, const std::string b);
}



#endif /* SRC_VEINS_MODULES_APPLICATION_DATA_STRUCTURE_VEHICLEDATA_H */
