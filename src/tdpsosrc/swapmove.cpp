//=================================================================================================
// Name        : swapmove.cpp
// Author      : Muhammad Obaidullah
// Version     : 0.1
// Copyright   : Electrical & Computer Engineering, Ryerson University ©2015
// Description : Allows creation of swap move objects
//=================================================================================================
#include "swapmove.h"

// ---------------------------------------------------------------------------------------------------------------------------
//
//	Function:		SwapMove CONSTRUCTOR
// 	Purpose:		Constructs an object of class SwapMove to store cores which are to be swapped
// 	Parameters: 	nothing
//	Returns:		nothing
//
// ---------------------------------------------------------------------------------------------------------------------------
SwapMove::SwapMove()
{

}

// ---------------------------------------------------------------------------------------------------------------------------
//
//	Function:		SwapMove CONSTRUCTOR
// 	Purpose:		Constructs an object of class SwapMove to store cores which are to be swapped
// 	Parameters: 	swapCore1Position - A core position which is to be swapped
//                  swapCore2Position - A core position which is to be swapped with
//	Returns:		nothing
//
// ---------------------------------------------------------------------------------------------------------------------------
SwapMove::SwapMove(int swapCore1Position, int swapCore2Position)
{
    this->corePositionToSwap1 = swapCore1Position;
    this->corePositionToSwap2 = swapCore2Position;
}

