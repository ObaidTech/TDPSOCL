//=================================================================================================
// Name        : swapmove.h
// Author      : Muhammad Obaidullah
// Version     : 0.1
// Copyright   : Electrical & Computer Engineering, Ryerson University ©2015
// Description : Allows creation of swap move objects
//=================================================================================================
#ifndef SWAPMOVE_H
#define SWAPMOVE_H
#include <vector>
#include <particle.h>
#include <math.h>

class SwapMove
{
public:
    // BEGIN - Functions ------------ //
    SwapMove();
    SwapMove(int swapCore1Position, int swapCore2Position);
    // END - Functions ------------ //

    // BEGIN - Properties ------------ //
    int corePositionToSwap1;
    int corePositionToSwap2;
    // END - Properties ------------ /
};

#endif // SWAPMOVE_H
