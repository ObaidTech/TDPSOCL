//=================================================================================================
// Name        : Particle.cpp
// Author      : Muhammad Obaidullah
// Version     : 0.1
// Copyright   : Electrical & Computer Engineering, Ryerson University ©2015
// Description : Particle class which stores an intermediate core arrangement solution
//=================================================================================================

#include "particle.h"

using namespace std;

// ---------------------------------------------------------------------------------------------------------------------------
//
//	Function:		Particle CONSTRUCTOR
// 	Purpose:		Constructs an object of class particle to store solution, move in solution space and evaluate it's cost
// 	Parameters: 	particleID - A unique identifier number for the particle
//					size - Size of the particle/solution
//					initialCondition - What are the initial positions of the cores. -1 for not assigned.
//	Returns:		nothing
//
// ---------------------------------------------------------------------------------------------------------------------------
Particle::Particle(int particleID, int size, std::vector<int> initialCondition) {
	// Set the particle ID the same as the passed one
	ParticleID = particleID;
	// Set the particle size same as the passed size
	Size = size;
	// Initialize the CoreArrangement array size same as the passed size
    CoreArrangement.resize(size,-1);
	// How many slots are empty ?
	int NumOfEmptySlots = 0;
	// Check the size of initial condition, it should be the same as the passed size
	if(initialCondition.size() != size)
	{
		cout << "Initial Condition size does not match the particle size. Initial Condition Size: " << initialCondition.size() << " Expected Size: " << Size << endl;
		return;
	}
	// Make CoreArrangement conform to the initial condition
	for(int i = 0; i < Size; i++)
	{
		// If the value is not less than 0, then make the initial core arrangement same as the initial condition.
		if(initialCondition[i] >= 0)
		{
			CoreArrangement[i] = initialCondition[i];
		}
		else
		{
			// This slot is empty, so mark it negative and increment empty slot counter
			CoreArrangement[i] = -1;
			NumOfEmptySlots++;
		}
	}
    std::vector<int> remainingCores(NumOfEmptySlots+1,-1);
    std::vector<int> remainingCorePositions(NumOfEmptySlots+1,-1);
	int cursor = 0;
	for(int i = 0; i < size; i++)
	{
		if(CoreArrangement[i] < 0)
		{
			remainingCorePositions[cursor++] = i;
		}
	}
	cursor = 0;
	// Check if core is mapped already
	for(int i = 0; i < size; i++)
	{
		bool coreFound = false;
		for(int j = 0; j < size; j++)
		{
			if(CoreArrangement[j] == i)
			{
				// This core has been mapped already, move on to check next core
				coreFound = true;
				break;
			}
		}
		if(!coreFound)
		{
			remainingCores[cursor++] = i;
		}
	}
	// Shuffle the positions of remaining (unmapped) cores to make them not in any order
	random_shuffle(&remainingCores[0],&remainingCores[NumOfEmptySlots]);
	// Now put shuffled remaining cores into empty core positions
	for(int i = 0; i < NumOfEmptySlots; i++)
	{
		CoreArrangement[remainingCorePositions[i]] = remainingCores[i];
    }

    // No resetting all costs. Beacuse this is a new object
    this->CurrentCost = -1;
    this->LocalBestCost = -1;
}

// ---------------------------------------------------------------------------------------------------------------------------
//
//	Function:		Particle DESTRUCTOR
// 	Purpose:		Destroys the a particle object
// 	Parameters: 	nothing
//	Returns:		nothing
//
// ---------------------------------------------------------------------------------------------------------------------------
Particle::~Particle() {
	// TODO Auto-generated destructor stub
}

// ---------------------------------------------------------------------------------------------------------------------------
//
//	Function:		Particle CONSTRUCTOR
// 	Purpose:		Constructs an object of class particle to store solution, move in solution space and evaluate it's cost
// 	Parameters: 	nothing
//	Returns:		nothing
//
// ---------------------------------------------------------------------------------------------------------------------------
Particle::Particle() {
    // TODO Auto-generated destructor stub
}

// ---------------------------------------------------------------------------------------------------------------------------
//
//	Function:		toString
// 	Purpose:		Creates a string to briefly describe the particle object
// 	Parameters: 	nothing
//	Returns:		Printable string describing the particle
//
// ---------------------------------------------------------------------------------------------------------------------------
string Particle::toString()
{
    std::stringstream ss;
    ss << endl << "========================================================================" << endl;
    ss << "Particle ID: " << ParticleID << endl;
    ss << "Current Cost: " << CurrentCost << endl;
    ss << "Local Best Cost: " << LocalBestCost << endl;
    ss << "------------------------------------------------------------------------" << endl;
    ss << "Size: " << Size << endl;
    ss << "Core Arrangement: { ";
    if(Size > 2)
    {
        for(int i = 0; i < Size - 1; i++)
        {
            ss << CoreArrangement[i] << ", ";
        }
        ss << CoreArrangement[Size-1] << " }" << endl;
    }
    else if(Size == 2)
    {
        ss << CoreArrangement[0] << ", " << CoreArrangement[1] << " }" << endl;
    }
    else
    {
        ss << CoreArrangement[0] << " }" << endl;
    }
    ss << "========================================================================" << endl;
    return ss.str();
}


Particle Particle::deepClone()
{
    Particle newParticle;
    newParticle.CoreArrangement = CoreArrangement;
    newParticle.CurrentCost = CurrentCost;
    newParticle.LocalBestCost = LocalBestCost;
    newParticle.LocalBestCoreArrangement = LocalBestCoreArrangement;
    newParticle.ParticleID = ParticleID;
    newParticle.Size = Size;
    return newParticle;
}

