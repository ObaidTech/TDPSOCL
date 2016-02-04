#ifndef MAINVIEW_H
#define MAINVIEW_H

#include <QMainWindow>
#include <QGridLayout>
#include <QLayoutItem>
#include <QWidget>
#include <QTimer>
#include <qcustomplot.h> // the header file of QCustomPlot. Don't forget to add it to your project, if you use an IDE, so it gets compiled.
#include <iostream>
#include <particle.h>
#include <QtXml>
#include <QMessageBox>
#include <QDebug>
#include <q_debugstream.h>
#include <iostream>
#include <QStringList>
#include <QStringListModel>
#include <QTableView>
#include <QStandardItemModel>
#include <QPushButton>
#include <QGridLayout>
#include <QLayoutItem>
#include <QWidget>
#include <QDesktopWidget>
#include <QScreen>
#include <QMessageBox>
#include <QMetaEnum>
#include <QFileDialog>
#include <xmlcoregraphparser.h>
#include <application.h>
#include <communicationedge.h>
#include <vector>
#include "Matrix.hpp"
#include <oboptimizer.h>
#include <math.h>
#include <thread>
#include <reading.h>
#include <readingdb.h>

namespace Ui {
class MainVIew;
}

class MainVIew : public QMainWindow
{
    Q_OBJECT

public:
    // BEGIN - Functions ------------ //
    explicit MainVIew(QWidget *parent = 0);
    void MainVIew::deleteChildWidgets(QLayoutItem *item);
    void MainVIew::removeGridChildren(QGridLayout *layout, int row, int column, bool deleteWidgets);
    void MainVIew::setupScatterStyleDemo(QCustomPlot *customPlot);
    void MainVIew::plotParticleCosts(std::vector<Particle>* particlesToPlot);
    void MainVIew::printElementsInside(QDomNodeList root);
    void MainVIew::generateTreeViewFromApp(Application anApp);
    void MainVIew::printAllTrafficMatrices(Application anApp);
    void MainVIew::makeListOfParticles(QStringListModel* mod);
    void MainVIew::onIteratedAlgorithm(Application changeApplication, int iterNo);
    QTreeWidgetItem* MainVIew::addTreeRoot(QString name, QString description);
    QTreeWidgetItem* MainVIew::addTreeChild(QTreeWidgetItem *parent, QString name, QString description);
    void MainVIew::plotGlobalCosts(std::vector<double>* allGlobalCosts);
    void MainVIew::updateCurrentGenerationPlot(std::vector<Particle>* particlesToPlot);
    void MainVIew::clearCurrentGenerationPlot();
    void MainVIew::updateGlobalCostPlot();
    void MainVIew::clearGlobalCostPlot();
    void MainVIew::makeListOfParticles(std::vector<Particle>* particlesToShow);
    ~MainVIew();
    // END - Functions ------------ //

    // BEGIN - Properties ------------ //
    Application appToOptimize;
    std::thread OptimizationThread;
    QMutex dataMutex;
    // END - Properties ------------ //

public slots:
    void slotForOptimizationStarted();
    void slotForOptimizerIterated(int IterationNo, Application* app, vector<Particle>* particleList, Particle* globalBestParticle);
    void slotForOptimizationFinished();
    void postOutput(string str);

private slots:
    void on_runButton_clicked();
    void on_particleList_clicked(const QModelIndex &index);
    void on_importApplicationBtn_clicked();

    void on_drawParticlesCheckBox_toggled(bool checked);

    void on_optimizationTechniqueComboBox_currentIndexChanged(int index);

    void on_runButton_3_clicked();

private:
    Ui::MainVIew *ui;
};

#endif // MAINVIEW_H
