//=================================================================================================
// Name        : application.cpp
// Author      : Muhammad Obaidullah
// Version     : 0.1
// Copyright   : Electrical & Computer Engineering, Ryerson University ©2015
// Description : Application class which represents an application object containing all
//               application modes and communication structure for each mode.
//=================================================================================================

#include "application.h"

using namespace std;

// ---------------------------------------------------------------------------------------------------------------------------
//
//	Function:		Application CONSTRUCTOR
// 	Purpose:		Constructs an object of class Application to represent a complete Application object to be optimized
//                  or simulated or evaluated
// 	Parameters: 	nothing
//	Returns:		nothing
//
// ---------------------------------------------------------------------------------------------------------------------------
Application::Application()
{

}

// ---------------------------------------------------------------------------------------------------------------------------
//
//	Function:		Application CONSTRUCTOR
// 	Purpose:		Constructs an object of class Application to represent a complete Application object to be optimized
//                  or simulated or evaluated
// 	Parameters: 	applicationId   - Unique integer identifier for an application
//                  applicationName - String application name
//	Returns:		nothing
//
// ---------------------------------------------------------------------------------------------------------------------------
Application::Application(int applicationId, string applicationName)
{
    this->Id = applicationId;
    this->Name = applicationName;
}

// ---------------------------------------------------------------------------------------------------------------------------
//
//	Function:		toString
// 	Purpose:		Creates a string to briefly describe the application object
// 	Parameters: 	nothing
//	Returns:		Printable string describing the application
//
// ---------------------------------------------------------------------------------------------------------------------------
string Application::toString()
{
    std::stringstream ss;
    ss << "=========== BEGIN APPLICATION ===========" << endl;
    ss << "Application Id: " << this->convertToString(this->Id) << " Application Name: " << this->Name << endl;
    ss << "----------- BEGIN CORES -----------" << endl;
    for(int coreNo = 0; coreNo < this->Cores.size(); coreNo++)
    {
        Core aCore = this->Cores.at(coreNo);
        ss << aCore.toString();
    }
    ss << "----------- END CORES -----------" << endl;
    ss << "----------- BEGIN MODES -----------" << endl;
    for(int modeNo = 0; modeNo < this->Modes.size(); modeNo++)
    {
        CoreGraph aMode = this->Modes.at(modeNo);
        ss << aMode.toString();
    }
    ss << "----------- END MODES -----------" << endl;
    ss << "=========== END APPLICATION ===========" << endl;
    return ss.str();
}

