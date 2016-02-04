#ifndef READING_H
#define READING_H

using namespace std;

enum ReadingType
{
    Global,
    Local,
    ParticleCost
};

class Reading
{
public:
    Reading();
    int iterationNo;
    double value;
    int particleID;
    ReadingType type;
    Reading(int IterNo, double aValue, int parID);
    Reading(int IterNo, double aValue, int parID, ReadingType t);
    Reading(int IterNo, double aValue, ReadingType t);
    Reading(int IterNo, double aValue);
};

#endif // READING_H
