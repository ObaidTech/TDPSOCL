#ifndef READINGDB_H
#define READINGDB_H
#include <reading.h>
#include <vector>
#include <particle.h>

using namespace std;

class ReadingDB
{
public:
    ReadingDB(int parID);
    int particleID;
    vector<Reading> readings;
    void addReading(int iterNo, double value);
};

#endif // READINGDB_H
