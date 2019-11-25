//
// Copyright (C) 2011 David Eckhoff <eckhoff@cs.fau.de>
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

#include "veins/modules/application/ieee80211p/BaseWaveApplLayer.h"
#include "veins/modules/application/data_structure/VehicleData.h"

const simsignalwrap_t BaseWaveApplLayer::mobilityStateChangedSignal = simsignalwrap_t(MIXIM_SIGNAL_MOBILITY_CHANGE_NAME);
const simsignalwrap_t BaseWaveApplLayer::parkingStateChangedSignal = simsignalwrap_t(TRACI_SIGNAL_PARKING_CHANGE_NAME);

void BaseWaveApplLayer::initialize(int stage) {
    BaseApplLayer::initialize(stage);

    if (stage==0) {

        //initialize pointers to other modules
        if (FindModule<TraCIMobility*>::findSubModule(getParentModule())) {
            mobility = TraCIMobilityAccess().get(getParentModule());
            traci = mobility->getCommandInterface();
            traciVehicle = mobility->getVehicleCommandInterface();
        }
        else {
            traci = NULL;
            mobility = NULL;
            traciVehicle = NULL;
        }

        annotations = AnnotationManagerAccess().getIfExists();
        ASSERT(annotations);

        mac = FindModule<WaveAppToMac1609_4Interface*>::findSubModule(
                getParentModule());
        assert(mac);

        // It's the id which the simulator generate corresponding to a particular node. It is not the id of the route file
        myId = getParentModule()->getId();

        //get the Index shown in the simulation, but it's not the ID assigned into the route file
        nodeIndex = getParentModule()->getIndex();

        //Get the correct id of vehicles declared into the route file
        nodeID = std::stoi(mobility->getExternalId());


        //read parameters
        headerLength = par("headerLength").longValue();
        sendBeacons = par("sendBeacons").boolValue();
        beaconLengthBits = par("beaconLengthBits").longValue();
        beaconUserPriority = par("beaconUserPriority").longValue();
        beaconInterval =  par("beaconInterval");

        dataLengthBits = par("dataLengthBits").longValue();
        dataOnSch = par("dataOnSch").boolValue();
        dataUserPriority = par("dataUserPriority").longValue();

        wsaInterval = par("wsaInterval").doubleValue();
        communicateWhileParked = par("communicateWhileParked").boolValue();
        currentOfferedServiceId = -1;

        isParked = false;


        findHost()->subscribe(mobilityStateChangedSignal, this);
        findHost()->subscribe(parkingStateChangedSignal, this);

        sendBeaconEvt = new cMessage("beacon evt", SEND_BEACON_EVT);
        sendWSAEvt = new cMessage("wsa evt", SEND_WSA_EVT);

        generatedBSMs = 0;
        generatedWSAs = 0;
        generatedWSMs = 0;
        receivedBSMs = 0;
        receivedWSAs = 0;
        receivedWSMs = 0;
    }
    else if (stage == 1) {
        //simulate asynchronous channel access

        if (dataOnSch == true && !mac->isChannelSwitchingActive()) {
            dataOnSch = false;
            std::cerr << "App wants to send data on SCH but MAC doesn't use any SCH. Sending all data on CCH" << std::endl;
        }
        simtime_t firstBeacon = simTime();

        if (par("avoidBeaconSynchronization").boolValue() == true) {

            simtime_t randomOffset = dblrand() * beaconInterval;
            firstBeacon = simTime() + randomOffset;

            if (mac->isChannelSwitchingActive() == true) {
                if ( beaconInterval.raw() % (mac->getSwitchingInterval().raw()*2)) {
                    std::cerr << "The beacon interval (" << beaconInterval << ") is smaller than or not a multiple of  one synchronization interval (" << 2*mac->getSwitchingInterval() << "). "
                            << "This means that beacons are generated during SCH intervals" << std::endl;
                }
                firstBeacon = computeAsynchronousSendingTime(beaconInterval, type_CCH);
            }

            if (sendBeacons) {
                scheduleAt(firstBeacon, sendBeaconEvt);
            }
        }
    }
}

simtime_t BaseWaveApplLayer::computeAsynchronousSendingTime(simtime_t interval, t_channel chan) {

    /*
     * avoid that periodic messages for one channel type are scheduled in the other channel interval
     * when alternate access is enabled in the MAC
     */

    simtime_t randomOffset = dblrand() * beaconInterval;
    simtime_t firstEvent;
    simtime_t switchingInterval = mac->getSwitchingInterval(); //usually 0.050s
    simtime_t nextCCH;

    /*
     * start event earliest in next CCH (or SCH) interval. For alignment, first find the next CCH interval
     * To find out next CCH, go back to start of current interval and add two or one intervals
     * depending on type of current interval
     */

    if (mac->isCurrentChannelCCH()) {
        nextCCH = simTime() - SimTime().setRaw(simTime().raw() % switchingInterval.raw()) + switchingInterval*2;
    }
    else {
        nextCCH = simTime() - SimTime().setRaw(simTime().raw() %switchingInterval.raw()) + switchingInterval;
    }

    firstEvent = nextCCH + randomOffset;

    //check if firstEvent lies within the correct interval and, if not, move to previous interval

    if (firstEvent.raw()  % (2*switchingInterval.raw()) > switchingInterval.raw()) {
        //firstEvent is within a sch interval
        if (chan == type_CCH) firstEvent -= switchingInterval;
    }
    else {
        //firstEvent is within a cch interval, so adjust for SCH messages
        if (chan == type_SCH) firstEvent += switchingInterval;
    }

    return firstEvent;
}

void BaseWaveApplLayer::populateWSM(WaveShortMessage* wsm, int rcvId, int serial) {
    //std::string path = "C:/workspace_veins-4.7.1acc_id/log/recap" + mobility->getExternalId() + ".xml";
    //std::ofstream recFile(path, std::ios::app);

    wsm->setWsmVersion(1);
    wsm->setTimestamp(simTime());
    wsm->setSenderAddress(myId);
    wsm->setRecipientAddress(rcvId);
    wsm->setSerial(serial);
    wsm->setBitLength(headerLength);


    if (BasicSafetyMessage* bsm = dynamic_cast<BasicSafetyMessage*>(wsm) ) {

        bsm->setSenderPosBSM(curPosition);
        bsm->setSenderSpeedBSM(traciSpeed);
        bsm->setPsid(-1);
        bsm->setChannelNumber(Channels::CCH);
        bsm->addBitLength(beaconLengthBits);
        wsm->setUserPriority(beaconUserPriority);

        //bsm->setNodeIndex(nodeIndex);
        bsm->setNodeIDBSM(nodeID);
        bsm->setSendtimeBSM(simTime());
        bsm->setAccelerationBSM(m_storage[nodeID].getAcceleration());
        bsm->setIntersectionXBSM(m_storage[nodeID].getIntersectionPoint().first);
        bsm->setIntersectionYBSM(m_storage[nodeID].getIntersectionPoint().second);
        bsm->setHeadingBSM(m_storage[nodeID].getHeading());
        bsm->setIntersectionFlagBSM(m_storage[nodeID].getIntersectionFlag());
        bsm->setLanePositionBSM(m_storage[nodeID].getLanePosition());
        bsm->setSignalBSM(m_storage[nodeID].getSignal());
        bsm->setRoadID(m_storage[nodeID].getRoadId().c_str());

        bsm->setOptimizationFlagBSM(m_storage[nodeID].getOptimized());
        bsm->setOptimizationCounterBSM(m_storage[nodeID].getOptimizationCounter());

        //Only if the considered vehicle is a leader
        if(nodeID == m_storage[nodeID].getLeaderFlag())
        {
            //recFile << "INSIDE FIRST IF" << std::endl;
            if(m_storage[nodeID].getDistance2Intersection() < 100 )
            {
                //recFile << "INSIDE SECOND IF" << std::endl;
                if(allowedToSend == 0 && m_storage[nodeID].getLeadersMapElement(nodeID).size() > 0){
                    //recFile << "INSIDE THIRD IF" << std::endl;
                    bsm->setLeaderStringBSM(m_storage[nodeID].getLeadersMapElement(nodeID).c_str());

                    //recFile << "Base layer " << nodeID << " \nsend: "<< m_storage[nodeID].getLeadersMapElement(nodeID) << std::endl;
                    if(m_storage[nodeID].getRoadId()[0] == ':'){
                        m_storage[nodeID].setLeadersMapElement(nodeID, "");
                        allowedToSend = 1; // If I'm the leader, I have broadcast the message and I'm crossing the intersection, I stop broadcasting the optimization
                    }
                }
            }

            //std::cout << m_storage[nodeID].getLeadersMapElement(nodeID).c_str() << std::endl;
        }

        //All vehicles
        if(std::strncmp(m_storage[nodeID].getBroadcastIdSet().c_str(), "",1) != 0)
        {
            std::string toBroadcast = m_storage[nodeID].getBroadcastIdSet();
            if(allowedToSend == 0 && isMyIdInString(toBroadcast, nodeID) == true ){
                bsm->setStringFlagBSM(m_storage[nodeID].getBroadcastIdSet().c_str());
                if(m_storage[nodeID].getRoadId()[0] == ':'){
                    allowedToSend = 1;
                }
            }
        }
        //bsm->setTime2intersection(m_storage[nodeIndex].getTime2Intersection());


    }
    else if (WaveServiceAdvertisment* wsa = dynamic_cast<WaveServiceAdvertisment*>(wsm)) {
        wsa->setChannelNumber(Channels::CCH);
        wsa->setTargetChannel(currentServiceChannel);
        wsa->setPsid(currentOfferedServiceId);
        wsa->setServiceDescription(currentServiceDescription.c_str());
    }
    else {
        if (dataOnSch) wsm->setChannelNumber(Channels::SCH1); //will be rewritten at Mac1609_4 to actual Service Channel. This is just so no controlInfo is needed
        else wsm->setChannelNumber(Channels::CCH);
        wsm->addBitLength(dataLengthBits);
        wsm->setUserPriority(dataUserPriority);
    }
}

void BaseWaveApplLayer::receiveSignal(cComponent* source, simsignal_t signalID, cObject* obj, cObject* details) {
    Enter_Method_Silent();
    if (signalID == mobilityStateChangedSignal) {
        handlePositionUpdate(obj);
    }
    else if (signalID == parkingStateChangedSignal) {
        handleParkingUpdate(obj);
    }
}

void BaseWaveApplLayer::handlePositionUpdate(cObject* obj) {
    ChannelMobilityPtrType const mobility = check_and_cast<ChannelMobilityPtrType>(obj);
    curPosition = mobility->getCurrentPosition();
    curSpeed = mobility->getCurrentSpeed();
    traciSpeed = traciVehicle->getSpeed();
}

void BaseWaveApplLayer::handleParkingUpdate(cObject* obj) {
    //this code should only run when used with TraCI
    isParked = mobility->getParkingState();
    if (communicateWhileParked == false) {
        if (isParked == true) {
            (FindModule<BaseConnectionManager*>::findGlobalModule())->unregisterNic(this->getParentModule()->getSubmodule("nic"));
        }
        else {
            Coord pos = mobility->getCurrentPosition();
            (FindModule<BaseConnectionManager*>::findGlobalModule())->registerNic(this->getParentModule()->getSubmodule("nic"), (ChannelAccess*) this->getParentModule()->getSubmodule("nic")->getSubmodule("phy80211p"), &pos);
        }
    }
}

void BaseWaveApplLayer::handleLowerMsg(cMessage* msg) {

    WaveShortMessage* wsm = dynamic_cast<WaveShortMessage*>(msg);
    ASSERT(wsm);

    if (BasicSafetyMessage* bsm = dynamic_cast<BasicSafetyMessage*>(wsm)) {
        receivedBSMs++;
        onBSM(bsm);
        onBeacon(bsm);
    }
    else if (WaveServiceAdvertisment* wsa = dynamic_cast<WaveServiceAdvertisment*>(wsm)) {
        receivedWSAs++;
        onWSA(wsa);
    }
    else {
        receivedWSMs++;
        onWSM(wsm);
    }

    delete(msg);
}

void BaseWaveApplLayer::handleSelfMsg(cMessage* msg) {
    switch (msg->getKind()) {
    case SEND_BEACON_EVT: {
        BasicSafetyMessage* bsm = new BasicSafetyMessage();
        populateWSM(bsm);
        sendDown(bsm);
        scheduleAt(simTime() + beaconInterval, sendBeaconEvt);
        break;
    }
    case SEND_WSA_EVT:   {
        WaveServiceAdvertisment* wsa = new WaveServiceAdvertisment();
        populateWSM(wsa);
        sendDown(wsa);
        scheduleAt(simTime() + wsaInterval, sendWSAEvt);
        break;
    }
    default: {
        if (msg)
            DBG_APP << "APP: Error: Got Self Message of unknown kind! Name: " << msg->getName() << endl;
        break;
    }
    }
}

void BaseWaveApplLayer::finish() {
    recordScalar("generatedWSMs",generatedWSMs);
    recordScalar("receivedWSMs",receivedWSMs);

    recordScalar("generatedBSMs",generatedBSMs);
    recordScalar("receivedBSMs",receivedBSMs);

    recordScalar("generatedWSAs",generatedWSAs);
    recordScalar("receivedWSAs",receivedWSAs);
}

BaseWaveApplLayer::~BaseWaveApplLayer() {
    cancelAndDelete(sendBeaconEvt);
    cancelAndDelete(sendWSAEvt);
    findHost()->unsubscribe(mobilityStateChangedSignal, this);
}

void BaseWaveApplLayer::startService(Channels::ChannelNumber channel, int serviceId, std::string serviceDescription) {
    if (sendWSAEvt->isScheduled()) {
        error("Starting service although another service was already started");
    }

    mac->changeServiceChannel(channel);
    currentOfferedServiceId = serviceId;
    currentServiceChannel = channel;
    currentServiceDescription = serviceDescription;

    simtime_t wsaTime = computeAsynchronousSendingTime(wsaInterval, type_CCH);
    scheduleAt(wsaTime, sendWSAEvt);

}

void BaseWaveApplLayer::stopService() {
    cancelEvent(sendWSAEvt);
    currentOfferedServiceId = -1;
}

void BaseWaveApplLayer::sendDown(cMessage* msg) {
    checkAndTrackPacket(msg);
    BaseApplLayer::sendDown(msg);
}

void BaseWaveApplLayer::sendDelayedDown(cMessage* msg, simtime_t delay) {
    checkAndTrackPacket(msg);
    BaseApplLayer::sendDelayedDown(msg, delay);
}

void BaseWaveApplLayer::checkAndTrackPacket(cMessage* msg) {
    if (isParked && !communicateWhileParked) error("Attempted to transmit a message while parked, but this is forbidden by current configuration");

    if (dynamic_cast<BasicSafetyMessage*>(msg)) {
        DBG_APP << "sending down a BSM" << std::endl;
        generatedBSMs++;
    }
    else if (dynamic_cast<WaveServiceAdvertisment*>(msg)) {
        DBG_APP << "sending down a WSA" << std::endl;
        generatedWSAs++;
    }
    else if (dynamic_cast<WaveShortMessage*>(msg)) {
        DBG_APP << "sending down a wsm" << std::endl;
        generatedWSMs++;
    }
}


