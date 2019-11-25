#ifndef VEHICLEMAINCHARACTERISTICS_H
#define VEHICLEMAINCHARACTERISTICS_H
#include <vector>
//#include "../data_structure/VehicleData.h"

struct VehicleMainChar
{
    int m_id;
    int m_queuePosition;
    int m_signal;
    double m_heading;
    bool optimized = false;

    VehicleMainChar()
    {
    }
    VehicleMainChar(int id, int queuePos, int signal, double heading){
        m_id = id;
        m_queuePosition = queuePos;
        m_signal = signal;
        m_heading = heading;
    }

    void initializer(int id, int queuePosition, int signal, double heading);
    //bool isEqual(VehicleMainChar first, VehicleMainChar second);
    bool isPresent(std::vector<VehicleMainChar> vector, VehicleMainChar item);

    bool operator==(const VehicleMainChar& op);
};




#endif //VEHICLEMAINCHARACTERISTICS_H
