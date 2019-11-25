

#!/usr/bin/env python
"""
@file    runner.py
@author  Marcello Sgarbi
@date    10/12/2018
@version $Id: runner.py  2018-10-12 
@version $Id: runner3.py  2018-10-19

This script is a test runner for TraCI implementation. Check for new version or updates
"""

##########################################
#             DECLARATION
##########################################

from __future__ import absolute_import
from __future__ import print_function

import os
import sys
import optparse
# import the virtual traffic light, the route generator and the log destination
#from Functions import rou_generator, printDirectory1
#import VirtualTrafficLight as VTL

sys.path.insert(0, 'C:/veins-veins-4.7.1_terzo/examples/veins')

if 'SUMO_HOME' in os.environ:
    tools = os.path.join(os.environ['SUMO_HOME'], 'tools')
    sys.path.append(tools)
else:
    sys.exit("please declare environment variable 'SUMO_HOME' ")

from sumolib import checkBinary
import traci as tc

def get_options():
    optParser = optparse.OptionParser()
    optParser.add_option("--nogui", action="store_true",
                         default=False, help="run the commandline version of sumo")
    options, args = optParser.parse_args()
    return options

def printOut(toprint):
    toprint = str(toprint)
    file = open('sumoLog.txt','a')
    file.write(toprint + '\n')
    file.close()

def run():
    """execute the TraCI control loop"""
    step = 0    
    

    vehicle_list = list()
    
    while tc.simulation.getMinExpectedNumber() > 0:
        tc.simulationStep()
        
        vehicle_list = tc.vehicle.getIDList()
        start = 0
        end = 0
        startPos = 0.0
        endPos = 0.0
        if("0" in vehicle_list):
            if(tc.vehicle.getSpeed("0") > 13.5 and step > 4 ):
                startPos = tc.vehicle.getLanePosition("0")
                tc.vehicle.setSpeed("0", 0)
                start = tc.simulation.getCurrentTime()

            if(tc.vehicle.getSpeed("0") < 1):
                end = tc.simulation.getCurrentTime()
                endPos = tc.vehicle.getLanePosition("0")
                pri = "distance to stop: " + str(endPos-startPos)
                printOut(pri)
                pri2 = "time to stop: " + str(end-start)
                printOut(pri2)
                

        
        step += 1
    tc.close()
    sys.stdout.flush()


##########################################
#                  MAIN
##########################################

if __name__ == "__main__":
    
    
    # clear print out file
    open('log.txt','w')

    options = get_options()

    # this script has been called from the command line. It will start sumo as a
    # server, then connect and run
    if options.nogui:
        sumoBinary = checkBinary('sumo')
    else:
        sumoBinary = checkBinary('sumo-gui')


    # this is the normal way of using traci. sumo is started as a
    # subprocess and then the python script connects and runs
    tc.start([sumoBinary, "-c", "Cross_intersection.sumo.cfg",
                             "--tripinfo-output", "tripinfo.xml"])
    run()

