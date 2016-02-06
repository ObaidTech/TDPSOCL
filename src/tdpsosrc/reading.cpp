#include "reading.h"

Reading::Reading()
{
    this->type = Global;
}

Reading::Reading(int IterNo, double aValue)
{
    this->iterationNo = IterNo;
    this->value = aValue;
    this->type = Global;
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
    this->type = ParticleCost;
}


Reading::Reading(int IterNo, double aValue, int parID, ReadingType t)
{
    this->iterationNo = IterNo;
    this->value = aValue;
    this->particleID = parID;
    this->type = t;
}
