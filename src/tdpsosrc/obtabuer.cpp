//=================================================================================================
// Name        : obtabuer.cpp
// Author      : Muhammad Obaidullah
// Version     : 0.1
// Copyright   : Electrical & Computer Engineering, Ryerson University ©2015
// Description : Tabuer class which stores all tabu-ed core arrangements and proposes new moves
//               based on proposed moves.
//=================================================================================================

#include "obtabuer.h"

// ---------------------------------------------------------------------------------------------------------------------------
//
//	Function:		OBTabuer CONSTRUCTOR
// 	Purpose:		Constructs an object of class OBtabuer to guide particles to predicted optimum moves
// 	Parameters: 	nothing
//	Returns:		nothing
//
// ---------------------------------------------------------------------------------------------------------------------------
OBTabuer::OBTabuer()
{
    allDeflectionTypes.push_back(DeflectionType::xAxisLine);
    allDeflectionTypes.push_back(DeflectionType::yAxisLine);
    allDeflectionTypes.push_back(DeflectionType::yEqualsxLine);
    allDeflectionTypes.push_back(DeflectionType::yEqualsMinusxLine);
    allDeflectionTypes.push_back(DeflectionType::reverse);
}

// ---------------------------------------------------------------------------------------------------------------------------
//
//	Function:		OBTabuer CONSTRUCTOR
// 	Purpose:		Constructs an object of class OBtabuer to guide particles to predicted optimum moves
// 	Parameters: 	topologyWidth - integer representing the width of topology
//                  topologyHeight - integer representing the height of topology
//	Returns:		nothing
//
// ---------------------------------------------------------------------------------------------------------------------------
OBTabuer::OBTabuer(int topologyWidth, int topologyHeight)
{
    this->meshHeight = topologyHeight;
    this->meshWidth = topologyWidth;
    allDeflectionTypes.push_back(DeflectionType::xAxisLine);
    allDeflectionTypes.push_back(DeflectionType::yAxisLine);
    allDeflectionTypes.push_back(DeflectionType::yEqualsxLine);
    allDeflectionTypes.push_back(DeflectionType::yEqualsMinusxLine);
    allDeflectionTypes.push_back(DeflectionType::reverse);
}

// ---------------------------------------------------------------------------------------------------------------------------
//
//	Function:		addToTabuList
// 	Purpose:		Adds the passed core arrangment to the list of core arrangements which are tabued
// 	Parameters: 	tabuedCoreArrangement - vector of integers representing the arrangement of cores
//	Returns:		nothing
//
// ---------------------------------------------------------------------------------------------------------------------------
void OBTabuer::addToTabuList(vector<int> CoreArrangementToTabu)
{
    // Check if the core arrangment is already tabu-ed. If it is not then add it to the list
    if(!isTabued(CoreArrangementToTabu))
    {
        this->allTabuedCoreArrangments.push_back(CoreArrangementToTabu);
    }
}

// ---------------------------------------------------------------------------------------------------------------------------
//
//	Function:		isTabued
// 	Purpose:		Checks wheather the passed move (core arrangement) is already tabued or not
// 	Parameters: 	move - vector of integers representing the proposed arrangement of cores
//	Returns:		bool - representing if the move is tabued or not
//
// ---------------------------------------------------------------------------------------------------------------------------
bool OBTabuer::isTabued(vector<int> move)
{
    for(int moveIndex = 0; moveIndex < this->allTabuedCoreArrangments.size(); moveIndex++)
    {
        // Get the mode at that index
        vector<int> tabuedMove = this->allTabuedCoreArrangments.at(moveIndex);
        if(this->isSame(move,tabuedMove))
        {
            return true;
        }
    }
    return false;
}

// ---------------------------------------------------------------------------------------------------------------------------
//
//	Function:		isSame
// 	Purpose:		Checks wheather the two passed core arrangments are similar
// 	Parameters: 	oneArrangement - vector of integers representing one arrangement of cores
//                  anotherArrangement - vector of integers representing another arrangement of cores
//	Returns:		bool - representing if the two passed core arrangments are exactly same or not
//
// ---------------------------------------------------------------------------------------------------------------------------
bool OBTabuer::isSame(vector<int> oneArrangement, vector<int> anotherArrangement)
{
    // Cycle through all cores in oneArrangment vector
    for(int i = 0; i < oneArrangement.size(); i++)
    {
        int coreAtOneArrangement = oneArrangement.at(i);
        int coreAtAnotherArrangement = anotherArrangement.at(i);
        if(coreAtOneArrangement != coreAtAnotherArrangement)
        {
            return false;
        }
    }
    return true;
}

// ---------------------------------------------------------------------------------------------------------------------------
//
//	Function:		isMoveApplicable
// 	Purpose:		Checks wheather the proposed move will cause a core arrangment which is tabued or no
// 	Parameters: 	coreArrangment - vector of integers representing initial arrangement of cores
//                  moveToApply - SwapMove object which represent a move which is proposed
//	Returns:		bool - representing if proposed move is applicable or no
//
// ---------------------------------------------------------------------------------------------------------------------------
bool OBTabuer::isMoveApplicable(vector<int> coreArrangment, SwapMove moveToApply)
{
    int totalPositions = this->meshHeight * this->meshWidth;
    // Get start move y coordinate
    int starty = (int)((double)(moveToApply.corePositionToSwap1)/(double)(totalPositions));
    // Check if within limit
    if(starty >= this->meshHeight || starty < 0)
    {
        return false;
    }
    // Get start move x coordinate
    int startx = moveToApply.corePositionToSwap1 - (starty*this->meshHeight);
    // Check if within limit
    if(startx >= this->meshWidth  || startx < 0)
    {
        return false;
    }
    // Get end move y coordinate
    int endy = (int)((double)(moveToApply.corePositionToSwap2)/(double)(totalPositions));
    // Check if within limit
    if(endy >= this->meshHeight  || endy < 0)
    {
        return false;
    }
    // Get end move x coordinate
    int endx = moveToApply.corePositionToSwap2 - (starty*this->meshHeight);
    // Check if within limit
    if(endx >= this->meshWidth || endx < 0)
    {
        return false;
    }
    if(moveToApply.corePositionToSwap1 == moveToApply.corePositionToSwap2)
    {
        return true;
    }
    // Checking for tabu
    // First apply the move to a temporary variable
    return true; // OB bypassing tabu for now
    vector<int> temp = coreArrangment;
    int tempCore;
    tempCore = temp[moveToApply.corePositionToSwap1];
    temp[moveToApply.corePositionToSwap1] = temp[moveToApply.corePositionToSwap2];
    temp[moveToApply.corePositionToSwap2] = tempCore;
    // Now check if this move will result in a tabu-ed core arrangement
    if(!this->isTabued(temp))
    {
        return true;
    }
    else
    {
        return false;
    }
}

// ---------------------------------------------------------------------------------------------------------------------------
//
//	Function:		deflectMove
// 	Purpose:		Deflects a swap move on the given deflection line
// 	Parameters: 	aLineToDeflectOn - Type of deflection line based on DeflectionType enumeration object
//                  initialMove - SwapMove object which represent a move which is proposed
//	Returns:		SwapMove - resulting deflected swap move
//
// ---------------------------------------------------------------------------------------------------------------------------
SwapMove OBTabuer::deflectMove(SwapMove initialMove, DeflectionType aLineToDeflectOn)
{
    // Make an object to return
    SwapMove m;
    switch(aLineToDeflectOn)
    {
    case DeflectionType::xAxisLine:
    {
        // Destination position becomes the source position
        m.corePositionToSwap1 = initialMove.corePositionToSwap2;
        int totalPositions = this->meshHeight*this->meshWidth;
        int starty = (int)((double)(initialMove.corePositionToSwap1)/(double)(totalPositions));
        int startx = totalPositions - (starty*this->meshHeight);
        int endy = (int)((double)(initialMove.corePositionToSwap2)/(double)(totalPositions));
        int endx = totalPositions - (starty*this->meshHeight);
        // double magnitude = sqrt((((double)endy)-((double)starty)) + (((double)endx)-((double)startx)));
        // X position
        int xSize = endx - startx;
        int newX = endx + xSize;
        // Y position does not change
        int newY = starty;
        int newPosition = (newY*this->meshHeight) + newX;
        m.corePositionToSwap2 = newPosition;
        break;
    }
    case DeflectionType::yAxisLine:
    {
        // Destination position becomes the source position
        m.corePositionToSwap1 = initialMove.corePositionToSwap2;
        int totalPositions = this->meshHeight*this->meshWidth;
        int starty = (int)((double)(initialMove.corePositionToSwap1)/(double)(totalPositions));
        int startx = totalPositions - (starty*this->meshHeight);
        int endy = (int)((double)(initialMove.corePositionToSwap2)/(double)(totalPositions));
        int endx = totalPositions - (starty*this->meshHeight);
        // X position does not change
        int newX = startx;
        // Y position
        int ySize = endy - starty;
        int newY = endy + ySize;
        int newPosition = (newY*this->meshHeight) + newX;
        m.corePositionToSwap2 = newPosition;
        break;
    }
    case DeflectionType::yEqualsxLine:
    {
        // Destination position becomes the source position
        m.corePositionToSwap1 = initialMove.corePositionToSwap2;
        int totalPositions = this->meshHeight*this->meshWidth;
        int starty = (int)((double)(initialMove.corePositionToSwap1)/(double)(totalPositions));
        int startx = totalPositions - (starty*this->meshHeight);
        int endy = (int)((double)(initialMove.corePositionToSwap2)/(double)(totalPositions));
        int endx = totalPositions - (starty*this->meshHeight);
        // X position becomes start Y position
        int newX = starty;
        // Y position becomes start X position
        int newY = startx;
        int newPosition = (newY*this->meshHeight) + newX;
        m.corePositionToSwap2 = newPosition;
        break;
    }
    case DeflectionType::yEqualsMinusxLine:
    {
        // Destination position becomes the source position
        m.corePositionToSwap1 = initialMove.corePositionToSwap2;
        int totalPositions = this->meshHeight*this->meshWidth;
        int starty = (int)((double)(initialMove.corePositionToSwap1)/(double)(totalPositions));
        int startx = totalPositions - (starty*this->meshHeight);
        int endy = (int)((double)(initialMove.corePositionToSwap2)/(double)(totalPositions));
        int endx = totalPositions - (starty*this->meshHeight);
        // X position becomes start Y position
        int newX = starty;
        // Y position becomes start X position
        int newY = this->meshWidth - startx - 1;
        int newPosition = (newY*this->meshHeight) + newX;
        m.corePositionToSwap2 = newPosition;
        break;
    }
    default:
    {
        // Complete deflection, where the source core becomes the destiantion and vice versa
        m.corePositionToSwap1 = initialMove.corePositionToSwap2;
        m.corePositionToSwap2 = initialMove.corePositionToSwap1;
    }
    }
    return m;
}

SwapMove OBTabuer::proposeMove(SwapMove initialMove, vector<int> particleCoreArrangement)
{
    if(this->isMoveApplicable(particleCoreArrangement, initialMove))
    {
        // The proposed move is directly applicable
        cout << "Move Applicable directly" << endl;
        return initialMove;
    }
    else
    {
        for(int trial = 0; trial < allDeflectionTypes.size(); trial++)
        {
            // Choose a deflection type
            DeflectionType defType = allDeflectionTypes.at(trial);
            // Get deflected move
            SwapMove trialMove = deflectMove(initialMove, defType);
            // Check if deflected
            if(this->isMoveApplicable(particleCoreArrangement,trialMove))
            {
                switch(defType)
                {
                case DeflectionType::xAxisLine:
                {
                    cout << "Move deflected in x-axis" << endl;
                    break;
                }
                case DeflectionType::yAxisLine:
                {
                    cout << "Move deflected in y-axis" << endl;
                    break;
                }
                case DeflectionType::yEqualsxLine:
                {
                    cout << "Move deflected in line y = x" << endl;
                    break;
                }
                case DeflectionType::yEqualsMinusxLine:
                {
                    cout << "Move deflected in line y = -x" << endl;
                    break;
                }
                default:
                {
                    cout << "Move reversed completely" << endl;
                    break;
                }
                }
                return trialMove;
            }
        }
        cout << "returning default move..." << endl;
        // If all deflected moves are tabued and already tried, let it apply the initial move
        return initialMove;
    }
}

























