//=================================================================================================
// Name        : coreGraph.cpp
// Author      : Muhammad Obaidullah
// Version     : 0.1
// Copyright   : Electrical & Computer Engineering, Ryerson University ©2015
// Description : Core Graph class to store communication volume between all cores for one
//               application mode.
//=================================================================================================

#include "coregraph.h"
#include "Matrix.hpp"

using namespace std;
using namespace YMatrix;

// ---------------------------------------------------------------------------------------------------------------------------
//
//	Function:		Core Graph CONSTRUCTOR
// 	Purpose:		Constructs an object of class CoreGraph to store core communication volume for one application mode.
//					An application might have one or many application modes and each mode has a core graph.
// 	Parameters: 	modeID - A unique ID to identify specific core graph
//                  modeName - A string name for the application mode
//                  communicationEdges - All the communication edges (links) contained in the core graph
//	Returns:		nothing
//
// ---------------------------------------------------------------------------------------------------------------------------
CoreGraph::CoreGraph(int modeID, int numOfCores, string modeName,  std::vector<CommunicationEdge> communicationEdges)
{
    this->ID = modeID;
    this->NoOfCores = numOfCores;
    this->Name = modeName;
    this->Edges = communicationEdges;
}

// ---------------------------------------------------------------------------------------------------------------------------
//
//	Function:		Core Graph CONSTRUCTOR
// 	Purpose:		Constructs an object of class CoreGraph to store core communication volume for one application mode.
//					An application might have one or many application modes and each mode has a core graph.
// 	Parameters: 	nothing
//	Returns:		nothing
//
// ---------------------------------------------------------------------------------------------------------------------------
CoreGraph::CoreGraph(){

}

// ---------------------------------------------------------------------------------------------------------------------------
//
//	Function:		Core Graph DESTRUCTOR
// 	Purpose:		Destroys the CoreGraph object
// 	Parameters: 	nothing
//	Returns:		nothing
//
// ---------------------------------------------------------------------------------------------------------------------------
CoreGraph::~CoreGraph()
{
	// TODO Auto-generated destructor stub
}

MatrixM CoreGraph::getTrafficMatrix()
{
    // Prepare traffic array with column size the same as number of cores and row size the same as number of cores
    int TRAFFIC_ARRAY_SIZE = this->NoOfCores * this->NoOfCores;
    vector<float> trafficVector(TRAFFIC_ARRAY_SIZE,0.0);
    // Setting traffic matrix dimensions as R X C = number of cores X number of cores
    MatrixM trafficMatrix(this->NoOfCores,this->NoOfCores);
    for(int coreID = 0; coreID < TRAFFIC_ARRAY_SIZE; coreID++)
    {
        // Row Number
        int toCore = (int)(coreID/this->NoOfCores);
        // Column Number
        int fromCore = (int)(coreID - (this->NoOfCores * toCore));
        float foundVolume = 0.0;
        // Diagonal entries are zero. Save time. Core does not communicate to itself.
        if(fromCore != toCore)
        {
            // Loop through, and try to find if volume for that edge was provided or not
            for (int edgeNo = 0; edgeNo < (this->Edges.size()); edgeNo++)
            {
                CommunicationEdge edgeToCheck = (CommunicationEdge)(this->Edges[edgeNo]);
                if(edgeToCheck.SourceID == fromCore && edgeToCheck.DestinationID == toCore)
                {
                    // Volume provided
                    foundVolume = edgeToCheck.Volume;
                }
            }
        }
        trafficMatrix(toCore,fromCore) = foundVolume;
        trafficVector[coreID] = foundVolume;
    }
    return trafficMatrix;
}

// ---------------------------------------------------------------------------------------------------------------------------
//
//	Function:		toString
// 	Purpose:		Creates a string to briefly describe the core object
// 	Parameters: 	nothing
//	Returns:		Printable string describing the core
//
// ---------------------------------------------------------------------------------------------------------------------------
string CoreGraph::toString()
{
    std::stringstream ss;
    ss << "Mode Id: " << this->convertToString(this->ID) << " Application Mode: " << this->Name << " No. Of Cores: " << this->convertToString(this->ID) << endl;
    for (int edgeNo = 0; edgeNo < this->Edges.size(); edgeNo++)
    {
        CommunicationEdge ed = this->Edges.at(edgeNo);
        ss << "Edge ID: " << this->convertToString(ed.ID) << " From: " <<  this->convertToString(ed.SourceID) << " To: " << this->convertToString(ed.SourceID);
        ss << " Volume: " << this->convertToString(ed.Volume) << endl;
    }
    return ss.str();
}

// ---------------------------------------------------------------------------------------------------------------------------
//
//	Function:		getCoresUsed
// 	Purpose:		Finds out which cores are used in this application mode
// 	Parameters: 	nothing
//	Returns:		Vector of all core ids which are being used in this application mode
//
// ---------------------------------------------------------------------------------------------------------------------------
vector<int> CoreGraph::getCoresUsed()
{
    vector<int> coresUsed;
    for (int coreNo = 0; coreNo < this->Edges.size(); coreNo++)
    {
        CommunicationEdge edge = this->Edges.at(coreNo);
        if(find(coresUsed.begin(), coresUsed.end(), edge.DestinationID) == coresUsed.end())
        {
            // This vertex has not already been added, add it
            coresUsed.push_back(edge.DestinationID);
        }
        if(find(coresUsed.begin(), coresUsed.end(), edge.SourceID) == coresUsed.end())
        {
            // This vertex has not already been added, add it
            coresUsed.push_back(edge.SourceID);
        }
    }
    return coresUsed;
}
