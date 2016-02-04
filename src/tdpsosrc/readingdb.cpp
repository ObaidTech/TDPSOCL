#include "readingdb.h"

ReadingDB::ReadingDB(int parID)
{
    this->particleID = parID;
}

void ReadingDB::addReading(int iterNo, double value)
{
    Reading r(iterNo, value, this->particleID);
    this->readings.push_back(r);
}
