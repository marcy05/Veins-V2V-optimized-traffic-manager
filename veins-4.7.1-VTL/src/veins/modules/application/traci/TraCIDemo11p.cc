//
// Copyright (C) 2006-2011 Christoph Sommer <christoph.sommer@uibk.ac.at>
//
// Documentation for these modules is at http://veins.car2x.org/
//
// This program is free software; you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation; either version 2 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program; if not, write to the Free Software
// Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//

#include <veins/modules/application/traci/TraCIDemo11p.h>
#include <iomanip>

Define_Module(TraCIDemo11p);

void TraCIDemo11p::initialize(int stage) {
    BaseWaveApplLayer::initialize(stage);
    if (stage == 0) {
        sentMessage = false;
        lastDroveAt = simTime();
        currentSubscribedServiceId = -1;
    }
    //std::map<int, int> signalFromXML = rxml::vehicleSignals("C:/veins-4.7.1acc_id/examples/veins/Cross_intersection.rou.xml");
    //std::map<int, int>::iterator fit = signalFromXML.find(std::stoi(mobility->getExternalId()));
    //m_storage[std::stoi(mobility->getExternalId())].setSignalXML(fit->second);

    //Initialize the variable containing all the possible solutions for the xml

    if(initsem == 0){
         clock_t time = clock();
        mapDataset = rxml::readfileXMLSignals("C:/veins-4.7.1acc_id/src/veins/modules/application/optimization/OutputXML4Signal.xml");
        initsem = 1;
        std::cout << "Vehicle: " << mobility->getExternalId() << " load in: " << (clock() - time) / ((clock_t)1) << "ms" << std::endl;
    }


}

void TraCIDemo11p::onWSA(WaveServiceAdvertisment* wsa) {
    if (currentSubscribedServiceId == -1) {
        mac->changeServiceChannel(wsa->getTargetChannel());
        currentSubscribedServiceId = wsa->getPsid();
        if  (currentOfferedServiceId != wsa->getPsid()) {
            stopService();
            startService((Channels::ChannelNumber) wsa->getTargetChannel(), wsa->getPsid(), "Mirrored Traffic Service");
        }
    }
}

void TraCIDemo11p::onWSM(WaveShortMessage* wsm) {
    //findHost()->getDisplayString().updateWith("r=16,green");

    if (mobility->getRoadId()[0] != ':') traciVehicle->changeRoute(wsm->getWsmData(), 9999);
    if (!sentMessage) {
        sentMessage = true;
        //repeat the received traffic update once in 2 seconds plus some random delay
        wsm->setSenderAddress(myId);
        wsm->setSerial(3);
        scheduleAt(simTime() + 2 + uniform(0.01,0.2), wsm->dup());
    }
}

void TraCIDemo11p::handleSelfMsg(cMessage* msg) {
    if (WaveShortMessage* wsm = dynamic_cast<WaveShortMessage*>(msg)) {
        //send this message on the service channel until the counter is 3 or higher.
        //this code only runs when channel switching is enabled
        sendDown(wsm->dup());
        wsm->setSerial(wsm->getSerial() +1);
        if (wsm->getSerial() >= 3) {
            //stop service advertisements
            stopService();
            delete(wsm);
        }
        else {
            scheduleAt(simTime()+1, wsm);
        }
    }
    else {
        BaseWaveApplLayer::handleSelfMsg(msg);
    }
}

void TraCIDemo11p::handlePositionUpdate(cObject* obj) {
    BaseWaveApplLayer::handlePositionUpdate(obj);
}


void TraCIDemo11p::onBeacon(BasicSafetyMessage* bsm)
{
    if(simTime().dbl() > 5)
    {
        std::cout << "Vehicle: " << mobility->getExternalId() << " receiving" << std::endl;
        m_beaconReceived++;

        updateMyData();         //1) compute the acceleration and update my data


        updateStorage(bsm);     //2) update the storage
        std::cout << "\tUpdate received data executed" << std::endl;

        computeIntersection(std::stoi(mobility->getExternalId()));
        std::cout << "\tCompute intersection executed" << std::endl;
        wrtIntersection();      //3) Distance2Intersection, IntersectionFlag(if I already pass the intersection), Time2Intersection (Each vehicle compute its data, does not send them to other vehicles)
        std::cout << "\twrtIntersection executed" << std::endl;

        leader();
        std::cout << "\tleader executed" << std::endl;

        //manageSeenVehicles(bsm);
        //std::cout << "\tmanageSeenVehicles executed" << std::endl;

        //if I am the leader
        if(m_storage[std::stoi(mobility->getExternalId())].getLeaderFlag() == std::stoi(mobility->getExternalId())){
            // If my position is over a threshold
            if(m_storage[std::stoi(mobility->getExternalId())].getLanePosition() >= 984){
                prepareLeaderData();
            }
        }
        //
        std::cout << "\tprepareLeaderData executed" << std::endl;


        speedManaging();

        std::cout << "\tspeedManaging executed" << std::endl;
        std::string to_print = "VEHICLE STORAGE: " + mobility->getExternalId();
        wrt::w2Storage(to_print, std::stoi(mobility->getExternalId()));
        wrt::printStorage(m_storage, m_storagePath, std::stoi(mobility->getExternalId()), std::stoi(mobility->getExternalId()));
        /*
        std::string to_printCSV = "VEHICLE STORAGE," + mobility->getExternalId();
        wrt::w2Storage(to_printCSV, "csv");
        wrt::printStorage(m_storage, m_storagePathCSV, std::stoi(mobility->getExternalId()), "csv");
        */


    }



}

void TraCIDemo11p::updateMyData()
{
        //allow to update the m_storage data with the current information

        int id = std::stoi(mobility->getExternalId());
        Coord position = mobility->getCurrentPosition();
        double speed = traciVehicle->getSpeed();
        double heading = static_cast<double>(static_cast<int>(mobility->getAngleRad()*100))/100;
        double yaw = 0;
        double length = traciVehicle->getLength();
        double width = 0;
        simtime_t time = simTime();
        double timeDouble = time.dbl();
        double lanePosition = traciVehicle->getLanePosition(); // Position of the vehicle in sumo street
        double acceleration = mobility->getAcceleration();

        if(id != -1)
        {
            //before update the road id check if I'm crossing the intersection or not
            if(m_storage[id].getRoadId() != traciVehicle->getRoadId()){
                m_storage[id].setCrossingIntersection(1);
            }

            std::string roadId = traciVehicle->getRoadId();
            if(m_storage[id].getRoadId()[0] == ':' && traciVehicle->getRoadId()[0] != ':')
            {
                m_storage[id].setIntersectionFlag(1);
            }
            /*
            if(roadId[0] == ':'){
                roadId = "intersection";
            }*/

            //Get the acceleration for the new method inserted in TraCIMobility
            m_storage[id].setAcceleration(acceleration);
            m_storage[id].setData(id, position, speed, heading, yaw, length, width, time);
            m_storage[id].setLanePosition(lanePosition);
            m_storage[id].setRoadId(roadId);


            //Set straight if
            if(traciVehicle->getSignal() == 0 )
            {
                m_storage[id].setSignal(111);
            }
            else{
                m_storage[id].setSignal(traciVehicle->getSignal());
            }

        }
        //search and delate -1 vehicle
        std::map<int, VehicleData>::iterator fit = m_storage.find(-1);
        if(fit != m_storage.end()){
            m_storage.erase(fit);
        }

        std::cout << "\tUpdate my data executed" << std::endl;
}



void TraCIDemo11p::leaderCheckOptimization(BasicSafetyMessage* bsm)
{
    //std::string path = "C:/workspace_veins-4.7.1acc_id/log/recap" + mobility->getExternalId() + ".xml";
    std::string path = "E:/log/recap" + mobility->getExternalId() + ".xml";
    std::ofstream log(path, std::ios::app);
    //If I am the leader
    if(m_storage[std::stoi(mobility->getExternalId())].getLeaderFlag() == std::stoi(mobility->getExternalId()))
    {
        if(storage::amIOnlyLeader(m_storage, std::stoi(mobility->getExternalId())) == false)
        {
            std::string leaderSringReceived = bsm->getLeaderStringBSM();
            //If I receive a non-null from other leaders
            if(std::strncmp(leaderSringReceived.c_str(), "", 1) != 0)
            {
                log << "received a message from " << bsm->getNodeIDBSM() << " S:" << leaderSringReceived << std::endl;
                //std::map<int, std::string> leaderMap = m_storage[std::stoi(mobility->getExternalId())].getLeadersMap();

                //leaderMap[bsm->getNodeIDBSM()] = bsm->getLeaderStringBSM();


                //m_storage[std::stoi(mobility->getExternalId())].setLeadersMap(leaderMap);
                if(isMyIdInString(leaderSringReceived, std::stoi(mobility->getExternalId())))
                {
                    log << "  I'm in the received leader message" << std::endl;
                    m_storage[std::stoi(mobility->getExternalId())].setLeadersMapElement(bsm->getNodeIDBSM(), leaderSringReceived);
                    leaderReceiving();

                    //Print recap

                    std::map<int, std::string> leadersMap = m_storage[std::stoi(mobility->getExternalId())].getLeadersMap();
                    log << "Mapped leaders messages received" << std::endl;
                    for(std::map<int, std::string>::iterator it = leadersMap.begin(); it != leadersMap.end(); ++it)
                    {
                        log << "id: " << it->first << " Str: " << it->second << std::endl;
                    }
                }
                else{
                    log << "I'm not in the received leader message" << std::endl;
                }

             }
        }
        if(storage::amIOnlyLeader(m_storage, std::stoi(mobility->getExternalId())) == true)
        {
            std::string myLeaderString = m_storage[std::stoi(mobility->getExternalId())].getLeadersMapElement(std::stoi(mobility->getExternalId()));
            m_storage[std::stoi(mobility->getExternalId())].setLeadersMapElement(std::stoi(mobility->getExternalId()), myLeaderString);
            leaderReceiving();
        }


        log.close();

    }
}



void TraCIDemo11p::allVehicleCheckOptimization(BasicSafetyMessage* bsm)
{
    //std::string pathRecap = "C:/workspace_veins-4.7.1acc_id/log/recap" + mobility->getExternalId() + ".xml";
    std::string pathRecap = "E:/log/recap" + mobility->getExternalId() + ".xml";
    //std::string path3 = "C:/workspace_veins-4.7.1acc_id/log/Optimization" + mobility->getExternalId() + ".xml";
    std::string path3 = "E:/log/Optimization" + mobility->getExternalId() + ".xml";
    std::ofstream outfile(pathRecap, std::ios::app);

    std::string receivedStringFlag = bsm->getStringFlagBSM();

    bool aloneFlag = false;
    int consId = std::stoi(mobility->getExternalId());

    std::string myLeaderString = m_storage[consId].getLeadersMapElement(consId);

    if(m_storage[consId].getLeaderFlag() == consId && m_storage[consId].getVelocity() < 0.5 && m_storage[consId].getLeadersMap().size() == 1 && m_storage[consId].getOptimized() == false)
    {
        for(std::map<int, VehicleData>::iterator it = m_storage.begin(); it != m_storage.end(); ++it){
            if(it->second.getIntersectionFlag() == 1){
                aloneFlag = true;
            }
            else{
                aloneFlag = false;
                break;
            }
        }

    }



    //If a new broadcast message arrive means that new leaders are been elected and I have to be sure to have all intersection fleg of brevious iteration = 1
    // can happen that I did't received messages to set the intersection flag
    //ottengo tutti i messaggi delle ottimizzazioni precedenti e setto l'intersection flag = 1!

    if(m_storage[nodeID].getAllOptimBroad().size() > 1  && m_storage[nodeID].isBroadMessagePresent(receivedStringFlag) == false)
    {
        std::cout << "\n\tIn the storage there is a message and I received a new message" << std::endl;
        std::vector<std::string> consideredVector = m_storage[nodeID].getAllOptimBroad();
        std::cout << "\textract messages" << std::endl;
        for(std::vector<std::string>::iterator it = consideredVector.begin(); it != consideredVector.end(); ++it)
        {
            std::cout << "i-th string" << std::endl;
            std::vector<VehicleMainChar> extractedVehicles = bitString2vmc(*it);
            for(std::vector<VehicleMainChar>::iterator sit = extractedVehicles.begin(); sit != extractedVehicles.end(); ++sit){
                std::map<int, VehicleData>::iterator fit = m_storage.find(sit->m_id);
                std::cout << "\tsearch for vehicle " << sit->m_id << std::endl;
                if(fit != m_storage.end()){
                    std::cout << "\tvehicle " << fit->first << " found\n\tCheck for intersection flag" << std::endl;
                    if(fit->second.getIntersectionFlag() != 1 && (m_storage[nodeID].getTime().dbl() - fit->second.getTime().dbl()) > 15  ){
                        std::cout << "\nINTERSECTION FLAG NOT ALREADY SETTED, SETTING..." << std::endl;
                        outfile << "\n\nSETTING INTERSECTION FLAG FOR VEHICLE: " << fit->first << std::endl;
                        fit->second.setIntersectionFlag(1);
                        std::cout << "SET" << std::endl;
                        outfile << "SETTED" << std::endl;
                    }
                    else{
                        std::cout << "intersection flag already set" << std::endl;
                    }
                }
            }
        }
    }










    //setting the string for all vehicle in the storage
    //Research of the maxSize vector containing all the receiving message, before assign the new one. Used in the iteration for new vehicles
    int dimension = 0;
    std::vector<std::string> biggestVector = {};
    for(std::map<int, VehicleData>::iterator it = m_storage.begin(); it != m_storage.end(); ++it)
    {
        std::vector<std::string> consideredVector = it->second.getAllOptimBroad();
        if(consideredVector.size() > dimension){
            dimension = consideredVector.size();
            biggestVector = consideredVector;
        }
    }



    //Set the message to vehicles already present in the storage
    for(std::map<int, VehicleData>::iterator it = m_storage.begin(); it != m_storage.end(); ++it) {
        if(it->second.getAllOptimBroad().size() == 0){
            it->second.setAllOptimBroad(biggestVector);
        }
        it->second.setNewOptimBroad(receivedStringFlag);
    }






    //if the received message is not empty and I'm not already optimized

    //Set the received message to be rebroadcast
    if(receivedStringFlag.size()>0){
        m_storage[std::stoi(mobility->getExternalId())].setBroadcastIdSet(receivedStringFlag);
    }


    if((std::strncmp(receivedStringFlag.c_str(), "",1) != 0 &&  m_storage[std::stoi(mobility->getExternalId())].getOptimized() == false) || aloneFlag == true)
    {

        std::vector<VehicleMainChar> vecReceivedString = bitString2vmc(receivedStringFlag);

        //----------------------------------------------------------------- ALONE START ----------------------------------------------------------------------------------
        if(aloneFlag == true){

            vecReceivedString = bitString2vmc(myLeaderString);
        }
        //----------------------------------------------------------------- ALONE END -------------------------------------------------------------------------------------



        //Setting optimization counter

        //setting the string for all vehicle in the storage
        //Research of the maxSize vector containing all the receiving message, before assign the new one. Used in the iteration for new vehicles
        //------------------------------- research for new vehicles Start --------------------------------------------------------------------
        /*int dimension = 0;
        std::vector<std::string> biggestVector = {};
        for(std::map<int, VehicleData>::iterator it = m_storage.begin(); it != m_storage.end(); ++it)
        {
            std::vector<std::string> consideredVector = it->second.getAllOptimBroad();
            if(consideredVector.size() > dimension){
                dimension = consideredVector.size();
                biggestVector = consideredVector;
            }
        }*/
        //------------------------------- research for new vehicles End --------------------------------------------------------------------


        //Set the message to vehicles already present in the storage
        /*for(std::map<int, VehicleData>::iterator it = m_storage.begin(); it != m_storage.end(); ++it) {
            if(it->second.getAllOptimBroad().size() == 0){
                it->second.setAllOptimBroad(biggestVector);
            }
            it->second.setNewOptimBroad(receivedStringFlag);
        }*/

        //Set the message to vehicles which are not already present in the storage
        for(std::vector<VehicleMainChar>::iterator it = vecReceivedString.begin(); it != vecReceivedString.end(); ++it) {
            std::map<int, VehicleData>::iterator fit = m_storage.find(it->m_id);
            if(fit == m_storage.end())
            {
                //I have a new vehicle, before setting the new message, I set the previous one.
                m_storage[it->m_id].setAllOptimBroad(biggestVector);
                m_storage[it->m_id].setNewOptimBroad(receivedStringFlag);
                m_storage[it->m_id].setTime(simTime());
            }
            else{ fit->second.setNewOptimBroad(receivedStringFlag); }
        }
        //Incrementing the counter
        for(std::map<int, VehicleData>::iterator it = m_storage.begin(); it != m_storage.end(); ++it)
        {
            if(it->second.getOptimizationCounter() == 0){
                std::vector<std::string> ithBroadVector = it->second.getAllOptimBroad();
                for(std::vector<std::string>::iterator sit = ithBroadVector.begin(); sit != ithBroadVector.end(); ++sit)
                {
                    if(isMyIdInString(*sit, it->first) == true && it->second.getOptimizationCounter() == 0){
                        it->second.setOptimizationCounter(ithBroadVector.size());
                    }
                }
            }
        }

        /*for(std::map<int, VehicleData>::iterator it = m_storage.begin(); it != m_storage.end(); ++it)
        {
            if(it->second.isBroadMessagePresent(receivedStringFlag) == false){
                it->second.setNewOptimBroad(receivedStringFlag);
                if( isMyIdInString(receivedStringFlag, std::stoi(mobility->getExternalId())) && it->second.getOptimizationCounter() == 0)
                {
                    it->second.setOptimizationCounter(it->second.getAllOptimBroad().size());
                    outfile << "INCREMENTING THE OPTIMIZATION COUNTER, NOT ALONE. SIZE: " << it->second.getAllOptimBroad().size() << std::endl;
                }
            }
        }*/



        //----------------------------------------------------------------- ALONE START ----------------------------------------------------------------------------------
        if(aloneFlag == true){
            for(std::map<int, VehicleData>::iterator it = m_storage.begin(); it != m_storage.end(); ++it){
                it->second.setNewOptimBroad(myLeaderString);
                if(isMyIdInString(myLeaderString, consId) && it->second.getOptimizationCounter() == 0)
                {
                    it->second.setOptimizationCounter(it->second.getAllOptimBroad().size());
                    outfile << "INCREMENTING THE OPTIMIZATION COUNTER, ANLONE. SIZE: " << it->second.getAllOptimBroad().size() << std::endl;
                }
            }
        }
        //----------------------------------------------------------------- ALONE END ----------------------------------------------------------------------------------

        // print Start
        outfile << "\nV: " << mobility->getExternalId() << " RECEIVED OPTIMIZATION STRING CONTAINING:\n{id, heading, queuePos, signal}" << std::endl;
        for(std::vector<VehicleMainChar>::iterator it = vecReceivedString.begin(); it != vecReceivedString.end(); ++it){
            outfile << "{" << it->m_id << "," << it->m_heading << "," << it->m_queuePosition << "," << it->m_signal << "}" << std::endl;
        }
        outfile << std::endl;
        //print End




        //Collect the received data in my map only one time
        if(receivedBroadcastMap.size() == 0)
        {
            for(std::vector<VehicleMainChar>::iterator it = vecReceivedString.begin(); it != vecReceivedString.end(); ++it){
                receivedBroadcastMap[it->m_id] = *it;
            }
            std::cout << "\t\tReceivedBroadcastMap correctly created" << std::endl;



            //If I'm among the optimization
            if(receivedBroadcastMap.find(std::stoi(mobility->getExternalId())) != receivedBroadcastMap.end())
            {


                //Divide queuePosition and signal of vehicles for the optimizer
                std::vector<int> Evehicles, ESignal, Nvehicles, NSignal, Wvehicles, WSignal, Svehicles, SSignal;

                for(std::map<int, VehicleMainChar>::iterator it = receivedBroadcastMap.begin(); it != receivedBroadcastMap.end(); ++it)
                {
                    switch(carUtility::checkHeading(it->second.m_heading))
                    {
                    //East
                    case 1:
                        Evehicles.push_back(it->second.m_queuePosition);
                        ESignal.push_back(it->second.m_signal);
                        //outfile << "E vehicles: " << it->second.m_id;
                        continue;
                    //Nord
                    case 2:
                        Nvehicles.push_back(it->second.m_queuePosition);
                        NSignal.push_back(it->second.m_signal);
                        //outfile << "N vehicles: " << it->second.m_id;
                        continue;
                    //West
                    case 3:
                        Wvehicles.push_back(it->second.m_queuePosition);
                        WSignal.push_back(it->second.m_signal);
                        //outfile << "W vehicles: " << it->second.m_id;
                        continue;
                    //South
                    case 4:
                        Svehicles.push_back(it->second.m_queuePosition);
                        SSignal.push_back(it->second.m_signal);
                        //outfile << "S vehicles: " << it->second.m_id;
                        continue;
                    }
                }



                //print

                outfile << std::endl;
                outfile << "Vehicle " << mobility->getExternalId() << " data" << std::endl;
                outfile << "Evehicles:" << std::endl;
                for(std::vector<int>::iterator it = Evehicles.begin(); it != Evehicles.end(); ++it){
                    outfile << *it << " ";
                }
                outfile << "\nESignal:" << std::endl;
                for(std::vector<int>::iterator it = ESignal.begin(); it != ESignal.end(); ++it){
                    outfile << *it << " ";
                }
                outfile << std::endl;
                outfile << "Nvehicles:" << std::endl;
                for(std::vector<int>::iterator it = Nvehicles.begin(); it != Nvehicles.end(); ++it){
                    outfile << *it << " ";
                }
                outfile << "\nNSignal:" << std::endl;
                for(std::vector<int>::iterator it = NSignal.begin(); it != NSignal.end(); ++it){
                    outfile << *it << " ";
                }
                outfile << std::endl;
                outfile << "Wvehicles:" << std::endl;
                for(std::vector<int>::iterator it = Wvehicles.begin(); it != Wvehicles.end(); ++it){
                    outfile << *it << " ";
                }
                outfile << "\nWSignal:" << std::endl;
                for(std::vector<int>::iterator it = WSignal.begin(); it != WSignal.end(); ++it){
                    outfile << *it << " ";
                }
                outfile << std::endl;
                outfile << "Svehicles:" << std::endl;
                for(std::vector<int>::iterator it = Svehicles.begin(); it != Svehicles.end(); ++it){
                    outfile << *it << " ";
                }
                outfile << "\nSSignal:" << std::endl;
                for(std::vector<int>::iterator it = SSignal.begin(); it != SSignal.end(); ++it){
                    outfile << *it << " ";
                }
                outfile << std::endl;

                /**********************************************************************
                 *                  OPTIMIZATION FUNCTION
                 * ********************************************************************/

                std::cout << "Optimization Begin !" << std::endl;
                double timeSimulStart = simTime().dbl(); //in millisecond
                clock_t time = clock();

                chosenSolution = runOptimization(Evehicles, ESignal, Nvehicles, NSignal, Wvehicles, WSignal, Svehicles, SSignal,mapDataset);
                std::cout << "chosenSolution Executed" << std::endl;


                std::cout << "Recursion done for Vehicle " << mobility->getExternalId() << " Simulation time in: " << ((simTime().dbl() - timeSimulStart)/1000) << "[ms]" << std::endl;
                std::cout << "Recursion done for Vehicle " << mobility->getExternalId() << " Real time in: " << (clock() - time)/((clock_t)1) << "[ms]" << std::endl;

                outfile << "Recursion done for Vehicle " << mobility->getExternalId() << " Simulation time in: " << (clock() - time)/((clock_t)1) << "[ms]" << std::endl;
                outfile << "Recursion done for Vehicle " << mobility->getExternalId() << " Real time in: " << ((simTime().dbl() - timeSimulStart)/1000) << "[ms]" << std::endl;

                //Set optimized flag
                for(std::map<int, VehicleMainChar>::iterator it = receivedBroadcastMap.begin(); it != receivedBroadcastMap.end(); ++it){
                    std::map<int, VehicleData>::iterator fit = m_storage.find(it->first);
                    if(fit != m_storage.end()){
                        fit->second.setOptimized(true);
                        fit->second.setQueuePosition(it->second.m_queuePosition);
                         outfile << "\nOptimized and queue position set in found vehicle\n" << std::endl;
                    }
                    else{
                        VehicleData aux;
                        aux.setId(it->first);
                        aux.setHeading(it->second.m_heading);
                        aux.setQueuePosition(it->second.m_queuePosition);

                        m_storage[it->second.m_id] = aux;
                        //m_storage[it->second.m_id].setOptimized(true);
                        //m_storage[it->second.m_id].setQueuePosition(it->second.m_queuePosition);
                        outfile << "\nOptimized and queue position setted in NOT found vehicle\n" << std::endl;

                    }
                }
                storage::setIdsInChosenSol(chosenSolution, vecReceivedString);

                //Print Optimization
                storage::printVectorVector(chosenSolution, m_storage, path3, "");
            }

            //If I'm not optimized I reset the map
            if(isMyIdInString(receivedStringFlag, std::stoi(mobility->getExternalId())) == false && receivedBroadcastMap.find(std::stoi(mobility->getExternalId())) == receivedBroadcastMap.end()){
                receivedBroadcastMap = {};
            }


            //Increment counter of the optimization

            //setOptimizationCounter(bsm, m_storage);

            //std::cout << "\t\tOptimization counter incremented" << std::endl;



        }

    }
}


void TraCIDemo11p::updateStorage(BasicSafetyMessage* bsm)
{
    // Update the m_storage variable with the data received from the message
    if(bsm->getNodeIDBSM() != -1)
    {
        int id = bsm->getNodeIDBSM();
        Coord position = bsm->getSenderPosBSM();
        double speed = bsm->getSenderSpeedBSM();
        double heading = bsm->getHeadingBSM();
        double yaw = bsm->getYawBSM();
        double length = bsm->getCarLengthBSM();
        double width = bsm->getCarWidthBSM();
        double lanePos = bsm->getLanePositionBSM();
        int signal = bsm->getSignalBSM();

        simtime_t time = bsm->getSendtimeBSM();
        double acceleration = bsm->getAccelerationBSM();
        std::pair<double, double> intersectionPoint = std::pair<double, double>(bsm->getIntersectionXBSM(), bsm->getIntersectionYBSM());
        int intersectionFlag = bsm->getIntersectionFlagBSM();
        std::string roadId = bsm->getRoadID();

        int optimizationCounter = bsm->getOptimizationCounterBSM();
        bool optimizationFlag = bsm->getOptimizationFlagBSM();

        std::string broadcastString = bsm->getStringFlagBSM();

        std::map<int, VehicleData>::iterator it = m_storage.find(id);
        if( it != m_storage.end())
        {
            //If already present it is overwritten
            it->second.setData(id, position, speed, heading, yaw, length, width, time);
            it->second.setAcceleration(acceleration);
            it->second.setIntersectionPoint(intersectionPoint);
            it->second.setIntersectionFlag(intersectionFlag);
            it->second.setLanePosition(lanePos);
            it->second.setBeaconSignal(signal);
            it->second.setRoadId(roadId);
            if(it->second.getOptimizationCounter() == 0 && optimizationCounter != 0){
                it->second.setOptimizationCounter(optimizationCounter);
            }
            if(it->second.getOptimized() == false && optimizationFlag != false){
                it->second.setOptimized(optimizationFlag);
            }

            it->second.setBroadcastIdSet(broadcastString);

        }
        else
        {
            //no element found in the map with that index => it is added
            m_storage[id].setData(id, position, speed, heading, yaw, length, width, time);
            m_storage[id].setAcceleration(acceleration);
            m_storage[id].setIntersectionPoint(intersectionPoint);
            m_storage[id].setIntersectionFlag(intersectionFlag);
            m_storage[id].setLanePosition(lanePos);
            m_storage[id].setBeaconSignal(signal);
            m_storage[id].setRoadId(roadId);
            if(m_storage[id].getOptimizationCounter() == 0 && optimizationCounter != 0){
                m_storage[id].setOptimizationCounter(optimizationCounter);
            }
            if(m_storage[id].getOptimized() == false && optimizationFlag != false){
                m_storage[id].setOptimized(optimizationFlag);
            }

            m_storage[id].setBroadcastIdSet(broadcastString);
        }

        std::cout << "\t\textracted and updated data from BSM" << std::endl;

        //std::string pathRecap = "C:/workspace_veins-4.7.1acc_id/log/recap";
        std::string pathRecap = "E:/log/recap";
        pathRecap += std::to_string(id) + ".xml";

        std::ofstream outfile(pathRecap, std::ios::app);

        //Leader check
        leaderCheckOptimization(bsm);


        std::cout << "\t\tLeader check pass" << std::endl;

        //All vehicle check

        allVehicleCheckOptimization(bsm);


    }
}

void TraCIDemo11p::computeIntersection(int id)
{
    /*
     * Function to compute the position of the intersection
     * If possible the vehicle compute the position of the intersection, otherwise it set the
     *   real value of the intersection
     *
     * The function it's been modified. The exact position of the intersection is always set.
     *      This is done in order to extend this function with the exact position
     *       of the intersection coming from a map data.
     */

    for (std::map<int, VehicleData>::iterator it = m_storage.begin(); it != m_storage.end(); ++it)
    {
        it->second.setIntersectionPoint(std::pair<int, int>(1000.0,1000.0));
    }


}

void TraCIDemo11p::wrtIntersection()
{
    /* Compute: - the distance from the intersection for each vehicle in the storage
                - Compute the time to intersection
    */

    for( std::map<int, VehicleData>::iterator it = m_storage.begin(); it != m_storage.end(); ++it)
    {
        // 1) Compute the distance from the intersection double distance = LANE_LENGTH - it->second.getLanePosition();
        // - intersectionRadius
        double distance = 0;
        if(it->second.getIntersectionFlag() == 0){
            distance = it->second.getIntersectionPoint().first - it->second.getLanePosition();
        }
        if(it->second.getIntersectionFlag() == 1) {
            distance = -(it->second.getLanePosition() - it->second.getIntersectionPoint().first);
        }
        it->second.setDistance2Intersection(distance);



        /* 2)Compute the time to intersection with the new distance which uses the lane position.
         *      After some tests the best result are given using the simplest formula T=DeltaS/v
         */

       //Start computing the time after that the vehicles reach the full speed at least 1 time
        if(m_timeSemaphore != 1 && it->second.getVelocity() >= 13){
            m_timeSemaphore = 1;
        }

        if(m_timeSemaphore == 1)
        {
            double T_actual;
            double v = it->second.getVelocity();

            T_actual = distance/v;
            //Avoid wrong computation due to the frequency of its computation
            if(T_actual > -1000 && T_actual < 1000){
                it->second.setTime2Intersection(T_actual);
            }
        }
    }


}


void TraCIDemo11p::leader()
{
    /*
    * This procedure allow to set the leader
    *
    * Before that the optimization happened
    * It performs the following operations:
    *      1) The auxDistances vector is filled with all the distance2Intersection of each vehicle
    *      2) The auxDistances vector is sorted
    *      3) The leaderFlag is assigned to the vehicle that has the minimum distance and it's stored in the auxLeader variable.
    *      4) The leaderFlag is assigned to all the other vehicle that are present in the storage
    */

    //std::string pathRecap = "C:/workspace_veins-4.7.1acc_id/log/recap";
    std::string pathRecap = "E:/log/recap";
    pathRecap += mobility->getExternalId() + ".xml";

    std::ofstream outfile(pathRecap, std::ios::app);

    //{heading, {distance2intersection}}
    std::map<double, std::vector<double>> auxDistance;

    if(m_storage.size()>=2 && storage::optimizationAlreadyHappened(m_storage) == false)
    {
        //1) The auxDistances vector is filled with all the distance2Intersection of each vehicle for each direction

        for(std::map<int, VehicleData>::iterator it = m_storage.begin(); it != m_storage.end(); ++it)
        {
            //{heading, {distance2intersection}}
            std::map<double, std::vector<double>>::iterator fit = auxDistance.find(it->second.getHeading());
            if(fit == auxDistance.end())
            {
                //Condition to avoid error due to new generated vehicle
                if(it->second.getLanePosition() > 5)
                {
                    std::vector<double> distAux = {it->second.getDistance2Intersection()};
                    auxDistance[it->second.getHeading()] = distAux;
                }
            }
            else
            {
                if(it->second.getLanePosition() > 5)
                {
                    fit->second.push_back(it->second.getDistance2Intersection());
                }
            }
        }

        //2) The auxDistances vector is sorted
        for(std::map<double, std::vector<double>>::iterator it = auxDistance.begin(); it != auxDistance.end(); ++it)
        {
            std::sort(it->second.begin(), it->second.end());
        }


        //3) The leaderFlag is assigned to the vehicle that has the minimum distance and it's stored in the auxLeader variable.
        std::vector<double> leaderDistance;
        //{vehicle id, heading}
        std::map<int, double> leaders;
        //      collect the minimum distances for each direction
        for(std::map<double, std::vector<double>>::iterator it = auxDistance.begin(); it != auxDistance.end(); ++it)
        {
            if(it->second.size() > 0){
                leaderDistance.push_back(*it->second.begin());
            }
        }
        //      search for the vehicle id and store it
        for(std::map<int, VehicleData>::iterator it = m_storage.begin(); it != m_storage.end(); ++it)
        {
            for(std::vector<double>::iterator sit = leaderDistance.begin(); sit != leaderDistance.end(); ++ sit)
            {
                if(it->second.getDistance2Intersection() == *sit)
                {
                    leaders[it->first] = it->second.getHeading();
                }
            }
        }

        //4) The leaderFlag is assigned to all the other vehicle that are present in the storage
        for(std::map<int, double>::iterator it = leaders.begin(); it != leaders.end(); ++it)
        {
            for(std::map<int, VehicleData>::iterator mit = m_storage.begin(); mit != m_storage.end(); ++mit)
            {
                if(mit->second.getHeading() == it->second && mit->second.getOptimized() == false){
                    mit->second.setLeaderFlag(it->first);
                }
            }
        }
    }





    //{heading, {distance2intersection}}
    std::map<double, std::vector<double>> auxDistance2;

    if(storage::optimizationAlreadyHappened(m_storage) == true)
    {
        std::map<int, VehicleData> optimizedStorage = {};
        for(std::map<int, VehicleData>::iterator it = m_storage.begin(); it != m_storage.end(); ++it)
        {
            if(it->second.getOptimized() == true){
                optimizedStorage[it->first] = it->second;
            }
        }

        // vehicles not optimized detection
        std::map<int, VehicleData> auxStorage = {};
        for(std::map<int, VehicleData>::iterator it = m_storage.begin(); it != m_storage.end(); ++it)
        {
            if(it->second.getOptimized() == false){
                auxStorage[it->first] = it->second;
            }
        }

        outfile << "auxStorage:" << std::endl;
        for(std::map<int, VehicleData>::iterator it = auxStorage.begin(); it != auxStorage.end(); ++it)
        {
            outfile << "id:" <<it->first << " heading:" << it->second.getHeading() << std::endl;
        }
        /* print
        for(std::map<int, VehicleData>::iterator it = auxStorage.begin(); it != auxStorage.end(); ++it){
            std::cout << "id: " << it->second.getId() << " heading: " << it->second.getHeading() << std::endl;
        }
         */

        // 1)
        for(std::map<int, VehicleData>::iterator it = auxStorage.begin(); it != auxStorage.end(); ++it)
        {
            //{heading, {distance2intersection}}
           std::map<double, std::vector<double>>::iterator fit = auxDistance2.find(it->second.getHeading());
           if(fit == auxDistance2.end())
           {
               //Condition to avoid error due to new generated vehicle

               std::vector<double> distAux = {it->second.getDistance2Intersection()};
               auxDistance2[it->second.getHeading()] = distAux;

           }
           else
           {
               fit->second.push_back(it->second.getDistance2Intersection());
           }
        }



        // 2)
        for(std::map<double, std::vector<double>>::iterator it = auxDistance2.begin(); it != auxDistance2.end(); ++it)
        {
            std::sort(it->second.begin(), it->second.end());
        }

        // 3)
        //{heading, LeaderDistance}
        std::map<double, double> lDist = {};
        for(std::map<double, std::vector<double>>::iterator it = auxDistance2.begin(); it != auxDistance2.end(); ++it)
        {
            lDist[it->first] = *it->second.begin();
        }

        std::map<int, VehicleData> leaders = {};
        for(std::map<double, double>::iterator it = lDist.begin(); it != lDist.end(); ++it)
        {
            for(std::map<int, VehicleData>::iterator sit = auxStorage.begin(); sit != auxStorage.end(); ++sit)
            {
                if(it->first == sit->second.getHeading() && it->second == sit->second.getDistance2Intersection()){
                    leaders[sit->first] = sit->second;
                    break;
                }
            }
        }

        outfile << "Leaders Founded:" << std::endl;
        for(std::map<int, VehicleData>::iterator it = leaders.begin(); it != leaders.end(); ++it)
        {
            outfile << "id:" << it->first << " heading:" << it->second.getHeading() << std::endl;
        }

        // 4)
        for(std::map<int, VehicleData>::iterator it = optimizedStorage.begin(); it != optimizedStorage.end(); ++it)
        {
            std::map<int, VehicleData>::iterator fit = m_storage.find(it->first);
            if(fit != m_storage.end() && fit->second.getOptimized() == false){
                fit->second.setLeaderFlag(it->second.getLeaderFlag());
            }
        }

        for(std::map<int, VehicleData>::iterator it = leaders.begin(); it != leaders.end(); ++it)
        {
            for(std::map<int, VehicleData>::iterator sit = m_storage.begin(); sit != m_storage.end(); ++sit)
            {
                if(sit->second.getOptimized() == false && sit->second.getHeading() == it->second.getHeading()){
                    sit->second.setLeaderFlag(it->first);
                }
            }
        }

        /*
        std::map<int, std::map<int, VehicleData>> auxStByCircle = storage::storageVehicleByCircle(auxStorage);

        // print
        //for(std::map<int, std::map<int, VehicleData>>::iterator it = auxStByCircle.begin(); it != auxStByCircle.end(); ++it)
        //{
        //    std::cout << "queue: " << it->first << std::endl;
        //    for(std::map<int, VehicleData>::iterator sit = it->second.begin(); sit != it->second.end(); ++sit)
        //    {
        //        std::cout << "\tID: " << sit->second.getId() << " Heading: " << sit->second.getHeading() << std::endl;
        //    }
        //}

        std::map<int, std::map<int, VehicleData>>::iterator itFind = auxStByCircle.find(1);
        if(itFind != auxStByCircle.end() && auxStByCircle.begin()->second.size() > 0)
        {
            std::vector<VehicleData> newLeaders = {};
            std::vector<VehicleData> toAssign = {};
            for(std::map<int, VehicleData>::iterator it = auxStByCircle.begin()->second.begin(); it != auxStByCircle.begin()->second.end(); ++it)
            {
                newLeaders.push_back(it->second);
            }

            for(std::map<int, std::map<int, VehicleData>>::iterator it = auxStByCircle.begin(); it != auxStByCircle.end(); ++it)
            {
                for(std::map<int, VehicleData>::iterator sit = it->second.begin(); sit != it->second.end(); ++sit)
                {
                    toAssign.push_back(sit->second);
                }
            }

            for(std::vector<VehicleData>::iterator it = toAssign.begin(); it != toAssign.end(); ++it)
            {
                for(std::vector<VehicleData>::iterator sit = newLeaders.begin(); sit != newLeaders.end(); ++sit)
                {
                    if(it->getHeading() == sit->getHeading())
                    {
                        m_storage[it->getId()].setLeaderFlag(sit->getId());
                    }
                }
            }

        }
        */

    }



}


void TraCIDemo11p::manageSeenVehicles(BasicSafetyMessage* bsm)
{
    myHeadingVector(bsm);
    allSeenVehicle(bsm);
    vehicleInMyDir(bsm);

}


void TraCIDemo11p::myHeadingVector(BasicSafetyMessage* bsm)
{
    /* Detect all seen direction
     * Save into a vector each direction that I receive
     */
    double bsmHeading = bsm->getHeadingBSM();
    int myindex = std::stoi(mobility->getExternalId());

    m_storage[myindex].setHeadingVecElement(m_storage[myindex].getHeading());
    m_storage[myindex].setHeadingVecElement(bsmHeading);

    m_storage[myindex].setHeadingPair(myindex, m_storage[myindex].getHeading());
    m_storage[myindex].setHeadingPair(bsm->getNodeIDBSM(), bsmHeading);


}

void TraCIDemo11p::allSeenVehicle(BasicSafetyMessage* bsm)
{
    if(m_storage[bsm->getNodeIDBSM()].getDistance2Intersection() >= 4.9)
    {
        if(bsm->getHeadingBSM() == -1){
            m_invalHeadingCounterAll += 1;
            if(m_invalHeadingCounterAll >= 4){
                m_storage[std::stoi(mobility->getExternalId())].setAllSeenVehicle(bsm->getHeadingBSM(), bsm->getNodeIDBSM());
            }
        }
        else{
            m_storage[stoi(mobility->getExternalId())].setAllSeenVehicle(bsm->getHeadingBSM(), bsm->getNodeIDBSM());
        }
    }

}

void TraCIDemo11p::vehicleInMyDir(BasicSafetyMessage *bsm)
{
    if(m_storage[bsm->getNodeIDBSM()].getDistance2Intersection() >= 4.9)
    {
        if(bsm->getHeadingBSM() != -1)
        {
            m_storage[std::stoi(mobility->getExternalId())].setVehicleMyDir(m_storage[std::stoi(mobility->getExternalId())].getHeading(), bsm->getHeadingBSM(), bsm->getNodeIDBSM());
        }
    }
}





/***********************************************************************************************************************************************************************************************
 *
 *                                                                          Virtual Traffic Light
 *
 ***********************************************************************************************************************************************************************************************/


void TraCIDemo11p::prepareLeaderData()
{
    //std::string patRec = "C:/workspace_veins-4.7.1acc_id/log/recap" + mobility->getExternalId() + ".xml";
    std::string patRec = "E:/log/recap" + mobility->getExternalId() + ".xml";
    std::ofstream outfile(patRec, std::ios::app);

    int leader = m_storage[std::stoi(mobility->getExternalId())].getLeaderFlag();



    //If the considered vehicle is the leader
    if(std::stoi(mobility->getExternalId()) == leader)
    {

        //Executed only one time
        if(m_storage[leader].getDistance2Intersection() < 55.5 && semPrepareLeaderData == 0)
        {
            semPrepareLeaderData = 1;

            //std::cout << "\t\tInside prepare data" << std::endl;

            //Contains all vehicles under 100m when the leader start the search
            std::vector<VehicleMainChar> under100 = {};

            int counterE = 1;
            int counterN = 1;
            int counterW = 1;
            int counterS = 1;
            outfile << "\n\n\n\n\nfounded vehicles:" << std::endl;
            for(std::map<int, VehicleData>::iterator it = m_storage.begin(); it != m_storage.end(); ++it)
            {
                //if(it->second.getDistance2Intersection() < 100 && it->first != leader)
                if(it->second.getDistance2Intersection() < 100 && it->second.getOptimized() == false)
                {

                    outfile << "id: " << it->second.getId() << " heading:" << it->second.getHeading() << std::endl;
                    //Check if the vehicle come form East
                    if(carUtility::checkHeading(m_storage[it->first].getHeading()) == 1)
                    {
                        //It's possible to have at maximum 6 vehicles
                        if(counterE <= 6){
                            VehicleMainChar auxE(it->first, counterE, m_storage[it->first].getSignal(), m_storage[it->first].getHeading());
                            Ev.push_back(auxE);
                            under100.push_back(auxE);
                            counterE++;
                        }
                    }
                    //Check if the vehicle come form Nord
                    if(carUtility::checkHeading(m_storage[it->first].getHeading()) == 2)
                    {
                        //It's possible to have at maximum 6 vehicles
                        if(counterN <= 6){
                            VehicleMainChar auxN(it->first, counterN, m_storage[it->first].getSignal(), m_storage[it->first].getHeading());
                            Nv.push_back(auxN);
                            under100.push_back(auxN);
                            counterN++;
                        }
                    }
                    //Check if the vehicle come form West
                    if(carUtility::checkHeading(m_storage[it->first].getHeading()) == 3)
                    {
                        //It's possible to have at maximum 6 vehicles
                        if(counterW <= 6){
                            VehicleMainChar auxW(it->first, counterW, m_storage[it->first].getSignal(), m_storage[it->first].getHeading());
                            Wv.push_back(auxW);
                            under100.push_back(auxW);
                            counterW++;
                        }
                    }
                    //Check if the vehicle come form South
                    if(carUtility::checkHeading(m_storage[it->first].getHeading()) == 4)
                    {
                        //It's possible to have at maximum 6 vehicles
                        if(counterS <= 6){
                            VehicleMainChar auxS(it->first, counterS, m_storage[it->first].getSignal(), m_storage[it->first].getHeading());
                            Sv.push_back(auxS);
                            under100.push_back(auxS);
                            counterS++;
                        }
                    }
                }
            }



            //Convert under100 into bitString to be stored and sent

            if(under100.size() > 0)
            {
                under100ToBitString = vmcVector2bit(under100);
                outfile << "leader " << leader << " at distance = " << m_storage[leader].getDistance2Intersection() << " send the string:\n" << under100ToBitString << std::endl;

                //Seen Leader identification with empty string
                //std::map<int, std::string> lMap = {};

                for(std::map<int, VehicleData>::iterator it = m_storage.begin(); it != m_storage.end(); ++it)
                {
                    if(it->first == it->second.getLeaderFlag() && it->second.getOptimized() == false)
                    {
                        if(it->first == leader){

                            m_storage[leader].setLeadersMapElement(leader, under100ToBitString);
                            //lMap[leader] = under100ToBitString;
                        }
                        if(it->first != leader){
                              m_storage[leader].setLeadersMapElement(it->first, "");
                                //lMap[it->first] = "";
                        }
                        //m_storage[leader].setLeadersMapElement(it->second.getLeaderFlag(), "");
                    }
                }

                std::map<int, std::string> mappa = m_storage[leader].getLeadersMap();
                outfile << "PRINT AFTER SETTING" << std::endl;
                for(std::map<int, std::string>::iterator it = mappa.begin(); it != mappa.end(); ++it)
                {
                    outfile << "id: " << it->first << " S:" << it->second << std::endl;
                }

                //Set the bitString in the leader storage
                //m_storage[leader].setLeadersMapElement(leader, under100ToBitString);
                //m_storage[leader].setLeadersMap(lMap);

                /* Test robustness against different sent messages among leader
                if(std::stoi(mobility->getExternalId()) == 3){
                    m_storage[leader].setLeadersMapElement(leader, "00000000000000000010101001110101000000000000000100101001001110110000000000000010001100000000000000000000000000110011000100111010000000000000010001010010011101010000000000000101010100010011101100000000000001100101000000000000000000000000011101001101001110100000000000001000011011100111010100000000000010010110110100111011");
                }
                else{
                    m_storage[leader].setLeadersMapElement(leader, under100ToBitString);
                }*/




                //Print




                outfile << "Vehicle considered in the sent string:" << std::endl;
                outfile << "E Vehicle {id, queuePosition, Signal, Heading}: " << std::endl;
                for(std::vector<VehicleMainChar>::iterator v = Ev.begin(); v != Ev.end(); ++v){
                    outfile << "\t{" << v->m_id << " " << v->m_queuePosition << " " << v->m_signal << " " << v->m_heading << "}" << std::endl;
                }

                outfile << "N Vehicle {id, queuePosition, Signal, Heading}: " << std::endl;
                for(std::vector<VehicleMainChar>::iterator v = Nv.begin(); v != Nv.end(); ++v){
                    outfile << "\t{" << v->m_id << " " << v->m_queuePosition << " " << v->m_signal << " " << v->m_heading << "}" << std::endl;
                }

                outfile << "W Vehicle: {id, queuePosition, Signal, Heading}: " << std::endl;
                for(std::vector<VehicleMainChar>::iterator v = Wv.begin(); v != Wv.end(); ++v){
                    outfile << "\t{" << v->m_id << " " << v->m_queuePosition << " " << v->m_signal << " " << v->m_heading << "}" << std::endl;
                }

                outfile << "S Vehicle: {id, queuePosition, Signal, Heading}: " << std::endl;
                for(std::vector<VehicleMainChar>::iterator v = Sv.begin(); v != Sv.end(); ++v){
                    outfile << "\t{" << v->m_id << " " << v->m_queuePosition << " " << v->m_signal << " " << v->m_heading << "}" << std::endl;
                }

                outfile.close();
            }
        }
    }

}






void TraCIDemo11p::printIdSigna()
{
    if(semPrint == 0 && semVTL == 1)
    {
        //std::string path = "C:/workspace_veins-4.7.1acc_id/log/Vehicle" + mobility->getExternalId() + "SignalSeen.xml";
        std::string path = "E:/log/Vehicle" + mobility->getExternalId() + "SignalSeen.xml";
        std::ofstream myfile(path, std::ios::app);

        for(std::map<int, VehicleData>::iterator it = m_storage.begin(); it != m_storage.end(); ++it)
        {
            myfile << "id: " << it->first << " signal: " << it->second.getSignal() << std::endl;
        }
        semPrint++;
    }

}




void TraCIDemo11p::checkallSignals(std::string path)
{
    int counter = 0;
    if(semaphore2 == 0)
    {
        for(std::map<int, VehicleData>::iterator it = m_storage.begin(); it != m_storage.end(); ++it)
        {
            if(it->second.getSignal() != 0){
                counter += 1;
            }
        }

        if(counter == 7){
            semaphore2 = 1;
            std::string text = "VEHICLE STORAGE: ";
            text += mobility->getExternalId();
            wrt::w2path(text, path);
            wrt::printStorage(m_storage, path, std::stoi(mobility->getExternalId()));
        }
    }
}





void TraCIDemo11p::speedManaging()
{

    int myId = std::stoi(mobility->getExternalId());
    //int myQueue = m_storage[myId].getQueuePosition();
    //int myOptimCount = m_storage[myId].getOptimizationCounter();

    if(semGreen == 0)
    {
        // If I am in vehicles optimized
        if(receivedBroadcastMap.find(myId) != receivedBroadcastMap.end() && m_storage[myId].getIntersectionFlag() != 1)
        {
            std::cout << "\n\t\tAmong optimized vehicles: speed managing" << std::endl;
            if(storage::previousOptimizationNotCrossed(m_storage, myId) == false)
            {
                //If all vehicles of previous optimization cross the intersection
                if(storage::canICross(m_storage, chosenSolution, myId) == false)
                {
                    speedAproachingIntersectionManagement(m_storage, myId);
                    std::cout << "\t\tPrevious optimization cross but I can not cross\n" << std::endl;
                }
                if(storage::canICross(m_storage, chosenSolution, myId) == true && m_storage[myId].getIntersectionFlag() == 0)
                {
                    traciVehicle->setSpeed(13.8);
                    findHost()->getDisplayString().updateWith("r=2,green");
                    std::cout << "\n\t\tI have green... crossing\n" << std::endl;
                }
                //Print storage of vehicles when the phase is green
                if(storage::canICross(m_storage, chosenSolution, myId) == true && (m_storage[myId].getLanePosition() >= 992.3 || m_storage[myId].getLanePosition() < 7.7)){
                    printGreen(chosenSolution);
                    semGreen = 1;
                }

            }

            if(storage::previousOptimizationNotCrossed(m_storage, myId) == true)
            {
                speedAproachingIntersectionManagement(m_storage, myId);
                std::cout << "\n\t\tWaiting all previous optimized vehicle corss the intersection\n" << std::endl;
            }
        }

        else{
            std::cout << "Not among optimized vehicles: speed managing" << std::endl;
            speedAproachingIntersectionManagement(m_storage, myId);
        }
    }

    if(semGreen == 1){
        traciVehicle->setSpeed(13.8);
    }

    if(traciVehicle->getRoadId()[0] == ':'){
        traciVehicle->setSpeed(13.8);
    }
}




bool TraCIDemo11p::amILeader()
{
   int leader = m_storage[std::stoi(mobility->getExternalId())].getLeaderFlag();
   if (std::stoi(mobility->getExternalId()) == leader){
       return true;
   }
   return false;
}


bool TraCIDemo11p::allOtherLeadersRespondMe(std::map<int, std::string> leadersMap, int myId)
{
    if(leadersMap.find(myId) != leadersMap.end())
    {
        std::string sentString = leadersMap[myId];
        std::vector<VehicleMainChar> toData = bitString2vmc(sentString);

        //Extracting leaders form the sent string

        //Extract from the storage only the received dataset
        std::map<int, VehicleData> auxStorage = {};
        for(std::vector<VehicleMainChar>::iterator it = toData.begin(); it != toData.end(); ++it)
        {
            std::map<int, VehicleData>::iterator fit = m_storage.find(it->m_id);
            if(fit != m_storage.end()){
                auxStorage[fit->first] = fit->second;
            }
        }

        //map {heading, distance2intersection}
        std::map<double, std::vector<double>> dist2intersAux = {};
        for(std::map<int, VehicleData>::iterator it = auxStorage.begin(); it != auxStorage.end(); ++it)
        {
            std::map<double, std::vector<double>>::iterator fit = dist2intersAux.find(it->second.getHeading());
            if(fit == dist2intersAux.end())
            {
                std::vector<double> auxDist = {it->second.getDistance2Intersection()};
                dist2intersAux[it->second.getHeading()] = auxDist;
            }
            else{
                std::vector<double> auxD = dist2intersAux[it->second.getHeading()];
                auxD.push_back(it->second.getDistance2Intersection());
                dist2intersAux[it->second.getHeading()] = auxD;
            }
        }

        for(std::map<double, std::vector<double>>::iterator it = dist2intersAux.begin(); it != dist2intersAux.end(); ++it)
        {
            std::sort(it->second.begin(), it->second.end());
        }

        std::map<int, VehicleData> leader = {};
        for(std::map<double, std::vector<double>>::iterator it = dist2intersAux.begin(); it != dist2intersAux.end(); ++it)
        {
            for(std::map<int, VehicleData>::iterator sit = auxStorage.begin(); sit != auxStorage.end(); ++sit)
            {
                if(sit->second.getDistance2Intersection() == *it->second.begin()){
                    leader[sit->first] = sit->second;
                    continue;
                }
            }
        }

        //std::string recPath = "C:/workspace_veins-4.7.1acc_id/log/recap" + mobility->getExternalId() + ".xml";
        std::string recPath = "E:/log/recap" + mobility->getExternalId() + ".xml";
        std::ofstream outfile(recPath, std::ios::app);
        if(leader.size() != leadersMap.size())
        {
            std::cout << "\n\t\tNot all leader reply:\n\t\tLeader Sent in my message: ";
            outfile << "\n\t\tNot all leader reply:\n\t\tLeader Sent in my message: ";
            for(std::map<int, VehicleData>::iterator it = leader.begin(); it != leader.end(); ++it)
            {
                std::cout << it->first << " ";
                outfile << it->first << " ";
            }
            outfile << std::endl;
            std::cout << std::endl;


            std::cout << "\n\t\tMessage received from: ";
            outfile << "\n\t\tMessage received from: ";
            for(std::map<int, std::string>::iterator it = leadersMap.begin(); it != leadersMap.end(); ++it){
                outfile << it->first << " ";
                std::cout << it->first << " ";
            }
            outfile << std::endl;
            std::cout << std::endl;
            return false;
        }
        else{
            std::cout << "\n\t\tAll leader reply:\n\t\tLeader Sent in my message: ";
            outfile <<  "\n\t\tAll leader reply:\n\t\tLeader Sent in my message: ";
            for(std::map<int, VehicleData>::iterator it = leader.begin(); it != leader.end(); ++it)
            {
                std::cout << it->first << " ";
                outfile << it->first << std::endl;
            }
            std::cout << std::endl;
            outfile << std::endl;

            std::cout << "\n\t\tMessage received from: ";
            outfile <<  "\n\t\tMessage received from: ";
            for(std::map<int, std::string>::iterator it = leadersMap.begin(); it != leadersMap.end(); ++it){
                outfile << it->first << " ";
                std::cout << it->first << " ";
            }
            std::cout << std::endl;
            outfile << std::endl;
            return true;
        }
        outfile.close();

    }
    return false;
}


void TraCIDemo11p::leaderReceiving()
{
    //std::string recPath = "C:/workspace_veins-4.7.1acc_id/log/recap" + mobility->getExternalId() + ".xml";
    std::string recPath = "E:/log/recap" + mobility->getExternalId() + ".xml";
    std::ofstream recOut(recPath, std::ios::app);


    //Check correspondence between number of seen leaders and seen response with their flag
    std::map<int, std::string> leadersMap = m_storage[std::stoi(mobility->getExternalId())].getLeadersMap();

    recOut << "LeaderReceiving():" << std::endl;
    for(std::map<int, std::string>::iterator it = leadersMap.begin(); it != leadersMap.end(); ++it){
        recOut << "id: " << it->first << " S: " << it->second << std::endl;
    }
    //Search for leaders in the storage
    std::map<int, VehicleData> smallStorage = {};

    //Eligible vehicles to be leaders
    //{heading, {distance2intersection}}
    std::map<double, std::vector<double>> directionOrderer = {};
    for(std::map<int, VehicleData>::iterator it = m_storage.begin(); it != m_storage.end(); ++it)
    {
        //If I've not cross the intersection
        if(it->second.getIntersectionFlag() == 0 && it->second.getRoadId()[0] != ':'){
            std::map<double, std::vector<double>>::iterator fit = directionOrderer.find(it->second.getHeading());
            if(fit != directionOrderer.end()){
                fit->second.push_back(it->second.getDistance2Intersection());
            }
            else{
                directionOrderer[it->second.getHeading()] = {it->second.getDistance2Intersection()};
            }
        }
    }

    //Sorting eligible vehicles
    for(std::map<double, std::vector<double>>::iterator it = directionOrderer.begin(); it != directionOrderer.end(); ++it)
    {
        std::sort(it->second.begin(), it->second.end());
    }

    //Searching for the first vehicle for each direction ad collect it's id and data in the smallStorage
    for(std::map<double, std::vector<double>>::iterator it = directionOrderer.begin(); it != directionOrderer.end(); ++it)
    {
        for(std::map<int, VehicleData>::iterator sit = m_storage.begin(); sit != m_storage.end(); ++sit){
            if(sit->second.getHeading() == it->first && sit->second.getDistance2Intersection() == *it->second.begin()){
                smallStorage[sit->first] = sit->second;
                break;
            }
        }
    }


    bool check = false;
    for(std::map<int, VehicleData>::iterator it = smallStorage.begin(); it != smallStorage.end(); ++it)
    {
        std::map<int, std::string>::iterator fit = leadersMap.find(it->first);
        //if I receive a message for that leader and it's not an empty string
        if(fit != leadersMap.end() && std::strncmp(fit->second.c_str(), "", 1) != 0)
        {
            check = true;
        }
        else{
            check = false;
            break;
        }
    }


    //If I have received a message from all leader and it's not an empty string

    if(check == true)
    {
        recOut << "Received Message from all leader:" << std::endl;
        for(std::map<int, std::string>::iterator it = leadersMap.begin(); it != leadersMap.end(); ++it){
            recOut << "leader: " << it->first << " S: " << it->second << std::endl;
        }

        //{id, VehicleMainChar} collect all vehicles received in all messages from all leaders
        std::map<int, VehicleMainChar> traducedMessage = {};
        //collecting all messagges into a vector and sorting it by size
        std::vector<std::string> messageVector = {};
        for(std::map<int, std::string>::iterator it = leadersMap.begin(); it != leadersMap.end(); ++it)
        {
            messageVector.push_back(it->second);
        }
        std::sort(messageVector.begin(), messageVector.end(), storage::compareSize);
        std::reverse(messageVector.begin(), messageVector.end());

        for(std::vector<std::string>::iterator it = messageVector.begin(); it != messageVector.end(); ++it)
        {
            std::vector<VehicleMainChar> receivedVector = bitString2vmc(*it);
            for(std::vector<VehicleMainChar>::iterator sit = receivedVector.begin(); sit != receivedVector.end(); ++sit)
            {
                if(traducedMessage.find(sit->m_id) == traducedMessage.end()){
                    traducedMessage[sit->m_id] = *sit;
                }
            }
        }

        //Checking for correct queue position
        //dividing vehicle  by heading {heading, {id, VehicleMainChar}}
        std::map<double, std::map<int, VehicleMainChar>> auxMap = {};
        for(std::map<int, VehicleMainChar>::iterator it = traducedMessage.begin(); it != traducedMessage.end(); ++it)
        {
            std::map<double, std::map<int, VehicleMainChar>>::iterator fit = auxMap.find(it->second.m_heading);
            if(fit == auxMap.end())
            {
                std::map<int, VehicleMainChar> a1 = {{it->first, it->second}};
                auxMap[it->second.m_heading] = a1;
            }
            else{
                fit->second.insert(std::pair<int, VehicleMainChar>(it->first, it->second));
            }
        }

        //Checking if queue are in correct order based on heading
        int correctingFlag = 0;
        int countQueue = 1;
        for(std::map<double, std::map<int,VehicleMainChar>>::iterator it = auxMap.begin(); it != auxMap.end(); ++it)
        {
            countQueue = 1;
            for(std::map<int, VehicleMainChar>::iterator sit = it->second.begin(); sit != it->second.end(); ++sit){
                if(sit->second.m_queuePosition != countQueue){
                    sit->second.m_queuePosition = countQueue;
                    correctingFlag = 1;
                }
                countQueue++;
            }
        }

        if(correctingFlag == 1)
        {
            recOut << "Correcting queue order..." << std::endl;
            traducedMessage = {};
            for(std::map<double, std::map<int, VehicleMainChar>>::iterator it = auxMap.begin(); it != auxMap.end(); ++it){
                for(std::map<int, VehicleMainChar>::iterator sit = it->second.begin(); sit != it->second.end(); ++sit){
                    traducedMessage[sit->second.m_id] = sit->second;
                }
            }
            recOut << "Correcting queue done" << std::endl;
        }

        //print
        recOut << "Optimization Set:" << std::endl;
        for(std::map<int, VehicleMainChar>::iterator it = traducedMessage.begin(); it != traducedMessage.end(); ++it)
        {
            recOut << "id: " << it->second.m_id << " heading: " << it->second.m_heading << " queuePos: " << it->second.m_queuePosition << " signl: " << it->second.m_signal << std::endl;
        }


        //Converting all mapped vehicle in the string to send
        std::string readyToSend = vmcMap2bit(traducedMessage);
        m_storage[std::stoi(mobility->getExternalId())].setBroadcastIdSet(readyToSend);

    }
    else{
        recOut << "Message not received from all leaders:" << std::endl;
        for(std::map<int, std::string>::iterator it = leadersMap.begin(); it != leadersMap.end(); ++it){
            recOut << "leader: " << it->first << " S: " << it->second << std::endl;
        }
    }


    /*



    int seenLeaders = leadersMap.size();
    int responseNumber = 0;

    if(leadersEqualityCounter <=3){
        //Check not empty leaders string
        for(std::map<int, std::string>::iterator it = leadersMap.begin();it != leadersMap.end(); ++it) {
            if(it->second != "") { responseNumber += 1; }
        }
        if(seenLeaders == responseNumber){
            leadersEqualityCounter += 1;
        }
    }

    std::ofstream outfile("C:/workspace_veins-4.7.1acc_id/log/recap.xml", std::ios::app);

    // check if the number of seen leaders is equal to not empty response
    //vehicle 26 does not work, I change this if

    //if(allOtherLeadersRespondMe(leadersMap, std::stoi(mobility->getExternalId())) == true)
    if(seenLeaders == responseNumber && responseNumber > 1 && leadersEqualityCounter >=3)
    {
        std::cout << "Leader have check in the storage and it found the same number of received message and leaders" << std::endl;
        std::vector<VehicleMainChar> receivedDataFromAllLeaders = {};


        if(isEqualLeadersStringMap(leadersMap) == true)
        {

            outfile << "\nAll string are equal, The broadcast can start\n" << std::endl;

            m_storage[std::stoi(mobility->getExternalId())].setBroadcastIdSet(leadersMap.begin()->second);
            std::cout << "Vehicle " << mobility->getExternalId() << " sent string: " << leadersMap.begin()->second;
            semReadyToBroadcast = 1;
            semLeaderReceiving = 1;
        }
        else
        {
            outfile << "Vehicle: " << mobility->getExternalId() << "\nThe received string are different, start the process to define an unique dataset to be transmit\n" << std::endl;
            outfile << "Strings are:" << std::endl;
            for(std::map<int, std::string>::iterator it = leadersMap.begin(); it != leadersMap.end(); ++it)
            {
                outfile << "V: " << it->first << " S: " << it->second << std::endl;
            }

            std::map<int, VehicleMainChar> leadersMap2VehicleMainChar = {};
            //insert the first leader information to a vector
            std::vector<VehicleMainChar> first = bitString2vmc(leadersMap.begin()->second);
            // pass the vector's element to a map: key->id; value->VehicleMainChar
            for(std::vector<VehicleMainChar>::iterator it = first.begin(); it != first.end(); ++it)
            {
                leadersMap2VehicleMainChar[it->m_id] = *it;
            }

            //search for new elements and if exists add them to the map
            for(std::map<int, std::string>::iterator it = leadersMap.begin(); it != leadersMap.end(); ++it)
            {
                std::vector<VehicleMainChar> nthConvertion = bitString2vmc(it->second);
                for(std::vector<VehicleMainChar>::iterator sit = nthConvertion.begin(); sit != nthConvertion.end(); ++sit)
                {
                    std::map<int, VehicleMainChar>::iterator searched = leadersMap2VehicleMainChar.find(sit->m_id);

                    if(searched == leadersMap2VehicleMainChar.end()){
                        leadersMap2VehicleMainChar[sit->m_id] = *sit;
                    }
                }
            }

            //Convert the final map into a vector
            std::vector<VehicleMainChar> map2vecReadyToBroadcast = {};
            for(std::map<int, VehicleMainChar>::iterator it = leadersMap2VehicleMainChar.begin(); it != leadersMap2VehicleMainChar.end(); ++it)
            {
                map2vecReadyToBroadcast.push_back(it->second);
            }

            std::string stringReadyToBroadcast = vmcVector2bit(map2vecReadyToBroadcast);

            outfile << "The unique dataset string is:\n" << stringReadyToBroadcast << std::endl;

            m_storage[std::stoi(mobility->getExternalId())].setBroadcastIdSet(stringReadyToBroadcast);
            std::cout << "Vehicle " << mobility->getExternalId() << " sent string: " << stringReadyToBroadcast;
            semReadyToBroadcast = 1;
            semLeaderReceiving = 1;


        }

        outfile.close();


        std::cout << "\n\n\nVehicle " << mobility->getExternalId() << " READY  Distance-> " << m_storage[std::stoi(mobility->getExternalId())].getDistance2Intersection();

        std::cout << " message: " << m_storage[std::stoi(mobility->getExternalId())].getLeadersMapElement(std::stoi(mobility->getExternalId())) << std::endl;

        findHost()->getDisplayString().updateWith("r=4,blue");
    }

    if(otherVehiclesInOtherDirNotOptim(m_storage, std::stoi(mobility->getExternalId())) == true && seenLeaders == responseNumber && responseNumber == 1)
    {
        if(isEqualLeadersStringMap(leadersMap) == true)
        {

            outfile << "\nAll string are equal, The broadcast can start\n" << std::endl;

            m_storage[std::stoi(mobility->getExternalId())].setBroadcastIdSet(leadersMap.begin()->second);
            std::cout << "Vehicle " << mobility->getExternalId() << " sent string: " << leadersMap.begin()->second;
            semReadyToBroadcast = 1;
            semLeaderReceiving = 1;
        }
    }

    */
}




void TraCIDemo11p::speedAproachingIntersectionManagement(std::map<int, VehicleData> m_storage, int myId)
{
    if(m_storage[myId].getDistance2Intersection() <= 26 && m_storage[myId].getDistance2Intersection() > 15.5 && m_storage[myId].getIntersectionFlag() == 0){
        traciVehicle->setSpeed(9.7);
        findHost()->getDisplayString().updateWith("r=2,yellow");
    }
    if(m_storage[myId].getDistance2Intersection() <= 15.5 && m_storage[myId].getDistance2Intersection() > 10.5 && m_storage[myId].getIntersectionFlag() == 0){
        traciVehicle->setSpeed(6);
        findHost()->getDisplayString().updateWith("r=2,orange");
    }
    if(m_storage[myId].getDistance2Intersection() <= 10.5 && m_storage[myId].getIntersectionFlag() == 0){
        findHost()->getDisplayString().updateWith("r=2,red");
        // move the vehicle to the intersection line
        if(m_storage[myId].getLanePosition() <= 992.3){
            traciVehicle->setSpeed(5);
        }
        else{
            traciVehicle->setSpeed(0);
        }

        //Print storage of vehicles when the phase is red
        printRed(chosenSolution);
    }
    if(m_storage[myId].getRoadId() == ":"){
        traciVehicle->setSpeed(13.8);
    }
}

bool TraCIDemo11p::otherVehiclesInOtherDirNotOptim(std::map<int, VehicleData> storage, int myId)
{
    double myHead = storage[myId].getHeading();

    int otherDirectionFounded = 0;
    for(std::map<int, VehicleData>::iterator it = storage.begin(); it != storage.end(); ++it){
        if(it->second.getOptimized() == 0 && it->second.getIntersectionFlag() == 0 && it->second.getHeading() != myHead){
            otherDirectionFounded +=1;
        }
    }

    if(otherDirectionFounded != 0){
        return true;
    }
    else{
        return false;
    }
}


void TraCIDemo11p::printGreen(std::vector<std::vector<Car>> chosenSol)
{

    if(semGreenNameFile == 0)
    {
        int optimCounter = m_storage[std::stoi(mobility->getExternalId())].getOptimizationCounter();

        // prendendo i risultati dell'ottimizzatore vado a vedere in che vettore il mio veicolo ha segnale diverso da 1, mi salvo l'iteratore
        // vado a vedere la sua distanza dall'inizio del vettore. Questo dato lo utilizzo per nominare il file del semaforo verde.
        // In questo modo e' come se andassi a prendere il cerchio di veicoli che hanno il verde.
        // Questo inisieme al contatore dell'ottimizzatore li suo per nominarmi i file, in modo da sapere che direzioni e che veicoli passano a che turno e quanto ci mettono.

        std::vector<std::vector<Car>>::iterator vectorPosition = chosenSol.end();

        for(std::vector<std::vector<Car>>::iterator it = chosenSol.begin(); it != chosenSol.end(); ++it)
        {
            for(std::vector<Car>::iterator sit = it->begin(); sit != it->end(); ++sit)
            {
                if(sit->getId() == std::stoi(mobility->getExternalId()) && sit->getSignal() != 1){
                    vectorPosition = it;
                    break;
                }
            }
        }

        if(vectorPosition != chosenSol.end()){
            int circleOfVeh = std::distance(chosenSol.begin(), vectorPosition);
            circleOfVeh += 1; // startCounting from 1

            //std::string Gpath = "C:/workspace_veins-4.7.1acc_id/log/semaphorePhase/Green";
            std::string Gpath = "E:/log/semaphorePhase/Green";
            Gpath += std::to_string(optimCounter) + "_" + std::to_string(circleOfVeh) + ".xml";

            std::string to_print = "VEHICLE STORAGE: " + mobility->getExternalId();
            wrt::w2StoragePhase(to_print, "", Gpath);
            //Gpath = "C:/workspace_veins-4.7.1acc_id/log/semaphorePhase/Green";
            Gpath = "E:/log/semaphorePhase/Green";
            wrt::printStorage(m_storage, Gpath, std::stoi(mobility->getExternalId()));
        }

        if(m_storage[std::stoi(mobility->getExternalId())].getIntersectionFlag() == 1){
            semGreenNameFile = 1;
        }
    }
}

void TraCIDemo11p::printRed(std::vector<std::vector<Car>> chosenSol)
{
    if(semRedNameFile == 0)
    {
        int optimCounter = m_storage[std::stoi(mobility->getExternalId())].getOptimizationCounter();
        std::vector<std::vector<Car>>::iterator vectorPosition = chosenSol.end();

        for(std::vector<std::vector<Car>>::iterator it = chosenSol.begin(); it != chosenSol.end(); ++it)
        {
            for(std::vector<Car>::iterator sit = it->begin(); sit != it->end(); ++sit)
            {
                if(sit->getId() == std::stoi(mobility->getExternalId()) && sit->getSignal() == 1){
                    vectorPosition = it;
                    break;
                }
            }
        }

        if(vectorPosition != chosenSol.end()){

            int circleOfVeh = std::distance(chosenSol.begin(), vectorPosition);
            circleOfVeh += 1; // startCounting from 1

            //std::string Rpath = "C:/workspace_veins-4.7.1acc_id/log/semaphorePhase/Red";
            std::string Rpath = "E:/log/semaphorePhase/Red";
            Rpath += std::to_string(optimCounter) + "_" + std::to_string(circleOfVeh) + ".xml";

            std::string to_print = "VEHICLE STORAGE: " + mobility->getExternalId();
            wrt::w2StoragePhase(to_print, "", Rpath);
            //Rpath = "C:/workspace_veins-4.7.1acc_id/log/semaphorePhase/Red";
            Rpath = "E:/log/semaphorePhase/Red";
            wrt::printStorage(m_storage, Rpath, std::stoi(mobility->getExternalId()));
        }
        if(m_storage[std::stoi(mobility->getExternalId())].getIntersectionFlag() == 1){
            semRedNameFile = 1;
        }
    }
}
