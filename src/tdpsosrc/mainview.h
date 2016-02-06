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
    void deleteChildWidgets(QLayoutItem *item);
    void removeGridChildren(QGridLayout *layout, int row, int column, bool deleteWidgets);
    void setupScatterStyleDemo(QCustomPlot *customPlot);
    void plotParticleCosts(std::vector<Particle>* particlesToPlot);
    void printElementsInside(QDomNodeList root);
    void generateTreeViewFromApp(Application anApp);
    void printAllTrafficMatrices(Application anApp);
    void makeListOfParticles(QStringListModel* mod);
    void onIteratedAlgorithm(Application changeApplication, int iterNo);
    QTreeWidgetItem* addTreeRoot(QString name, QString description);
    QTreeWidgetItem* addTreeChild(QTreeWidgetItem *parent, QString name, QString description);
    void plotGlobalCosts(std::vector<double>* allGlobalCosts);
    void updateCurrentGenerationPlot(std::vector<Particle>* particlesToPlot);
    void clearCurrentGenerationPlot();
    void updateGlobalCostPlot();
    void clearGlobalCostPlot();
    void makeListOfParticles(std::vector<Particle>* particlesToShow);
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
