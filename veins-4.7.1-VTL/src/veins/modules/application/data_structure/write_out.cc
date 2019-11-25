#include "write_out.h"


void wrt::wout(std::string &text)
{
    std::string dataok, path1;
    // TODO: define the path for the log.xml file 
    path1 = "C:/log/log.xml";
    std::ofstream myfile(path1, std::ios::app);

    if (myfile.is_open()) {
        myfile << text << std::endl;
    }
    myfile.close();
}

void wrt::w2Storage(std::string &text, int id, std::string type)
{
    if(type == "")
    {
        std::string path;
        // TODO: define the path for the CarInternalStorage.xml file 
        path = "C:/log/CarInternalStorage";
        path += std::to_string(id) + ".xml";
        std::ofstream myfile(path, std::ios::app);

        if (myfile.is_open()) {
            myfile << text << std::endl;
        }
        myfile.close();
    }
    if(type == "csv")
    {
        std::string path;
        // TODO: define the path for the CarInternalStorage.csv file
        path = "C:/log/CarInternalStorage.csv";
        std::ofstream myfile(path, std::ios::app);

        if (myfile.is_open()) {
            myfile << text << std::endl;
        }
        myfile.close();
    }
}

void wrt::w2StoragePhase(std::string &text, std::string type, std::string path)
{
    if(type == "")
    {
        std::ofstream myfile(path, std::ios::app);

        if (myfile.is_open()) {
            myfile << text << std::endl;
        }
        myfile.close();
    }
    if(type == "csv")
    {
        std::ofstream myfile(path, std::ios::app);

        if (myfile.is_open()) {
            myfile << text << std::endl;
        }
        myfile.close();
    }
}

void wrt::w2path(std::string text, std::string path)
{
    std::ofstream myfile(path, std::ios::app);

    if (myfile.is_open()) {
        myfile << text << std::endl;
    }
    myfile.close();
}


void wrt::printStorage(std::map<int, VehicleData> storage, std::string path, int id, int mobilityID, std::string type)
{
    if(type == "text")
    {
        path += std::to_string(id) + ".xml";
        std::ofstream myfile(path, std::ios::app);


        myfile << "VID\t\tVehicle position\t\tVehicle speed\tVehicle Acceleration\tVehicle heading\t\t\t time\t\t\tIntersection Point\t\tDistance2Intersection\t\tTime2Inters\t\tLanePosition\t\tSignal\t\tRoadID\tOptimFlag\tOptimCount\tQueuePos"<<std::endl;

        for (std::map<int, VehicleData>::iterator it = storage.begin(); it != storage.end(); ++it)
        {

            myfile << std::fixed;
            myfile << std::setprecision(5);
            myfile << it->first << "\t\t";
            myfile << it->second.getPos().x << ", " << it->second.getPos().y << "\t\t";
            myfile << it->second.getVelocity() << "\t\t\t";
            myfile << it->second.getAcceleration() << "\t\t\t\t";
            myfile << it->second.getHeading() << " ";
            myfile << "Lf= " << it->second.getLeaderFlag() << "\t\t";
            myfile << it->second.getTime().str() << "\t\t";
            myfile << it->second.getIntersectionPoint().first << ", " << it->second.getIntersectionPoint().second << "\t\t";
            myfile << it->second.getDistance2Intersection() << " F = " << it->second.getIntersectionFlag() << "\t\t\t";
            myfile << it->second.getTime2Intersection() << "\t\t";
            myfile << it->second.getLanePosition() << "\t\t";
            myfile << it->second.getSignal() << "\t\t";
            myfile << it->second.getRoadId() << "\t\t\t";
            myfile << it->second.getOptimized() << "\t\t\t";
            myfile << it->second.getOptimizationCounter() << "\t\t\t";
            myfile << it->second.getQueuePosition() << std::endl;
        }


        if(mobilityID != -1)
        {
            //Print the direction of vehicles with which I got in contact to
            myfile << "seen directions: " << std::endl;
            std::vector<double> vector = storage[mobilityID].getHeadingVector();
            for (std::vector<double>::iterator vit = vector.begin(); vit != vector.end(); ++vit) {
                myfile << *vit << "\t";
            }

            //Print the vehicle's id with which I got in contact to, only in my direction

            myfile << "\nmy direction seen vehicle id:" <<std::endl;
            std::map<double, std::vector<int>> mapVehicle = storage[mobilityID].getVehicleMyDir();
            for(std::map<double, std::vector<int>>::iterator it = mapVehicle.begin(); it != mapVehicle.end(); ++it){
                myfile << "\theding: " << it->first << " -> ";
                for(std::vector<int>::iterator sit = it->second.begin(); sit != it->second.end(); ++sit){
                    myfile << *sit << " ";
                }
                myfile << std::endl;
            }

            
            // Print the leader messages sent and received
            std::map<int, std::string> leadersString = storage[mobilityID].getLeadersMap();
            myfile << "\nLeaderString:\n";
            for(std::map<int, std::string>::iterator it = leadersString.begin(); it != leadersString.end(); ++it)
            {
                myfile << it->first << ": " << it->second << std::endl;
            }

            // Print which coded message (sent by the leader or forwarded by other cars) a car has received
            myfile << "\n\nStored Messages for all vehicle in storage:" <<std::endl;
            for(std::map<int, VehicleData>::iterator it = storage.begin(); it != storage.end(); ++it)
            {
                myfile << "V: " << it->first << ":" << std::endl;
                std::vector<std::string> receivedString = storage[it->first].getAllOptimBroad();
                for(std::vector<std::string>::iterator sit = receivedString.begin(); sit != receivedString.end(); ++sit)
                {
                    myfile << *sit << std::endl;
                }
            }

            // Print the forwarded message by the vehicle
            myfile << "\nBROADCAST MESSAGE:" <<std::endl;
            myfile << storage[mobilityID].getBroadcastIdSet() << std::endl;



        }
        myfile << "\n\n";
        myfile.close();
    }

    if(type == "csv")
    {
        std::ofstream myfile(path, std::ios::app);
        myfile << "Vehicle ID,Vehicle position X,Vehicle position Y,Vehicle speed,Vehicle Acceleration,Vehicle heading,Leader Flag,time,Intersection Point,Distance2Intersection, Crossing Flag,Time2Inters,LanePosition,Signal,RoadID,Optimization Flag, Optimization Counter,Queue Position"<<std::endl;

        for (std::map<int, VehicleData>::iterator it = storage.begin(); it != storage.end(); ++it)
                {

                    myfile << std::fixed;
                    myfile << std::setprecision(5);
                    myfile << it->second.getId() << ",";
                    myfile << it->second.getPos().x << "," << it->second.getPos().y << ",";
                    myfile << it->second.getVelocity() << ",";
                    myfile << it->second.getAcceleration() << ",";
                    myfile << it->second.getHeading() << ",";
                    myfile << it->second.getLeaderFlag() << ",";
                    myfile << it->second.getTime().str() << ",";
                    myfile << it->second.getIntersectionPoint().first << "," ;
                    myfile << it->second.getDistance2Intersection() << "," << it->second.getIntersectionFlag() << ",";
                    myfile << it->second.getTime2Intersection() << ",";
                    myfile << it->second.getLanePosition() << ",";
                    myfile << it->second.getSignal() << ",";
                    myfile << it->second.getRoadId() << ",";
                    myfile << it->second.getOptimized() << ",";
                    myfile << it->second.getOptimizationCounter() << ",";
                    myfile << it->second.getQueuePosition() << std::endl;

                }
        

        if(mobilityID != -1)
                {
                    //Print the direction of vehicles with which I got in contact to
                    myfile << "seen directions: " << std::endl;
                    std::vector<double> vector = storage[mobilityID].getHeadingVector();
                    for (std::vector<double>::iterator vit = vector.begin(); vit != vector.end(); ++vit) {
                        myfile << *vit << ",";
                    }

                    //Print the vehicle's id with which I got in contact to, only in my direction

                    myfile << "\nmy direction seen vehicle id:" <<std::endl;
                    std::map<double, std::vector<int>> mapVehicle = storage[mobilityID].getVehicleMyDir();
                    for(std::map<double, std::vector<int>>::iterator it = mapVehicle.begin(); it != mapVehicle.end(); ++it){
                        myfile << "heding" << it->first << std::endl;
                        for(std::vector<int>::iterator sit = it->second.begin(); sit != it->second.end(); ++sit){
                            myfile << *sit << ",";
                        }
                        myfile << std::endl;
                    }


                    std::map<int, std::string> leadersString = storage[mobilityID].getLeadersMap();
                    myfile << "\nLeaderString:\n";
                    for(std::map<int, std::string>::iterator it = leadersString.begin(); it != leadersString.end(); ++it)
                    {
                        myfile << it->first << "," << it->second << std::endl;
                    }



                }
        myfile << "\n\n";
        myfile.close();
    }
}


