//=================================================================================================
// Name        : oboptimizer.cpp
// Author      : Muhammad Obaidullah
// Version     : 0.1
// Copyright   : Electrical & Computer Engineering, Ryerson University ©2015
// Description : OBOptimizer singleton class which allows many different optimization techniques
//               to be run on the application object
//=================================================================================================
#include "oboptimizer.h"

// Global static pointer used to ensure a single instance of the class.
OBOptimizer* OBOptimizer::m_pInstance = NULL;

OBOptimizer* OBOptimizer::Instance()
{
    if (m_pInstance == NULL)   // Only allow one instance of class to be generated.
    {
        m_pInstance = new OBOptimizer();
    }
    return m_pInstance;

}

OBOptimizer::OBOptimizer()
{
    ParticleInertia = 0.1;
    ParticleSelfConfidence = 0.4;
    SwarmConfidence = 0.1;
    recordAllParticles = false;
}


vector<Particle> OBOptimizer::generateParticles(int noOfParticles)
{
    vector<Particle> allParticles;
    if(this->meshHeight == 0 || this->meshWidth == 0)
    {
        return allParticles;
    }
    int particleSize = this->meshHeight * this->meshWidth;
    for(int i = 0; i < noOfParticles; i++)
    {
        vector<int> initialCondition (particleSize,-99);
        initialCondition[0] = i;
        Particle p(i, particleSize, initialCondition);
        allParticles.push_back(p);
    }
    OBOptimizer::optimizationParticles = allParticles;
    return allParticles;
}

// ---------------------------------------------------------------------------------------------------------------------------
//
//	Function:		evaluateCost
// 	Purpose:		Evaluates current cost of the particle according to current core arrangement and routing algorithm
// 	Parameters: 	nothing
//	Returns:		nothing
//
// ---------------------------------------------------------------------------------------------------------------------------
void OBOptimizer::evaluateCost(vector<Particle>* particlesToEvaluate){
    switch(this->routingTypeToOptimize)
    {
        case YX:
        {
            cout<<"YX Routing not implemented yet..."<<endl;
            break;
        }
        case WestFirst:
        {
            cout<<"West First Routing not implemented yet..."<<endl;
            break;
        }
        case NorthLast:
        {
            cout<<"North Last Routing not implemented yet..."<<endl;
            break;
        }
        case NegativeFirst:
        {
            cout<<"Negative First Routing not implemented yet..."<<endl;
            break;
        }
        default:
        {
            // cout << "--- Mapping for Mode ID.:" << modeNo << " ---" << endl;
            // Loop through all particles and calculate their costs
            for(int particleNo = 0; particleNo < particlesToEvaluate->size(); particleNo++)
            {
                // Loop through all applications to optimize and map application mode to particle to get mapped traffic volume matrix
                for(int modeIndex = 0; modeIndex < this->appModesToOptimize.size(); modeIndex++)
                {
                    int modeNo = this->appModesToOptimize.at(modeIndex);
                    Particle &p = particlesToEvaluate->at(particleNo);
                    // cout << "--- Mapping for Particle ID.:" << p.ParticleID << " ---" << endl;
                    float cost = 0.0;
                    // Get application mode from mode No / mode ID
                    CoreGraph c = getModeFromModeNo(modeNo);
                    // cout << "No of cores: " << c.NoOfCores << endl;
                    // Loop through all communication edges in core graph
                    for(int edgeNo = 0; edgeNo < c.Edges.size(); edgeNo++)
                    {
                        CommunicationEdge edge = c.Edges.at(edgeNo);
                        int sourceID = edge.SourceID;
                        int destinationID = edge.DestinationID;
                        float volume = edge.Volume;
                        // cout << "Mapping " << sourceID << " --- " << volume << " ---> " << destinationID << endl;
                        int sourcePositionInParticle = getCorePositionInParticle(sourceID,p);
                        // cout << "Source Position in Particle: " << sourcePositionInParticle << endl;
                        int destinatonPositionInParticle = getCorePositionInParticle(destinationID,p);
                        // cout << "Destination Position in Particle: " << destinatonPositionInParticle << endl;
                        int yOfSource = (int)(((float)sourcePositionInParticle)/((float)meshHeight));
                        int xOfSource = (int)(sourcePositionInParticle - (meshWidth * yOfSource));
                        int yOfDestinaton = (int)(((float)destinatonPositionInParticle)/((float)meshHeight));
                        int xOfDestinaton = (int)(destinatonPositionInParticle - (meshWidth * yOfDestinaton));
                        // cout << "Source is at: " << "( " << xOfSource << " , " << yOfSource << " )" << endl;
                        // cout << "Destination is at: " << "( " << xOfDestinaton << " , " << yOfDestinaton << " )" << endl;
                        // Find manhattan distance from source to destination
                        float manhattanDistance = abs(yOfDestinaton - yOfSource) + abs(xOfDestinaton - xOfSource);
                        // cout << "Manhattan Distance: " << manhattanDistance << endl;
                        cost += (volume * manhattanDistance);
                        // cout << "Cost: " << (volume * manhattanDistance) << endl;
                    } // Edges for loop
                    p.CurrentCost = cost;
                } // Modes for loop
            } // Particles For loop
        }
    }
}

// ---------------------------------------------------------------------------------------------------------------------------
//
//	Function:		getModeFromModeNo
// 	Purpose:		Finds the application mode in the vector for the given mode no
// 	Parameters: 	nothing
//	Returns:		nothing
//
// ---------------------------------------------------------------------------------------------------------------------------
CoreGraph OBOptimizer::getModeFromModeNo(int ModeNo)
{
    for(int modeIndex = 0; modeIndex < this->appToOptimize.Modes.size(); modeIndex++)
    {
        CoreGraph c = this->appToOptimize.Modes.at(modeIndex);
        if(c.ID == ModeNo)
        {
            return c;
        }
    }
}

// ---------------------------------------------------------------------------------------------------------------------------
//
//	Function:		getCorePositionInParticle
// 	Purpose:		Finds the core position in the core arrangment from a particle
// 	Parameters: 	coreID - integer value
//	Returns:		nothing
//
// ---------------------------------------------------------------------------------------------------------------------------
int OBOptimizer::getCorePositionInParticle(int coreID, Particle p)
{
    for(int coreIndex = 0; coreIndex < p.CoreArrangement.size(); coreIndex++)
    {
        int coreAtThatPosition = p.CoreArrangement.at(coreIndex);
        if(coreAtThatPosition == coreID)
        {
            return coreIndex;
        }
    }
}

// ---------------------------------------------------------------------------------------------------------------------------
//
//	Function:		run
// 	Purpose:		Runs the iteration as many times requested on a separate thread and then updates after each iteration
// 	Parameters: 	nothing
//	Returns:		nothing
//
// ---------------------------------------------------------------------------------------------------------------------------
void OBOptimizer::run()
{
    emit signalOptimizationStarted();
    int noOfIterations = iterationsToRun;
    // Create a new tabuer object
    tabuer.meshHeight = this->meshHeight;
    tabuer.meshWidth = this->meshWidth;
    // Clear out any previously stored global costs
    allGlobalBestCosts.clear();
    allParticleCosts.clear();
    OptimizationAlgorithm algorithm = algorithmToRun;
    // Iterate once
    OBOptimizer::iterate(&optimizationParticles,algorithm, true);
    // Add global cost list
    allGlobalBestCosts.push_back(Reading(0,GlobalBestParticle.CurrentCost));
    // Add particle costs list if required
    if(recordAllParticles)
    {
        for(int particleIndex = 0; particleIndex < optimizationParticles.size(); particleIndex++)
        {
            Particle* p = &optimizationParticles.at(particleIndex);
            ReadingDB db(p->ParticleID);
            db.addReading(0,p->CurrentCost);
            allParticleCosts.push_back(db);
        }
    }
    emit signalIterated(0, &appToOptimize, &optimizationParticles, &GlobalBestParticle);
    for(int iteratonNo = 1; iteratonNo < noOfIterations; iteratonNo++)
    {
        // cout<<"Running Iteraton No. " << iteratonNo << endl;

        // Iterate till end
        OBOptimizer::iterate(&optimizationParticles,algorithm, false);

        dataUpdateMutexPointer->lock();
        // Update global cost list
        allGlobalBestCosts.push_back(Reading(iteratonNo,GlobalBestParticle.CurrentCost));

        // Update particle costs list if required
        if(recordAllParticles)
        {
            for(int particleIndex = 0; particleIndex < optimizationParticles.size(); particleIndex++)
            {
                Particle* p = &optimizationParticles.at(particleIndex);
                ReadingDB* db = findDBForParticle(p->ParticleID);
                if(db != NULL)
                {
                    db->addReading(iteratonNo,p->CurrentCost);
                }
            }
        }
        dataUpdateMutexPointer->unlock();
        // Now update GUI
        emit signalIterated(iteratonNo, &appToOptimize, &optimizationParticles, &GlobalBestParticle);
    }
    cout << "Best Particle with cost " << GlobalBestParticle.CurrentCost << "found was: " << endl;
    cout << "---------------------------------------------" << endl;
    cout << GlobalBestParticle.toString();
    emit signalOptimizationFinished();
}

ReadingDB* OBOptimizer::findDBForParticle(int partID)
{
    for(int i = 0; i < allParticleCosts.size(); i++)
    {
        ReadingDB* db = &allParticleCosts.at(i);
        if(db->particleID == partID)
        {
            return db;
        }
    }
    return NULL;
}

// ---------------------------------------------------------------------------------------------------------------------------
//
//	Function:		iterate
// 	Purpose:		Runs single iteration and then updates after each iteration
// 	Parameters: 	oldParticles - takes in vector of all old particles
//	Returns:		vector of updated particles
//
// ---------------------------------------------------------------------------------------------------------------------------
void OBOptimizer::iterate(vector<Particle> *oldParticles, OptimizationAlgorithm algorithm, bool firstIteration)
{
    switch(algorithm)
    {
        case DPSO:
        {
            // cout << "Running plain DPSO."<< endl;
            if(firstIteration)
            {
                // Now evaluate Costs of all particles
                evaluateCost(oldParticles);
                // cout << "All particles first iteration cost Evaluated" << endl;

                // Implementation of plain DPSO
                // cout << "Starting first iteration..."<<endl;
                // Find the best cost of all particles (Global Cost)
                Particle thisIterationBestParticle = getBestCostParticle(oldParticles)->deepClone();

                GlobalBestParticle = thisIterationBestParticle;

                // cout << "Global Cost: " << GlobalBestParticle.CurrentCost<< endl;
                for(int i = 0; i < oldParticles->size(); i++)
                {
                    Particle* p = &oldParticles->at(i);
                    p->LocalBestCost = p->CurrentCost;
                    p->LocalBestCoreArrangement = p->CoreArrangement;
                }

                // cout << "All local costs found" << endl;

            }
            else
            {
                // Implementation of plain DPSO
                // cout << "Starting iteration..."<<endl;

                // Go through all particles and move them
                for(int particleNo = 0; particleNo < oldParticles->size(); particleNo++)
                {
                    moveParticle(&oldParticles->at(particleNo));
                }

                // cout << "All particles moved." << endl;

                // Now evaluate Costs of all particles
                evaluateCost(oldParticles);
                // cout << "All particles this iteration cost Evaluated" << endl;

                // Find best cost of each particle and update it (Local Cost)
                updateParticleLocalCost(oldParticles);

                // Find the best cost of all particles (Global Cost)
                Particle thisIterationBestParticle = getBestCostParticle(oldParticles)->deepClone();
                double thisIterationBestCost = thisIterationBestParticle.CurrentCost;
                // If new cost is less than current best cost
                if(GlobalBestParticle.CurrentCost > thisIterationBestCost)
                {
                    // The new particle is better, save it
                    Particle p = thisIterationBestParticle.deepClone();
                    GlobalBestParticle = p;
                    cout << "Global Cost Updated..." << endl;
                }

                // cout << "Global Cost: " << GlobalBestParticle.CurrentCost<< endl;

                // cout << "All local costs found" << endl;
            }
            break;
        }
        case TDPSO:
        {
        // cout << "Running Tabu-ed DPSO."<< endl;
            // Implementation of Tabu-ed DPSO
        if(firstIteration)
        {
            // Now evaluate Costs of all particles
            evaluateCost(oldParticles);
            // cout << "All particles first iteration cost Evaluated" << endl;

            // Implementation of plain DPSO
            // cout << "Starting first iteration..."<<endl;
            // Find the best cost of all particles (Global Cost)
            Particle thisIterationBestParticle = getBestCostParticle(oldParticles)->deepClone();

            GlobalBestParticle = thisIterationBestParticle;

            // cout << "Global Cost: " << GlobalBestParticle.CurrentCost<< endl;
            for(int i = 0; i < oldParticles->size(); i++)
            {
                Particle* p = &oldParticles->at(i);
                p->LocalBestCost = p->CurrentCost;
                p->LocalBestCoreArrangement = p->CoreArrangement;
            }

            // Add current particle positions to tabu list
            updateTabuList();

            // cout << "All local costs found" << endl;

        }
        else
        {
            // Implementation of plain DPSO
            // cout << "Starting iteration..."<<endl;

            // Go through all particles and move them
            for(int particleNo = 0; particleNo < oldParticles->size(); particleNo++)
            {
                moveParticle(&oldParticles->at(particleNo));
            }

            // cout << "All particles moved." << endl;

            // Now evaluate Costs of all particles
            evaluateCost(oldParticles);
            // cout << "All particles this iteration cost Evaluated" << endl;

            // Find best cost of each particle and update it (Local Cost)
            updateParticleLocalCost(oldParticles);

            // Find the best cost of all particles (Global Cost)
            Particle thisIterationBestParticle = getBestCostParticle(oldParticles)->deepClone();
            double thisIterationBestCost = thisIterationBestParticle.CurrentCost;
            // If new cost is less than current best cost
            if(GlobalBestParticle.CurrentCost > thisIterationBestCost)
            {
                // The new particle is better, save it
                Particle p = thisIterationBestParticle.deepClone();
                GlobalBestParticle = p;
                // cout << "Global Cost Updated..." << endl;
            }

            // Add current particle positions to tabu list
            updateTabuList();
            // cout << "Global Cost: " << GlobalBestParticle.CurrentCost<< endl;

            // cout << "All local costs found" << endl;
            break;
        }
        }
    }
}

// ---------------------------------------------------------------------------------------------------------------------------
//
//	Function:		updateTabuList
// 	Purpose:		Updates the tabu list from all particles current core arrangements
// 	Parameters: 	nothing
//	Returns:		nothing
//
// ---------------------------------------------------------------------------------------------------------------------------
void OBOptimizer::updateTabuList()
{
    for(int i = 0; i < this->optimizationParticles.size(); i++)
    {
        Particle *p = &this->optimizationParticles.at(i);
        tabuer.addToTabuList(p->CoreArrangement);
    }
}


// ---------------------------------------------------------------------------------------------------------------------------
//
//	Function:		moveParticle
// 	Purpose:		Moves a particle to a new core arrangment according to local best, global best and inertia factors
// 	Parameters: 	aParticle - takes in a reference to a particle object
//	Returns:		nothing
//
// ---------------------------------------------------------------------------------------------------------------------------
void OBOptimizer::moveParticle(Particle* aParticle)
{
    // Should the particle follow it's inertia ?
    bool FollowInertia = (double)(rand() % 100) < (double)(ParticleInertia*100);
    if(FollowInertia)
    {
        // Apply moves that allow particle to remain at it's current position
        vector<SwapMove> movesToApply = getSwapMoves(aParticle->CoreArrangement, aParticle->CoreArrangement);
        applySwapMoves(movesToApply, aParticle);
        // cout << "Particle Followed Inertia." << endl;
    }

    // Should the particle follow self-confidence ?
    bool FollowSelfConfidence = (double)(rand() % 100) < (double)(ParticleSelfConfidence*100);
    if(FollowSelfConfidence)
    {
        // Apply moves that allow particle to follow it's self confidence (local best)
        // cout << "Getting swap moves" << endl;
        vector<SwapMove> movesToApply = getSwapMoves(aParticle->CoreArrangement, aParticle->LocalBestCoreArrangement);
        // cout << "Applying swap moves" << endl;
        applySwapMoves(movesToApply, aParticle);
        // cout << "Particle Followed Self-Confidence." << endl;
    }

    // Should the particle follow swarm ?
    bool FollowSwarmConfidence = (double)(rand() % 100) < (double)(SwarmConfidence*100);
    if(FollowSwarmConfidence)
    {
        // Apply moves that allow particle to follow it's self confidence (local best)
        vector<SwapMove> movesToApply = getSwapMoves(aParticle->CoreArrangement, GlobalBestParticle.CoreArrangement);
        applySwapMoves(movesToApply, aParticle);
        // cout << "Particle Followed Swarm Confidence." << endl;
    }
}

// ---------------------------------------------------------------------------------------------------------------------------
//
//	Function:		updateParticleLocalCost
// 	Purpose:		Loops through all particles passed and updates their local best cost according to their current cost
// 	Parameters: 	allParticles - takes in vector of all particles to update local cost
//	Returns:		nothing
//
// ---------------------------------------------------------------------------------------------------------------------------
void OBOptimizer::updateParticleLocalCost(vector<Particle>* allParticles)
{
    for(int i = 0; i < allParticles->size(); i++)
    {
        // Get a pointer to particle object
        Particle *p = &allParticles->at(i);
        // If the particle's current best cost is smaller than best found previously.
        if(p->CurrentCost < p->LocalBestCost)
        {
            // Then assign the local best found as current
            int t = p->LocalBestCost;
            p->LocalBestCost = p->CurrentCost;
            p->LocalBestCoreArrangement = p->CoreArrangement;
            // cout<<"Local Cost Updated from : "<< t << " to " << p->LocalBestCost << endl;
        }
        else if(p->CurrentCost > p->LocalBestCost)
        {
            // cout<<"Local Cost NOT Updated from : "<< p->LocalBestCost << " to " << p->CurrentCost << endl;
        }
        else
        {
            // cout<<"Local Cost & Current Cost Same: "<< p->CurrentCost << endl;
        }
        // cout << "Particle " << p->ParticleID <<" local cost: " << p->LocalBestCost <<endl;
    }
}

// ---------------------------------------------------------------------------------------------------------------------------
//
//	Function:		getBestCostParticle
// 	Purpose:		Finds out the best cost of all passed particles for comparing against global best cost particle
// 	Parameters: 	allParticles - takes in vector of all particles from which to find the best cost
//	Returns:		Particle which has best cost
//
// ---------------------------------------------------------------------------------------------------------------------------
Particle* OBOptimizer::getBestCostParticle(vector<Particle>* allParticles)
{
    Particle* bestParticle = &allParticles->at(0);
    // cout << "Particle 0 cost: " << bestParticle->CurrentCost << endl;
    double currentBestCost = bestParticle->CurrentCost;
    for(int particleNo = 1; particleNo < allParticles->size(); particleNo++)
    {
        Particle* par = &allParticles->at(particleNo);
        if(currentBestCost > par->CurrentCost)
        {
            currentBestCost = par->CurrentCost;
            bestParticle = par;
        }
        // cout << "Particle " << par->ParticleID << " cost: " << par->CurrentCost << endl;
    }
    // cout << "Returning Particle " << bestParticle->ParticleID << " as global best." << endl;
    return bestParticle;
}

// ---------------------------------------------------------------------------------------------------------------------------
//
//	Function:		getSwapMoves
// 	Purpose:		Finds out the swap moves which are required to make subject particle same as reference particle
// 	Parameters: 	sourceParticle - a particle object which is to be changed or from which to begin
//                  destinationParticle - a particle object to which sourceParticle should go or to end
//	Returns:		vector collection of swap moves to apply to make source particle same as destination particle
//
// ---------------------------------------------------------------------------------------------------------------------------
vector<SwapMove> OBOptimizer::getSwapMoves(Particle sourceParticle, Particle destinationParticle)
{
    vector<SwapMove> s;
    for(int index = 0; index < sourceParticle.CoreArrangement.size(); index++)
    {
        SwapMove move;
        // The source core position to move
        move.corePositionToSwap1 = index;
        int sourceCoreIDAtIndex = sourceParticle.CoreArrangement.at(index);
        // Find that core's postion in destination particle
        move.corePositionToSwap2 = getCorePositionInParticle(sourceCoreIDAtIndex, destinationParticle);
        // Add swap move to list of swap moves to return
        s.push_back(move);
    }
    return s;
}

// ---------------------------------------------------------------------------------------------------------------------------
//
//	Function:		getSwapMoves
// 	Purpose:		Finds out the swap moves which are required to make subject particle same as reference particle
// 	Parameters: 	sourceCoreArrangement - Initial core arrangment which is to be changed or from which to begin
//                  destinationCoreArrangement - Core Arrangment to which source core arrangement should go or end
//	Returns:		vector collection of swap moves to apply to make source particle same as destination particle
//
// ---------------------------------------------------------------------------------------------------------------------------
vector<SwapMove> OBOptimizer::getSwapMoves(vector<int> sourceCoreArrangement, vector<int> destinationCoreArrangement)
{
    vector<SwapMove> s;
    for(int index = 0; index < sourceCoreArrangement.size(); index++)
    {
        SwapMove move;
        // The source core position to move
        move.corePositionToSwap1 = index;
        int sourceCoreIDAtIndex = sourceCoreArrangement.at(index);
        // Find that core's postion in destination particle
        move.corePositionToSwap2 = getCorePositionInCoreArrangment(sourceCoreIDAtIndex, destinationCoreArrangement);
        // Add swap move to list of swap moves to return
        s.push_back(move);
    }
    return s;
}

int OBOptimizer::getCorePositionInCoreArrangment(int coreIdToFind, vector<int> searchSpace)
{
    for(int coreIndex = 0; coreIndex < searchSpace.size(); coreIndex++)
    {
        int coreAtThatPosition = searchSpace.at(coreIndex);
        if(coreAtThatPosition == coreIdToFind)
        {
            return coreIndex;
        }
    }
}

// ---------------------------------------------------------------------------------------------------------------------------
//
//	Function:		applySwapMoves
// 	Purpose:		Applies the vector of swap moves to the particle
// 	Parameters: 	swaps - vector collection of all swap moves to apply
//                  aParticle - a particle object to which the swap moves are to be applied
//	Returns:		nothing
//
// ---------------------------------------------------------------------------------------------------------------------------
void OBOptimizer::applySwapMoves(vector<SwapMove> swaps, Particle* aParticle)
{
    // cout << "Swap moves to apply: "<< swaps.size() << endl;
    if(this->algorithmToRun == OptimizationAlgorithm::TDPSO)
    {
        // Choose a random swap move to apply
        int swapMoveToApply = (rand() % swaps.size());
        // Get the first swap move object
        SwapMove move = swaps.at(swapMoveToApply);
        move = tabuer.proposeMove(move,aParticle->CoreArrangement);
        // cout << "Trying to Swap from " << move.corePositionToSwap1 << " to " << move.corePositionToSwap2 << endl;
        int sourceCoreID = aParticle->CoreArrangement.at(move.corePositionToSwap1);
        int destCoreID = aParticle->CoreArrangement.at(move.corePositionToSwap2);
        // cout << "Swapping Core " << sourceCoreID << " with " << destCoreID;
        aParticle->CoreArrangement[move.corePositionToSwap1] = destCoreID;
        aParticle->CoreArrangement[move.corePositionToSwap2] = sourceCoreID;
        // cout << "Swapped Core " << sourceCoreID << " with " << destCoreID;
        // cout << " from " << move.corePositionToSwap1 << " to " << move.corePositionToSwap2 << endl;
    }
    else
    {
        // Go through all swap moves and apply one by one to particle
        for(int i = 0; i < swaps.size(); i++)
        {
            // Get the swap move object
            SwapMove move = swaps.at(i);
            // cout << "Trying to Swap from " << move.corePositionToSwap1 << " to " << move.corePositionToSwap2 << endl;
            int sourceCoreID = aParticle->CoreArrangement.at(move.corePositionToSwap1);
            int destCoreID = aParticle->CoreArrangement.at(move.corePositionToSwap2);
            // cout << "Swapping Core " << sourceCoreID << " with " << destCoreID;
            aParticle->CoreArrangement[move.corePositionToSwap1] = destCoreID;
            aParticle->CoreArrangement[move.corePositionToSwap2] = sourceCoreID;
            // cout << "Swapped Core " << sourceCoreID << " with " << destCoreID;
            // cout << " from " << move.corePositionToSwap1 << " to " << move.corePositionToSwap2 << endl;
        }
    }
}
