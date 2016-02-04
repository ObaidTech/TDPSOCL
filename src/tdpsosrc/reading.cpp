#include "reading.h"

Reading::Reading()
{
    this->type = ReadingType::Global;
}

Reading::Reading(int IterNo, double aValue)
{
    this->iterationNo = IterNo;
    this->value = aValue;
    this->type = ReadingType::Global;
}

Reading::Reading(int IterNo, double aValue, ReadingType t)
{
    this->iterationNo = IterNo;
    this->value = aValue;
    this->type = t;
}

Reading::Reading(int IterNo, double aValue, int parID)
{
    this->iterationNo = IterNo;
    this->value = aValue;
    this->particleID = parID;
    this->type = ReadingType::ParticleCost;
}


Reading::Reading(int IterNo, double aValue, int parID, ReadingType t)
{
    this->iterationNo = IterNo;
    this->value = aValue;
    this->particleID = parID;
    this->type = t;
}
