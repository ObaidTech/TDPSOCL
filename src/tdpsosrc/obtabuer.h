//=================================================================================================
// Name        : obtabuer.h
// Author      : Muhammad Obaidullah
// Version     : 0.1
// Copyright   : Electrical & Computer Engineering, Ryerson University ©2015
// Description : Tabuer class which stores all tabu-ed core arrangements and proposes new moves
//               based on proposed moves.
//=================================================================================================

#ifndef OBTABUER_H
#define OBTABUER_H
#include "vector"
#include "swapmove.h"
#include "math.h"

enum DeflectionType
{
    xAxisLine,
    yAxisLine,
    yEqualsxLine,
    yEqualsMinusxLine,
    reverse
};

using namespace std;

class OBTabuer
{
public:
    // BEGIN - Functions ------------ //
    OBTabuer();
    OBTabuer(int topologyWidth, int topologyHeight);
    void addToTabuList(vector<int> CoreArrangementToTabu);
    bool isTabued(vector<int> move);
    bool isSame(vector<int> oneMove, vector<int> anotherMove);
    bool isMoveApplicable(vector<int> coreArrangment, SwapMove moveToApply);
    SwapMove deflectMove(SwapMove initialMove, DeflectionType aLineToDeflectOn);
    SwapMove proposeMove(SwapMove initialMove, vector<int> particleCoreArrangement);
    // END - Functions ------------ //

    // BEGIN - Properties ------------ //
    int meshWidth;
    int meshHeight;
    vector<DeflectionType> allDeflectionTypes;
    // END - Properties ------------ //

private:
    // BEGIN - Properties ------------ //
    vector<vector<int>> allTabuedCoreArrangments;
    // END - Properties ------------ //
};

#endif // OBTABUER_H
