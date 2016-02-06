//=================================================================================================
// Name        : oboptimizer.h
// Author      : Muhammad Obaidullah
// Version     : 0.1
// Copyright   : Electrical & Computer Engineering, Ryerson University ©2015
// Description : OBOptimizer singleton class which allows many different optimization techniques
//               to be run on the application object
//=================================================================================================

#ifndef OBOPTIMIZER_H
#define OBOPTIMIZER_H
#include <vector>
#include <iostream>
#include <sstream>
#include <application.h>
#include <coregraph.h>
#include <communicationedge.h>
#include <core.h>
#include <math.h>
#include <swapmove.h>
#include <mainview.h>
// #include <ui_mainview.h>
#include <QObject>
#include <reading.h>
#include <readingdb.h>
#include <particle.h>
#include <obtabuer.h>

using namespace std;

enum RoutingType
{
    XY,
    YX,
    WestFirst,
    NorthLast,
    NegativeFirst
};

enum OptimizationAlgorithm
{
    DPSO,
    TDPSO
};


class OBOptimizer : public QObject
{
    Q_OBJECT

public:
    // BEGIN - Functions ------------ //
    static OBOptimizer* Instance();
    void iterate(vector<Particle> *oldParticles, OptimizationAlgorithm algorithm, bool firstIteration);
    float getEuclideanDistance(vector<Particle>);
    vector<Particle> generateParticles(int noOfParticles);
    void evaluateCost(vector<Particle>* particlesToEvaluate);
    int getCorePositionInParticle(int coreID, Particle p);
    Particle* getBestCostParticle(vector<Particle>* allParticles);
    vector<SwapMove> getSwapMoves(Particle sourceParticle, Particle destinationParticle);
    void run();
    void updateParticleLocalCost(vector<Particle>* allParticles);
    vector<SwapMove> getSwapMoves(vector<int> sourceCoreArrangement, vector<int> destinationCoreArrangement);
    void moveParticle(Particle* aParticle);
    void applySwapMoves(vector<SwapMove> swaps, Particle* aParticle);
    int getCorePositionInCoreArrangment(int coreIdToFind, vector<int> searchSpace);
    void plotParticleCosts(std::vector<Particle>* particlesToPlot);
    void plotGlobalCosts(std::vector<double>* allGlobalCosts);
    void makeListOfParticles();
    ReadingDB* findDBForParticle(int partID);
    void updateTabuList();
    // END - Functions ------------ //

    // BEGIN - Properties ------------ //
    Application appToOptimize;
    vector<int> appModesToOptimize;
    RoutingType routingTypeToOptimize;
    int meshWidth;
    int meshHeight;
    double ParticleInertia;
    double ParticleSelfConfidence;
    double SwarmConfidence;
    Particle GlobalBestParticle;
    vector<Particle> optimizationParticles;
    int iterationsToRun;
    OptimizationAlgorithm algorithmToRun;
    vector<Reading> allGlobalBestCosts;
    vector<ReadingDB> allParticleCosts;
    bool recordAllParticles;
    // This object is used to lock optmizer thread out of accessing sensitve objects which are being accessed by GUI thread
    QMutex* dataUpdateMutexPointer;
    // This object deflects proposed moves accoring to tabu-ed list
    OBTabuer tabuer;


    // vector<double> aParticleCost1;
    // vector<double> aParticleCost2;
    // bool drawOtherParticles;
    // void (*iteratedCallBackFunction)(Application changedApplication, int iterNo);
    // QCustomPlot* globalCostsPlot;
    // QCustomPlot* generationPlot;
    // QListView* particlesView;
    // END - Properties ------------ //

private:
    // BEGIN - Functions ------------ //
    OBOptimizer();
    CoreGraph getModeFromModeNo(int ModeNo);
    // END - Functions ------------ //

    // BEGIN - Properties ------------ //
    bool optimizationRunning;
    static OBOptimizer* m_pInstance;
    // END - Properties ------------ //

signals:
    void signalOptimizationStarted();
    void signalIterated(int IterationNo, Application* app, vector<Particle>* particleList, Particle* globalBestParticle);
    void signalOptimizationFinished();
    void signalOutput(string str);
};

#endif // OBOPTIMIZER_H
