//=================================================================================================
// Name        : core.h
// Author      : Muhammad Obaidullah
// Version     : 0.1
// Copyright   : Electrical & Computer Engineering, Ryerson University ©2015
// Description : Core class which represents a core object
//=================================================================================================

#ifndef CORE_H
#define CORE_H
#include <iostream>
#include <sstream>

using namespace std;

class Core
{
public:
    // BEGIN - Functions ------------ //
    Core(int coreId, string coreName);
    string Core::toString();


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
    // END - Properties ------------ //
};

#endif // CORE_H
