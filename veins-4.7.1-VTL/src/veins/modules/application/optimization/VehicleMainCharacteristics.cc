#include "VehicleMainCharacteristics.h"

void VehicleMainChar::initializer(int id, int queuePosition, int signal, double heading)
{
    m_id = id;
    m_queuePosition = queuePosition;
    m_signal = signal;
    m_heading = heading;
}

/*
bool VehicleMainChar::isEqual(VehicleMainChar first, VehicleMainChar second)
{
    if(first.m_heading == second.m_heading && first.m_id == second.m_id && first.m_queuePosition == second.m_queuePosition && first.m_signal == second.m_signal){
        return true;
    }
    return false;
}*/

bool VehicleMainChar::isPresent(std::vector<VehicleMainChar> vector, VehicleMainChar item)
{
    for(std::vector<VehicleMainChar>::iterator it = vector.begin(); it != vector.end(); ++it)
    {
        if(*it == item)
        {
            return true;
        }
    }
    return false;
}

bool VehicleMainChar::operator==(const VehicleMainChar & op)
{
    if (m_id == op.m_id && m_queuePosition == op.m_queuePosition && m_signal == op.m_signal && m_heading == op.m_heading) {
        return true;
    }
    return false;
}


