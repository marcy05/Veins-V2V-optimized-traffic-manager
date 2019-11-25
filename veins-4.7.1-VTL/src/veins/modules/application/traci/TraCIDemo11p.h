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

/**
 * @brief
 * A tutorial demo for TraCI. When the car is stopped for longer than 10 seconds
 * it will send a message out to other cars containing the blocked road id.
 * Receiving cars will then trigger a reroute via TraCI.
 * When channel switching between SCH and CCH is enabled on the MAC, the message is
 * instead send out on a service channel following a WAVE Service Advertisement
 * on the CCH.
 *
 * @author Christoph Sommer : initial DemoApp
 * @author David Eckhoff : rewriting, moving functionality to BaseWaveApplLayer, adding WSA
 *
 */


#ifndef TraCIDemo11p_H
#define TraCIDemo11p_H

#include "veins/modules/application/ieee80211p/BaseWaveApplLayer.h"
#include "veins/modules/application/data_structure/write_out.h"
#include "../optimization/xmlReader/readingXML.h"
#include "math.h"
#include <vector>
#include <time.h>
#include <veins/modules/application/optimization/RunOptimization.h>
#include "../optimization/hexManagement.h"
#include "../optimization/VehicleMainCharacteristics.h"


#define INTERSECTION_SIZE 27.2
#define LANE_LENGTH 995.25
#define DENSITY_THRESHOLD 1




class TraCIDemo11p : public BaseWaveApplLayer, public VehicleMainChar {
	public:
		virtual void initialize(int stage);
		//std::string m_storagePath = "C:/workspace_veins-4.7.1acc_id/log/CarInternalStorage";
		std::string m_storagePath = "e:/log/CarInternalStorage";
		//std::string m_storagePathCSV = "C:/workspace_veins-4.7.1acc_id/log/CarInternalStorage.csv";
		std::string m_storagePathCSV = "e:/log/CarInternalStorage.csv";

	protected:
		simtime_t lastDroveAt;
		bool sentMessage;
		int currentSubscribedServiceId;

	private:
		int m_beaconReceived;

		//Distance from the center of the intersection to the stop lane
		double intersectionRadius = 4.9;
		int semaphore2 = 0; // used in checkallSignals


	// semaphores to execute only one time the optimizer functions
	private:
		int semPrepareLeaderData = 0; //Set at 55.5m from the intersection
		int semLeaderReceiving = 0; // 1 if leader complete to receive messages
		int semReadyToBroadcast = 0;
		int semaphoreReadingOk = 0;


	private:
		std::vector<VehicleMainChar> Ev = {};
        std::vector<VehicleMainChar> Nv = {};
        std::vector<VehicleMainChar> Wv = {};
        std::vector<VehicleMainChar> Sv = {};


        //For leader election (heading, (id, distance2intersection))
        std::map<double, std::vector<double>> distanceByDirection = {};

	private:
		//time variable
		int m_timeSemaphore = 0;

	private:
		int initsem = 0;
		std::map<std::array<double, 4>, std::vector<std::array<std::pair<int, int>, 4>>> mapDataset;

		int m_invalHeadingCounterAll = 0;
		int m_invalHeadingCounterMyDir = 0;

		int vehBeforeMe = -1;
		int semaphoreBeforeMe = 0;

	private:
		int semVTL = 0; // Set at 100m from the intersection only among leaders
		int optimizerFlagStart = 0;
		std::string under100ToBitString = "";

		std::vector<std::vector<Car>> testedSolution;
		std::map<int, std::vector<std::vector<std::vector<Car>>>> fullSolutions;

		std::vector<VehicleMainChar> vehEReceived = {};
		std::vector<VehicleMainChar> vehNReceived = {};
		std::vector<VehicleMainChar> vehWReceived = {};
		std::vector<VehicleMainChar> vehSReceived = {};


		std::map<int, VehicleMainChar> receivedBroadcastMap = {}; //data on which it's done the optimization

		int leadersEqualityCounter = 0;
        int semCorrisponMap = 0;


		std::vector<std::vector<Car>> chosenSolution = {};

		int semPrint = 0;


		double myheading = -1;
		int queuePos = -1;

		int setStopflag = 0;
		double timeStopped = -1;
		int semSetTimeStop = 0;

		int semGreenNameFile = 0;
		int semRedNameFile = 0;

		int semGreen = 0;

		//Set when the leader broadcast the message, if no vehicles reply with a string with its id, the flag allow to rebroadcast it's message
		int leaderBroadcastOptimizationFlag = 0;
/*
		int printGreenFlag = 0;
		std::string greenPath = "C:/workspace_veins-4.7.1acc_id/log/semaphorePhase/Green";


		int printRedFlag = 0;
		std::string redPath = "C:/workspace_veins-4.7.1acc_id/log/semaphorePhase/Red";

*/

	protected:
        virtual void onWSM(WaveShortMessage* wsm);
        virtual void onWSA(WaveServiceAdvertisment* wsa);

        virtual void handleSelfMsg(cMessage* msg);
		virtual void handlePositionUpdate(cObject* obj);

		// Manage the beacon received messages
		virtual void onBeacon(BasicSafetyMessage* bsm);

		// Allow to update the m_storage data with the current information
		virtual void updateMyData();

		// Update the m_storage variable with the data received from the message
		virtual void updateStorage(BasicSafetyMessage* bsm);

		// It can compute the intersection, now the intersection position it's set manually but it's thought to obtain it from a map analysis
		virtual void computeIntersection(int id);

		/* Compute: - the distance from the intersection for each vehicle in the storage
                    - set the flag to signal that the vehicle is crossing the intersection
                    - compute the time to intersection*/
		virtual void wrtIntersection();

		// Detect which is the leader vehicle in it's own direction
		virtual void leader();

		//Managing vehicles from BSMs
		virtual void manageSeenVehicles(BasicSafetyMessage* bsm);

		// Detect all seen direction
		virtual void myHeadingVector(BasicSafetyMessage* bsm);

		// Collect all vehicles in my direction
		virtual void vehicleInMyDir(BasicSafetyMessage *bsm);

		// Collect all seen vehicles in any direction
		virtual void allSeenVehicle(BasicSafetyMessage*bsm);



		virtual void leaderCheckOptimization(BasicSafetyMessage* bsm);

		virtual void allVehicleCheckOptimization(BasicSafetyMessage* bsm);

		//knowing the number of vehicles which have signal != 0 this function can be uses to print the storage of the vehicles to a specific path when the vehicle knows the
		// signal of all the other correctly.
		virtual void checkallSignals(std::string path);

		virtual void prepareLeaderData();

		virtual void printIdSigna();





		virtual void speedManaging();

		virtual bool amILeader();
		virtual void leaderReceiving();


		virtual void speedAproachingIntersectionManagement(std::map<int, VehicleData> m_storage, int myId);

		virtual void printGreen(std::vector<std::vector<Car>> chosenSol);
		virtual void printRed(std::vector<std::vector<Car>> chosenSol);

		virtual bool allOtherLeadersRespondMe(std::map<int, std::string> leadersMap, int myId);

		virtual bool otherVehiclesInOtherDirNotOptim(std::map<int, VehicleData> storage, int myId);

		//virtual void setOptimizationCounter(BasicSafetyMessage* bsm, std::map<int, VehicleData>& storage);

};

#endif
