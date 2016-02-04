//=================================================================================================
// Name        : xmlcoregraphparser.cpp
// Author      : Muhammad Obaidullah
// Version     : 0.1
// Copyright   : Electrical & Computer Engineering, Ryerson University ©2015
// Description : XML Core Graph parser class which is used to parse the input core graph XML then
//               create communication edges and core graph objects to use in optimization
//               algorithm
//=================================================================================================

#include <xmlcoregraphparser.h>
#include <QFileDialog>

// ---------------------------------------------------------------------------------------------------------------------------
//
//	Function:		XMLCoreGraphParser CONSTRUCTOR
// 	Purpose:		Constructs an object of class XMLCoreGraphParser to generate core graph objects out of core graph XML
// 	Parameters: 	XmlAsString - Input XML as a form of string
//	Returns:		nothing
//
// ---------------------------------------------------------------------------------------------------------------------------
XMLCoreGraphParser::XMLCoreGraphParser()
{
    // Do nothing
}

// ---------------------------------------------------------------------------------------------------------------------------
//
//	Function:		generateCoreGraphFromString
// 	Purpose:		Generates a list of objects of CoreGraph from the input string to represent each application mode
//                  in one application
// 	Parameters: 	XmlAsString - Input XML as a form of string
//	Returns:        Application object containing vector of core graph objects
//
// ---------------------------------------------------------------------------------------------------------------------------
Application XMLCoreGraphParser::generateCoreGraphFromString(string xmlAsString)
{
    // Creating a document from string
    QDomDocument document;

    // Making file from string
    if(!document.setContent(QString::fromStdString(xmlAsString)))
    {
        cout<<"Failed to create document from string.";
    }
    return parseDocument(document);
}

// ---------------------------------------------------------------------------------------------------------------------------
//
//	Function:		generateCoreGraphFromFile
// 	Purpose:		Generates a list of objects of CoreGraph from the input file location to represent each application mode
//                  in one application
// 	Parameters: 	filePath - Input XML file path
//	Returns:        Application object containing vector of core graph objects
//
// ---------------------------------------------------------------------------------------------------------------------------
Application XMLCoreGraphParser::generateCoreGraphFromFile(string filePath)
{
    cout << "Opening XML File: " << filePath << endl;
    // Create a document from file path
    QDomDocument document;

    // Open a file for reading
    QFile file(QString::fromStdString(filePath));

    if(!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        cout<<"Failed to open the file for reading.";
    }
    else
    {
        // Loading file
        if(!document.setContent(&file))
        {
            cout<<"Failed to load the file for reading.";
        }
        file.close();
    }
    return parseDocument(document);
}

// ---------------------------------------------------------------------------------------------------------------------------
//
//	Function:		parseDocument
// 	Purpose:		Generates a list of objects of CoreGraph from the input QDomDocument object to represent each application
//                  mode in one application
// 	Parameters: 	aDocToParse - Input a QDomDocument object filled up with XML as content
//	Returns:        Application object containing vector of core graph objects
//
// ---------------------------------------------------------------------------------------------------------------------------
Application XMLCoreGraphParser::parseDocument(QDomDocument aDocToParse)
{
    Application parsedApp;
    vector<CoreGraph> allApplicationModes;
    // Getting root element
    QDomElement applicationElement = aDocToParse.firstChildElement();
    int appId       = stoi(applicationElement.attribute(AttributeId).toStdString());
    string appName  = applicationElement.attribute(AttributeName).toStdString();
    parsedApp.Id = appId;
    parsedApp.Name = appName;
    if(applicationElement.tagName().toStdString() == elementRootTagName.toStdString())
    {
        QDomNodeList rootCoresNode = applicationElement.elementsByTagName(elementCoresRootTagName);
        QDomNodeList coreNodes = rootCoresNode.at(0).toElement().elementsByTagName(elementCoreTagName);
        cout<<"No. of Cores: "<<coreNodes.count()<<endl;

        for(int coreNo = 0; coreNo < coreNodes.count(); coreNo++)
        {
            // Create cores
            QDomElement coreElement = coreNodes.at(coreNo).toElement();
            string coreId = coreElement.attribute(AttributeId).toStdString();
            string coreName = coreElement.attribute(AttributeName).toStdString();
            Core aCore(stoi(coreId),coreName);
            parsedApp.Cores.push_back(aCore);
            // Print core object
            // cout << aCore.toString();
        }

        try
        {
            // printElementsInside(coreNodes);
            QDomNodeList rootCoreGraphNodes = applicationElement.elementsByTagName(elementApplicatonModeTagName);
            for (int applicationMode = 0; applicationMode < rootCoreGraphNodes.count(); applicationMode++)
            {
                vector<CommunicationEdge> allCommunicationEdges;
                QDomNodeList rootEdgesNode = rootCoreGraphNodes.at(0).toElement().elementsByTagName(elementEdgesRootTagName);
                QDomNodeList edgeNodes = rootEdgesNode.at(0).toElement().elementsByTagName(elementEdgesTagName);
                QDomElement applicationModeElement = rootCoreGraphNodes.at(applicationMode).toElement();
                int modeId = stoi(applicationModeElement.attribute(AttributeId).toStdString());
                string modeName = applicationModeElement.attribute(AttributeName).toStdString();
                for(int edge = 0; edge < edgeNodes.count(); edge++)
                {
                    QDomElement edgeElement = edgeNodes.at(edge).toElement();
                    int edgeId = stoi(edgeElement.attribute(AttributeId).toStdString());
                    float volume = stof(edgeElement.attribute(AttributeVolume).toStdString());
                    int fromVertex = stoi(edgeElement.attribute(AttributeFrom).toStdString());
                    int toVertex = stoi(edgeElement.attribute(AttributeTo).toStdString());
                    CommunicationEdge cEdge(edgeId,volume,fromVertex,toVertex);
                    allCommunicationEdges.push_back(cEdge);
                }
                CoreGraph applicationMode(modeId,coreNodes.count(),modeName,allCommunicationEdges);
                allApplicationModes.push_back(applicationMode);
                // cout << applicationMode.toString();
            }
            // printElementsInside(edgeNodes);
            cout<<"Reading finished..." << endl;
        }
        catch(exception e)
        {
           cout << e.what();
        }

        parsedApp.Modes = allApplicationModes;
        //allApplicationModes.push_back();
        return parsedApp;
    }
    else
    {
        return parsedApp;
    }
}

void XMLCoreGraphParser::printElementsInside(QDomNodeList root)
{
    for(int i = 0; i < root.count(); i++)
    {
        QDomNode elm = root.at(i);
        if(elm.isElement())
        {
            QDomElement e = elm.toElement();
            cout<<"with "<<e.attributes().count()<<" attributes."<<endl;
        }
    }
}
