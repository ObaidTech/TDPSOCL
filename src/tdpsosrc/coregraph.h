//=================================================================================================
// Name        : CoreGraph.h
// Author      : Muhammad Obaidullah
// Version     : 0.1
// Copyright   : Electrical & Computer Engineering, Ryerson University ©2015
// Description : Core Graph class which stores an application mode structure
//=================================================================================================

#ifndef COREGRAPH_H_
#define COREGRAPH_H_
#include <string>
#include <vector>
#include <communicationedge.h>
#include <sstream>
#include <algorithm>

using namespace std;

class CoreGraph {
public:
	// BEGIN - Functions
    CoreGraph();
    CoreGraph(int modeID, int numOfCores, string modeName,  std::vector<CommunicationEdge> communicationEdges);
	virtual ~CoreGraph();
    int getTrafficMatrix();
    string toString();
    vector<int> getCoresUsed();

    template <typename T>

    string convertToString(T val)
    {
        stringstream stream;
        stream << val;
        return stream.str();
    }
	// END - Functions

	// BEGIN - Properties
    int ID;
    int NoOfCores;
    string Name;
    std::vector<CommunicationEdge> Edges;
	// END - Properties

};
#endif /* COREGRAPH_H_ */
