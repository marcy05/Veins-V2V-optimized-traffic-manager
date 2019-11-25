/*
 * VehicleData.cpp
 *
 *  Created on Nov 29, 2018
 *      Author: Marcello Sgarbi
 *
 */

#include "VehicleData.h"


VehicleData::VehicleData()
{
    m_idVD = -1;
    m_positionVD = Coord(-1,-1,-1);
    m_sendtimeVD = -1;
    m_velocityVD = -1;
    m_headingVD = -1;
    m_yawVD = -1;
    m_carLengthVD = 0;
    m_carWidthVD = 0;
}

VehicleData::VehicleData(int id)
{
    m_idVD = id;
    m_positionVD = Coord(-1,-1,-1);
    m_sendtimeVD = -1;
    m_velocityVD = -1;
    m_headingVD = -1;
    m_yawVD = -1;
    m_carLengthVD = 0;
    m_carWidthVD = 0;
}

VehicleData::VehicleData(VehicleMainChar veh)
{
    m_idVD = veh.m_id;
    m_headingVD = veh.m_heading;
    m_queuePositionVD = veh.m_queuePosition;
}
VehicleData::~VehicleData()
{

}

void VehicleData::setId(int id) { m_idVD = id; }
int VehicleData::getId() { return m_idVD; }

void VehicleData::setPos(Coord position) { m_positionVD = position; }
Coord VehicleData::getPos() { return m_positionVD; }

simtime_t VehicleData::getTime() { return m_sendtimeVD; }
void VehicleData::setTime(simtime_t time) { m_sendtimeVD = time; }


void VehicleData::setVelocity(double velocity) {m_velocityVD = velocity; }
double VehicleData::getVelocity() { return m_velocityVD; }

void VehicleData::setAcceleration(double acceleration) {
    if(acceleration > -50 && acceleration < 50 ){
        m_accelerationVD = acceleration;
    }
}
double VehicleData::getAcceleration() { return m_accelerationVD; }


void VehicleData::setHeading(double heading) { m_headingVD = heading; }
double VehicleData::getHeading() { return m_headingVD; }

void VehicleData::setYaw(double yaw) { m_yawVD = yaw; }
double VehicleData::getYaw() { return m_yawVD; }

void VehicleData::setCarLength(double carLength) { m_carLengthVD = carLength; }
double VehicleData::getCarLength() { return m_carLengthVD; }

void VehicleData::setCarWidth(double carWidth) { m_carWidthVD = carWidth; }
double VehicleData::getCarWidth() { return m_carWidthVD; }

void VehicleData::setIntersectionPoint(std::pair<double, double> intersectionPoint) { m_intersectionPointVD = intersectionPoint; }
std::pair<double, double> VehicleData::getIntersectionPoint() { return m_intersectionPointVD; }

void VehicleData::setDistance2Intersection(double distance) {
    if(distance > -5000 && distance < 5000){
        m_distance2IntersectionVD = distance;
    }
}
double VehicleData::getDistance2Intersection() { return m_distance2IntersectionVD; }

void VehicleData::setIntersectionFlag(int intersFlag) { m_intersectionFlagVD = intersFlag; }

int VehicleData::getIntersectionFlag() { return m_intersectionFlagVD; }

void VehicleData::setTime2Intersection(double time2intersection) {
    if(m_time2IntersectionVD > -5000 && m_time2IntersectionVD < 5000){
        m_time2IntersectionVD = time2intersection;
    }
}

double VehicleData::getTime2Intersection() {return m_time2IntersectionVD; }

void VehicleData::setMinDistance(double distance) {m_minDistanceVD = distance; }
double VehicleData::getMinDistance() {return m_minDistanceVD; }

void VehicleData::setLeaderFlag(int leaderFlag) {m_leaderFlagVD = leaderFlag; }
int VehicleData::getLeaderFlag() {return m_leaderFlagVD; }

void VehicleData::setLeaderCounter(int leader) {m_leaderCounterVD = leader;}

int VehicleData::getLeaderCounter() {return m_leaderCounterVD; }

void VehicleData::setHeadingVecElement(double heading)
{
    std::vector<double>::iterator it;
    it =find(m_headingVectorVD.begin(), m_headingVectorVD.end(), heading);

    if (it == m_headingVectorVD.end()) { m_headingVectorVD.push_back(heading); }
}

std::vector<double> VehicleData::getHeadingVector() {return m_headingVectorVD;}

double VehicleData::getHeadingElement(double headingElement)
{
    std::vector<double>::iterator it;
    it = find(m_headingVectorVD.begin(), m_headingVectorVD.end(), headingElement);

    if ( it != m_headingVectorVD.end()) { return *it; }
}

bool VehicleData::isHeading(std::vector<double> vector, double headingElement)
{
    std::vector<double>::iterator it;
    it = find(vector.begin(), vector.end(), headingElement);

    if (it != vector.end()) { return true; }
    else{ return false; }
}



std::vector<std::pair<int, double>> VehicleData::getHeadingPair() {return m_headingPairVD;}
void VehicleData::setHeadingPair(int id, double heading)
{

    if(m_headingPairVD.size() == 0)
    {
        m_headingPairVD.push_back(std::make_pair(id, heading));
    }
    else
    {
        std::vector<int> auxVector;
        for(std::vector<std::pair<int, double>>::iterator it = m_headingPairVD.begin(); it != m_headingPairVD.end(); ++it)
        {
            auxVector.push_back(it->first);
        }

        std::vector<int>::iterator vit;
        vit = find(auxVector.begin(), auxVector.end(), id);
        if(vit == auxVector.end())
        {
            m_headingPairVD.push_back(std::make_pair(id, heading));
        }
    }


}

double VehicleData::getLanePosition() {return m_lanePositionVD;}
void   VehicleData::setLanePosition(double lanePos) {m_lanePositionVD = lanePos;}







void    VehicleData::setData(int id, Coord position, double velocity, double heading, double yaw, double carLength, double carWidth, simtime_t time )
{
    m_idVD = id;
    m_positionVD = position;
    m_velocityVD = velocity;


    m_headingVD = heading;
    m_yawVD = yaw;
    m_carLengthVD = carLength;
    m_carWidthVD = carWidth;
    m_sendtimeVD = time;
}

void VehicleData::setSignal(int signal)
{
    //right
    if(signal == 1 || signal == 9){
        m_signalVD = 2;
    }
    //left
    if(signal == 2 || signal == 10){
        m_signalVD = 3;
    }
    if(signal == 111 && (m_signalVD != 2 && m_signalVD != 1)){
        m_signalVD = 4;
    }

}

void VehicleData::setBeaconSignal(int beaconSignal){
    m_signalVD = beaconSignal;
}

int VehicleData::getSignal(){
    return m_signalVD;
}


int VehicleData::getSignalXML()
{
    return m_signalMapXMLVD;
    //storage[id].m_signalMapXML = rxml::VehicleSignals("C:/veins-4.7.1acc_id/examples/veins/Cross_intersection.rou.xml");
}


void VehicleData::setSignalXML(int signalFromXMLMap){
    m_signalMapXMLVD = signalFromXMLMap;
}





void VehicleData::setAllSeenVehicle(double heading, int id)
{
    std::map<double, std::vector<int>>::iterator it = m_allSeenVehicleVD.find(heading);
    if(it == m_allSeenVehicleVD.end())
    {
        std::vector<int> aux = {id};
        m_allSeenVehicleVD[heading] = aux;
    }
    if(it != m_allSeenVehicleVD.end())
    {
        std::vector<int>::iterator sit = std::find(it->second.begin(), it->second.end(), id);
        if(sit == it->second.end()){
            m_allSeenVehicleVD[heading].push_back(id);
        }
    }

    for(std::map<double, std::vector<int>>:: iterator it = m_allSeenVehicleVD.begin(); it != m_allSeenVehicleVD.end(); ++it)
    {
        std::sort(it->second.begin(), it->second.end());
    }

}

std::map<double, std::vector<int>> VehicleData::getAllSeenVehicle()
{
    return m_allSeenVehicleVD;
}



void VehicleData::setVehicleMyDir(double myHeading, double headingBSM, int id)
{
    if(myHeading == headingBSM)
    {
        std::map<double, std::vector<int>>::iterator it = m_seenVehicleMyDirVD.find(headingBSM);
        if(it == m_seenVehicleMyDirVD.end()){
            std::vector<int> aux = {id};
            m_seenVehicleMyDirVD[myHeading] = aux;
        }
        if(it != m_seenVehicleMyDirVD.end()){
            std::vector<int>::iterator sit = std::find(it->second.begin(), it->second.end(), id);
            if(sit == it->second.end()){
                m_seenVehicleMyDirVD[myHeading].push_back(id);
            }
        }
    }

    for(std::map<double, std::vector<int>>::iterator it = m_seenVehicleMyDirVD.begin(); it != m_seenVehicleMyDirVD.end(); ++it)
    {
        std::sort(it->second.begin(), it->second.end());
    }
}

std::map<double, std::vector<int>> VehicleData::getVehicleMyDir()
{
    return m_seenVehicleMyDirVD;
}



void VehicleData::setRoadId(std::string roadId){
    m_roadIdVD = roadId;
}
std::string VehicleData::getRoadId(){
    return m_roadIdVD;
}



void VehicleData::setLeadersMapElement(int leaderId, std::string message)
{

    std::map<int, std::string>::iterator it = m_leadersMap.find(leaderId);
    if(it == m_leadersMap.end() || std::strncmp(it->second.c_str(), "",1) == 0){
        m_leadersMap[leaderId] = message;
    }
}
std::string VehicleData::getLeadersMapElement(int leaderId){

    return m_leadersMap[leaderId];
}

std::map<int, std::string> VehicleData::getLeadersMap(){
    return m_leadersMap;
}


void VehicleData::clearLeaderMap(){
    m_leadersMap = {};
}

void VehicleData::eraseLeaderMapElement(int id){
    std::map<int, std::string>::iterator fit = m_leadersMap.find(id);
    if(fit != m_leadersMap.end()){
        m_leadersMap.erase(fit);
    }
}

void VehicleData::setLeadersMap(std::map<int, std::string> leadersMap){
    m_leadersMap = leadersMap;
}

void VehicleData::setSem100(int sem)
{
    m_sem100mVD = sem;
}

int VehicleData::getSem100(){
    return m_sem100mVD;
}

void VehicleData::setBroadcastIdSet(std::string setId)
{
    if(setId.size() > 0 ){
        m_broadcastIdSet = setId;
    }
}

std::string VehicleData::getBroadcastIdSet()
{
    return m_broadcastIdSet;
}

void VehicleData::setOptimized(bool val){
    m_optimized = val;
}
bool VehicleData::getOptimized(){
    return m_optimized;
}

void VehicleData::setCrossingIntersection(int value){
    m_crossingIntersection = value;
}
int VehicleData::getCrossingIntersection(){
    return m_crossingIntersection;
}


void VehicleData::setQueuePosition(int i){
    m_queuePositionVD = i;
}

int VehicleData::getQueuePosition(){
    return m_queuePositionVD;
}

void VehicleData::setOptimizationCounter(int i){
    m_optimizationCouterVD = i;
}

int VehicleData::getOptimizationCounter(){
    return m_optimizationCouterVD;
}


void VehicleData::setNewOptimBroad(std::string message)
{
    if(isBroadMessagePresent(message) == false && message.size()>0){
        m_allOptimizBroadReceived.push_back(message);
    }
}

void VehicleData::setAllOptimBroad(std::vector<std::string> allBroadMessages)
{
    m_allOptimizBroadReceived = allBroadMessages;
}

std::vector<std::string> VehicleData::getAllOptimBroad(){
    return m_allOptimizBroadReceived;
}

bool VehicleData::isBroadMessagePresent(std::string message)
{
    std::vector<std::string>::iterator fit = std::find(m_allOptimizBroadReceived.begin(), m_allOptimizBroadReceived.end(), message);
    if(fit != m_allOptimizBroadReceived.end()){
        return true;
    }
    return false;
}







std::map<int, std::map<int, VehicleData>> storage::storageVehicleByCircle(std::map<int, VehicleData> m_storage)
{
    std::map<int, std::map<int, VehicleData>> VehByCircleVD;
    std::map<double, int> eDistances, nDistances, wDistances, sDistances;
    for (std::map<int, VehicleData>::iterator it = m_storage.begin(); it != m_storage.end(); ++it)
    {
        if (carUtility::checkHeading(it->second.getHeading()) == 1) {
            eDistances[it->second.getDistance2Intersection()] = it->second.getId();
        }
        if (carUtility::checkHeading(it->second.getHeading()) == 2) {
            nDistances[it->second.getDistance2Intersection()] = it->second.getId();
        }
        if (carUtility::checkHeading(it->second.getHeading()) == 3) {
            wDistances[it->second.getDistance2Intersection()] = it->second.getId();
        }
        if (carUtility::checkHeading(it->second.getHeading()) == 4) {
            sDistances[it->second.getDistance2Intersection()] = it->second.getId();
        }

    }



    int eCounter = 1, nCounter = 1, wCounter = 1, sCounter = 1;


    for (std::map<double, int>::iterator it = eDistances.begin(); it != eDistances.end(); ++it)
    {
        for (std::map<int, VehicleData>::iterator sit = m_storage.begin(); sit != m_storage.end(); ++sit)
        {
            if (it->first == sit->second.getDistance2Intersection() && it->second == sit->second.getId()) {

                if (VehByCircleVD.find(sit->second.getQueuePosition()) == VehByCircleVD.end()) {
                    std::map<int, VehicleData> aux;

                    if (VehByCircleVD.find(eCounter) == VehByCircleVD.end()) {
                        aux[sit->first] = sit->second;
                        VehByCircleVD[eCounter] = aux;
                    }
                    else {
                        aux = VehByCircleVD.at(eCounter);
                        aux[sit->first] = sit->second;
                        VehByCircleVD[eCounter] = aux;
                    }
                }
                else {
                    std::map<int, VehicleData> aux = VehByCircleVD[sit->second.getQueuePosition()];
                    if (aux.find(sit->first) == aux.end()) {
                        aux[sit->first] = sit->second;
                        VehByCircleVD[eCounter] = aux;
                    }

                }
                break;
            }
        }
        eCounter += 1;
    }

    for (std::map<double, int>::iterator it = nDistances.begin(); it != nDistances.end(); ++it)
    {
        for (std::map<int, VehicleData>::iterator sit = m_storage.begin(); sit != m_storage.end(); ++sit)
        {
            if (it->first == sit->second.getDistance2Intersection() && it->second == sit->second.getId()) {

                if (VehByCircleVD.find(nCounter) == VehByCircleVD.end()) {
                    std::map<int, VehicleData> aux;

                    if (VehByCircleVD.find(nCounter) == VehByCircleVD.end()) {
                        aux[sit->first] = sit->second;
                        VehByCircleVD[nCounter] = aux;
                    }
                    else {
                        aux = VehByCircleVD.at(nCounter);
                        aux[sit->first] = sit->second;
                        VehByCircleVD[nCounter] = aux;
                    }
                }
                else {
                    std::map<int, VehicleData> aux = VehByCircleVD[nCounter];
                    if (aux.find(sit->first) == aux.end()) {
                        aux[sit->first] = sit->second;
                        VehByCircleVD[nCounter] = aux;
                    }

                }
                continue;
            }
        }
        nCounter += 1;
    }

    for (std::map<double, int>::iterator it = wDistances.begin(); it != wDistances.end(); ++it)
    {
        for (std::map<int, VehicleData>::iterator sit = m_storage.begin(); sit != m_storage.end(); ++sit)
        {
            if (it->first == sit->second.getDistance2Intersection() && it->second == sit->second.getId()) {

                if (VehByCircleVD.find(wCounter) == VehByCircleVD.end()) {
                    std::map<int, VehicleData> aux;

                    if (VehByCircleVD.find(wCounter) == VehByCircleVD.end()) {
                        aux[sit->first] = sit->second;
                        VehByCircleVD[wCounter] = aux;
                    }
                    else {
                        aux = VehByCircleVD.at(wCounter);
                        aux[sit->first] = sit->second;
                        VehByCircleVD[wCounter] = aux;
                    }
                }
                else {
                    std::map<int, VehicleData> aux = VehByCircleVD[wCounter];
                    if (aux.find(sit->first) == aux.end()) {
                        aux[sit->first] = sit->second;
                        VehByCircleVD[wCounter] = aux;
                    }

                }
                continue;
            }
        }
        wCounter += 1;
    }

    for (std::map<double, int>::iterator it = sDistances.begin(); it != sDistances.end(); ++it)
    {
        for (std::map<int, VehicleData>::iterator sit = m_storage.begin(); sit != m_storage.end(); ++sit)
        {
            if (it->first == sit->second.getDistance2Intersection() && it->second == sit->second.getId()) {

                if (VehByCircleVD.find(sCounter) == VehByCircleVD.end()) {
                    std::map<int, VehicleData> aux;

                    if (VehByCircleVD.find(sCounter) == VehByCircleVD.end()) {
                        aux[sit->first] = sit->second;
                        VehByCircleVD[sCounter] = aux;
                    }
                    else {
                        aux = VehByCircleVD.at(sCounter);
                        aux[sit->first] = sit->second;
                        VehByCircleVD[sCounter] = aux;
                    }
                }
                else {
                    std::map<int, VehicleData> aux = VehByCircleVD[sCounter];
                    if (aux.find(sit->first) == aux.end()) {
                        aux[sit->first] = sit->second;
                        VehByCircleVD[sCounter] = aux;
                    }

                }
                continue;
            }
        }
        sCounter += 1;
    }

    return VehByCircleVD;
}




bool storage::optimizationAlreadyHappened(std::map<int, VehicleData> m_storage)
{
    for(std::map<int, VehicleData>::iterator it = m_storage.begin(); it != m_storage.end(); ++it)
    {
        if(it->second.getOptimized() != false ){
            return true;
        }
    }
    return false;
}

bool storage::queueBeforeMePassedStop(std::map<int, VehicleData> m_storage, int myId)
{
    std::map<int, std::map<int, VehicleData>> storageByCircle = storage::storageVehicleByCircle(m_storage);

    int myQueue = m_storage[myId].getQueuePosition();
    int myOptimCount = m_storage[myId].getOptimizationCounter();

    std::vector<VehicleData> vehBeforeMe = {};
    for(std::map<int, std::map<int, VehicleData>>::reverse_iterator it = storageByCircle.rbegin();  it != storageByCircle.rend(); ++it)
    {
        if(it->first <= myQueue)
        {
            for(std::map<int, VehicleData>::iterator sit = it->second.begin(); sit != it->second.end(); ++sit)
            {
                if(sit->second.getOptimizationCounter() <= myOptimCount && sit->second.getIntersectionFlag() != 1 && sit->second.getId() != myId)
                {
                    vehBeforeMe.push_back(sit->second);
                }
            }
        }
    }

    if(vehBeforeMe.size() == 0){
        std::cout << "vehicle: " << myId << " can restart" << std::endl;
        return true;
    }
    if(vehBeforeMe.size() > 0){
        std::cout << "vehicle: " << myId << "stopped by: " << std::endl;
        for(std::vector<VehicleData>::iterator it = vehBeforeMe.begin(); it != vehBeforeMe.end(); ++it)
        {
            std::cout << "\tid: " << it->getId() << std::endl;
        }
    }
    return false;
}

bool storage::queueBeforeMePassedNoStop(std::map<int, VehicleData> m_storage, int myId)
{
    std::map<int, std::map<int, VehicleData>> storageByCircle = storage::storageVehicleByCircle(m_storage);

    int myQueue = m_storage[myId].getQueuePosition();
    int myOptimCount = m_storage[myId].getOptimizationCounter();

    std::vector<VehicleData> vehBeforeMe = {};

    for(std::map<int, std::map<int, VehicleData>>::reverse_iterator it = storageByCircle.rbegin();  it != storageByCircle.rend(); ++it)
    {
        if(std::next(it) != storageByCircle.rend())
        {
            std::map<int, std::map<int, VehicleData>>::reverse_iterator nexIt = next(it);
            if(nexIt->first < myQueue)
            {
                for(std::map<int, VehicleData>::iterator sit = nexIt->second.begin(); sit != nexIt->second.end(); ++sit)
                {
                    if(sit->second.getOptimizationCounter() <= myOptimCount && sit->second.getIntersectionFlag() != 1 && sit->second.getId() != myId)
                    {
                        vehBeforeMe.push_back(sit->second);
                    }
                }
            }
        }
    }

    if(vehBeforeMe.size() == 0){
        std::cout << "vehicle: " << myId << " free to pass" << std::endl;
        return true;
    }

    std::cout << "vehicle: " << myId << "blocked by: " << std::endl;
    for(std::vector<VehicleData>::iterator it = vehBeforeMe.begin(); it != vehBeforeMe.end(); ++it)
    {
        std::cout << "\tid: " << it->getId() << std::endl;
    }
    return false;
}


//return true if a vehicle has vehicles of previous queue in which have to pass before it
bool storage::queueBeforeMe(std::map<int, VehicleData> m_storage, int myId)
{

    std::vector<VehicleData> blockingVeh = {};
    int myQueue = m_storage[myId].getQueuePosition();
    int myOptimCount = m_storage[myId].getOptimizationCounter();
    for(std::map<int, VehicleData>::reverse_iterator it = m_storage.rbegin(); it != m_storage.rend(); ++it)
    {
        if(myOptimCount == it->second.getOptimizationCounter() && myQueue > it->second.getQueuePosition()){
            if(it->second.getIntersectionFlag() == 0){
                blockingVeh.push_back(it->second);
            }
        }
    }

    if(blockingVeh.size() > 0){
        return true;
    }

    return false;
}


std::vector<VehicleData> storage::remainingVehBeforeMe(std::map<int, VehicleData> m_storage, int myId)
{
    std::vector<VehicleData> blockingVeh = {};
    int myQueue = m_storage[myId].getQueuePosition();
    int myOptimCount = m_storage[myId].getOptimizationCounter();
    for(std::map<int, VehicleData>::reverse_iterator it = m_storage.rbegin(); it != m_storage.rend(); ++it)
    {
        if(myOptimCount == it->second.getOptimizationCounter() && myQueue > it->second.getQueuePosition()){
            if(it->second.getIntersectionFlag() == 0){
                blockingVeh.push_back(it->second);
            }
        }
    }




    return blockingVeh;
}



void storage::setIdsInChosenSol(std::vector<std::vector<Car>>& chosenSolution, std::vector<VehicleMainChar> arrivedString)
{
    for(std::vector<std::vector<Car>>::iterator it = chosenSolution.begin(); it != chosenSolution.end(); ++it)
    {
        for(std::vector<VehicleMainChar>::iterator sit=arrivedString.begin(); sit != arrivedString.end(); ++sit)
        {
            if(carUtility::checkHeading(sit->m_heading) == 1)
            {
                if(it->at(0).getQueuePosition() == sit->m_queuePosition){
                    it->at(0).setId(sit->m_id);
                }
            }
            if(carUtility::checkHeading(sit->m_heading) == 2)
            {
                if(it->at(1).getQueuePosition() == sit->m_queuePosition){
                    it->at(1).setId(sit->m_id);
                }
            }
            if(carUtility::checkHeading(sit->m_heading) == 3)
            {
                if(it->at(2).getQueuePosition() == sit->m_queuePosition){
                    it->at(2).setId(sit->m_id);
                }
            }
            if(carUtility::checkHeading(sit->m_heading) == 4)
            {
                if(it->at(3).getQueuePosition() == sit->m_queuePosition){
                    it->at(3).setId(sit->m_id);
                }
            }
        }
    }



    //{direction, startPositionIterator}
    std::map<int, std::vector<std::vector<Car>>::iterator> setMinusOne = {};
    for(std::vector<std::vector<Car>>::iterator it = chosenSolution.begin(); it != chosenSolution.end(); ++it)
    {
        std::vector<std::vector<Car>>::iterator nit = std::next(it);
        if(nit != chosenSolution.end())
        {
            if(nit->at(0).getQueuePosition() < it->at(0).getQueuePosition()){
                setMinusOne[0] = nit;
            }
            if(nit->at(1).getQueuePosition() < it->at(1).getQueuePosition()){
                setMinusOne[1] = nit;
            }
            if(nit->at(2).getQueuePosition() < it->at(2).getQueuePosition()){
                setMinusOne[2] = nit;
            }
            if(nit->at(3).getQueuePosition() < it->at(3).getQueuePosition()){
                setMinusOne[3] = nit;
            }
        }
    }

    std::map<int, int> minusDistances = {};
    for(std::map<int, std::vector<std::vector<Car>>::iterator>::iterator it = setMinusOne.begin(); it != setMinusOne.end(); ++it)
    {
        minusDistances[it->first] = std::distance(chosenSolution.begin(), it->second);
    }

    for(std::map<int, int>::iterator it = minusDistances.begin(); it != minusDistances.end(); ++it)
    {
        for(std::vector<std::vector<Car>>::iterator sit = chosenSolution.begin(); sit != chosenSolution.end(); ++sit)
        {
            if(std::distance(chosenSolution.begin(), sit) >= it->second){
                sit->at(it->first).setId(-1);
            }
        }
    }

}




// returns true if the optimization algorithm had assign to the vehicle the stop command
bool storage::haveItoStop(std::vector<std::vector<Car>> chosenSol, int myId)
{
    for(std::vector<std::vector<Car>>::iterator it = chosenSol.begin(); it != chosenSol.end(); ++it){
        for(std::vector<Car>::iterator sit = it->begin(); sit != it->end(); ++sit)
        {
            if(sit->getId() == myId && sit->getSignal() == 1){
                return true;
            }
        }
    }

    return false;
}



//return true if all vehicles in my queue position, which does not have to stop, crossed the intersection

bool storage::canICross(std::map<int, VehicleData> m_storage, std::vector<std::vector<Car>> chosenSol, int myId)
{
    int exiting = 0;
    std::vector<Car> vehicleBeforeMe = {};
    std::vector<std::vector<Car>>::iterator position = chosenSol.end();

    //When it is found the signal for the considered vehicle which is not ==1, the position is saved
    for(std::vector<std::vector<Car>>::iterator it = chosenSol.begin(); it != chosenSol.end(); ++it)
    {
        for(std::vector<Car>::iterator sit = it->begin(); sit != it->end(); ++sit)
        {
            if(sit->getId() == myId && sit->getSignal() != 1){
                position = it;
                exiting = 1;
                break;
            }
        }
        if(exiting == 1){ break; }
    }


    std::cout << "\t\tPosition identified" << std::endl;
    if(position == chosenSol.begin()){
        std::cout << "\t\tamong firsts vehicles" << std::endl;
        return true;
    }
    else{
        for(std::vector<std::vector<Car>>::iterator it = chosenSol.begin(); it != chosenSol.end(); ++it)
        {
            if(it < position)
            {
                for(std::vector<Car>::iterator sit = it->begin(); sit != it->end(); ++sit)
                {
                    if(sit->getSignal() != 1){
                        carUtility::addUniqueCarInVector(vehicleBeforeMe, *sit);
                        std::cout << "\t\tvector filled" << std::endl;
                    }
                }
            }
        }

        //
        for(std::vector<Car>::iterator it = vehicleBeforeMe.begin(); it != vehicleBeforeMe.end(); ++it)
        {
            std::map<int, VehicleData>::iterator fit = m_storage.find(it->getId());
            if(fit != m_storage.end())
            {
                std::cout << "\t\t\tid: " << it->getId() << " founded in the storage" << std::endl;
                if(m_storage[it->getId()].getIntersectionFlag() != 1){
                    std::cout << "\t\t\tblocking vehicle id: " << it->getId() << " founded in the storage" << std::endl;
                    return false;
                }
            }
        }
        return true;
    }

}



bool storage::isCarInVec(std::vector<Car> myVec, Car myCar)
{
    for(std::vector<Car>::iterator it = myVec.begin(); it != myVec.end(); ++it){
        if(myCar.getId() == it->getId()){
            return true;
        }
    }
    return false;
}


bool storage::previousOptimizationNotCrossed(std::map<int, VehicleData> m_storage, int myId)
{
    int myOptimCount = m_storage[myId].getOptimizationCounter();


    for(std::map<int, VehicleData>::iterator it = m_storage.begin(); it != m_storage.end(); ++it)
    {
        if(it->second.getOptimizationCounter() < myOptimCount && it->second.getOptimized() == 1 && it->second.getIntersectionFlag() != 1)
        {
            return true;
        }
    }
    return false;
}



bool storage::amIOnlyLeader(std::map<int, VehicleData> storage, int myId)
{
    bool outVal = false;
    if(storage.find(myId) == storage.end() ||  myId != storage[myId].getLeaderFlag())
    {
        return false;
    }
    if(myId == storage[myId].getLeaderFlag())
    {
        for(std::map<int, VehicleData>::iterator it = storage.begin(); it != storage.end(); ++it)
        {
            if(it->second.getLeaderFlag() != myId && it->second.getIntersectionFlag() == 1){
                outVal = true;
            }
            if(it->second.getLeaderFlag() != myId && it->second.getIntersectionFlag() == 0){
                outVal = false;
            }
        }
    }


    return outVal;
}


void storage::printVectorVector(std::vector<std::vector<Car>> testedSolutions, std::map<int, VehicleData> storage, std::string path, std::string type)
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
            myfile << "      E          N            W           S" << std::endl;
            for (std::vector<std::vector<Car>>::iterator it = testedSolutions.begin(); it != testedSolutions.end(); ++it)
            {
                for (std::vector<Car>::iterator sit = it->begin(); sit != it->end(); ++sit)
                {
                    if(sit->getId() != -1){
                        myfile << "{" << sit->getId() << "," << sit->getQueuePosition() << "," << storage[sit->getId()].getSignal() << ",";
                        if(sit->getSignal() == 1){
                            myfile << sit->getSignal() << " stop}";
                        }
                        else{
                            myfile << sit->getSignal() << " go}";
                        }
                    }
                    if(sit->getId() == -1){
                        myfile << "{             }" ;
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


bool storage::compareSize(const std::string& a, const std::string b)
{
    return (a.size()<b.size());
}
