//=================================================================================================
// Name        : communicationedge.cpp
// Author      : Muhammad Obaidullah
// Version     : 0.1
// Copyright   : Electrical & Computer Engineering, Ryerson University ©2015
// Description : Communication edge to represent communication volume between two vertices (cores)
//=================================================================================================
#include "communicationedge.h"

// ---------------------------------------------------------------------------------------------------------------------------
//
//	Function:		Communication Edge CONSTRUCTOR
// 	Purpose:		Constructs an object of class CommunicationEdge to represent communication volume between two vertices (cores)
// 	Parameters: 	edgeID              - Unique ID assigned to the edge to identify it
//                  communicationVolume - A float value to represent amount of communication occuring between two vertices
//                  sourceVertex        - ID of the source vertex from where the communication is orginating
//                  destinationVertex   - ID of the destination vertex to which the communication is destined to
//	Returns:		nothing
//
// ---------------------------------------------------------------------------------------------------------------------------
CommunicationEdge::CommunicationEdge(int edgeID, float communicationVolume, int sourceVertex, int destinationVertex)
{
    this->ID = edgeID;
    this->Volume = communicationVolume;
    this->SourceID = sourceVertex;
    this->DestinationID = destinationVertex;
}
