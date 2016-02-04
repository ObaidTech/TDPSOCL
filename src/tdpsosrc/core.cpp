//=================================================================================================
// Name        : core.cpp
// Author      : Muhammad Obaidullah
// Version     : 0.1
// Copyright   : Electrical & Computer Engineering, Ryerson University ©2015
// Description : Core class which represents a core object
//=================================================================================================

#include "core.h"
#include "string.h"

// ---------------------------------------------------------------------------------------------------------------------------
//
//	Function:		Core CONSTRUCTOR
// 	Purpose:		Constructs an object of class Core to generate a core object to be mapped or simulated or evaluated
// 	Parameters: 	coreId      - Unique integer identifier for a core
//                  coreName    - String core name
//	Returns:		nothing
//
// ---------------------------------------------------------------------------------------------------------------------------
Core::Core(int coreId, string coreName)
{
    this->Id = coreId;
    this->Name = coreName;
}

// ---------------------------------------------------------------------------------------------------------------------------
//
//	Function:		toString
// 	Purpose:		Creates a string to briefly describe the core object
// 	Parameters: 	nothing
//	Returns:		Printable string describing the core
//
// ---------------------------------------------------------------------------------------------------------------------------
string Core::toString()
{
    std::stringstream ss;
    ss << "Core Id: " << this->convertToString(this->Id) << " Name: " << this->Name << endl;
    return ss.str();
}


