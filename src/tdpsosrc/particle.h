//=================================================================================================
// Name        : Particle.h
// Author      : Muhammad Obaidullah
// Version     : 0.1
// Copyright   : Electrical & Computer Engineering, Ryerson University ©2015
// Description : Particle class which stores an intermediate core arrangement solution
//=================================================================================================

#ifndef PARTICLE_H_
#define PARTICLE_H_
#include <vector>
#include <iostream>
#include <algorithm>
#include <sstream>

using namespace std;

class Particle {
public:
	// BEGIN - Functions
    Particle(int particleID, int size, std::vector<int> initialCondition);
    Particle();
    virtual ~Particle();
    string toString();
    Particle deepClone();
	// END - Functions

    // BEGIN - Properties
    double LocalBestCost;
    vector<int> LocalBestCoreArrangement;
    double CurrentCost;
	int ParticleID;
	int Size;
    vector<int> CoreArrangement;
	// END - Properties
};

#endif /* PARTICLE_H_ */
