#ifndef COMMUNICATIONEDGE_H
#define COMMUNICATIONEDGE_H


class CommunicationEdge
{
public:
    CommunicationEdge(int edgeID, float communicationVolume, int sourceVertex, int destinationVertex);
    int ID;
    float Volume;
    int SourceID;
    int DestinationID;

};

#endif // COMMUNICATIONEDGE_H
