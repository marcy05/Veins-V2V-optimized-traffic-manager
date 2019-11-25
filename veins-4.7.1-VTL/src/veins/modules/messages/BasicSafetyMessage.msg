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

cplusplus {{
#include "veins/base/utils/Coord.h"
#include "veins/modules/messages/WaveShortMessage_m.h"
}}

class WaveShortMessage;
class noncobject Coord;

packet BasicSafetyMessage extends WaveShortMessage {
	Coord senderPosBSM;
	double senderSpeedBSM;
	
	//int nodeIndex;
	int nodeIDBSM;
	double headingBSM;
	double accelerationBSM;
	double intersectionXBSM;
	double intersectionYBSM;
	double yawBSM;
	simtime_t sendtimeBSM;
	
	double carLengthBSM;
	double carWidthBSM;
	// 1 if I already pass the intersection, 0 otherwise
	int intersectionFlagBSM; 
	
	double lanePositionBSM;
	
	//Broadcast my signal for direction intention
	int signalBSM;
	string roadID;
	
	string leaderStringBSM; // Used By leaders to agree on dataset
	string stringFlagBSM;	// Used to comunicate to all the other vehicle about the dataset to use to run the oprimization
	
	bool optimizationFlagBSM;
	int optimizationCounterBSM;
	
}
