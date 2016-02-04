//=================================================================================================
// Name        : application.h
// Author      : Muhammad Obaidullah
// Version     : 0.1
// Copyright   : Electrical & Computer Engineering, Ryerson University ©2015
// Description : Application class which represents an application object containing all
//               application modes and communication structure for each mode.
//=================================================================================================

#ifndef APPLICATION_H
#define APPLICATION_H
#include <iostream>
#include <sstream>
#include <coregraph.h>
#include <core.h>

using namespace std;

class Application
{
public:
    // BEGIN - Functions ------------ //
    Application();
    Application(int Id, string applicationName);
    string Application::toString();

    template <typename T>

    string convertToString(T val)
    {
        stringstream stream;
        stream << val;
        return stream.str();
    }
    // END - Functions ------------ //

    // BEGIN - Properties ------------ //
    int Id;
    string Name;
    vector<CoreGraph> Modes;
    vector<Core> Cores;
    // END - Properties ------------ //
};

#endif // APPLICATION_H
