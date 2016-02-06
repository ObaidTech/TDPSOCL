#ifndef XMLCOREGRAPHPARSER_H
#define XMLCOREGRAPHPARSER_H
#include <coregraph.h>
#include <communicationedge.h>
#include <list>
#include <QtXml>
#include <core.h>
#include <application.h>

using namespace std;

// BEGIN - Constants ------------ //
static const QString elementRootTagName = QString::fromStdString("Application");
static const QString elementCoresRootTagName = QString::fromStdString("Cores");
static const QString elementCoreTagName = QString::fromStdString("Core");
static const QString elementApplicatonModeTagName = QString::fromStdString("CoreGraph");
static const QString elementEdgesRootTagName = QString::fromStdString("Edges");
static const QString elementEdgesTagName = QString::fromStdString("Edge");
static const QString AttributeId = QString::fromStdString("Id");
static const QString AttributeName = QString::fromStdString("Name");
static const QString AttributeFrom = QString::fromStdString("From");
static const QString AttributeTo = QString::fromStdString("To");
static const QString AttributeVolume = QString::fromStdString("Volume");
// END - Constants ------------ //

class XMLCoreGraphParser
{
public:
    // BEGIN - Functions ------------ //
    XMLCoreGraphParser();
    Application generateCoreGraphFromString(string xmlAsString);
    Application generateCoreGraphFromFile(string filePath);
    Application parseDocument(QDomDocument aDocToParse);
    void printElementsInside(QDomNodeList root);
    // END - Functions ------------ //

    // BEGIN - Properties ------------ //
    string error;
    // END - Properties ------------ //
};

#endif // XMLCOREGRAPHPARSER_H
