#include "mainview.h"
#include "ui_mainview.h"

using namespace std;

MainVIew::MainVIew(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainVIew)
{
    ui->setupUi(this);
    QPalette p = ui->logTextBox->palette();
    p.setColor(QPalette::Base, QColor(42, 40, 34));
    ui->logTextBox->setPalette(p);
    ui->logTextBox->setTextColor(QColor(243,242,241));
    setupScatterStyleDemo(ui->customPlot);

    // Tell the optimizer that I have your callback function
    // OBOptimizer::Instance()->iteratedCallBackFunction = &MainVIew::onIteratedAlgorithm;
    // OBOptimizer::Instance()->myParent = ui;

    // Link GUi to OBOptimizer
    // OBOptimizer::Instance()->globalCostsPlot = ui->iterationPlot;
    // OBOptimizer::Instance()->generationPlot = ui->customPlot;
    // OBOptimizer::Instance()->particlesView = ui->particleList;
    QObject::connect(OBOptimizer::Instance(),SIGNAL(signalIterated(int, Application*, vector<Particle>*, Particle*)),this,SLOT(slotForOptimizerIterated(int, Application*, vector<Particle>*, Particle*)));
    QObject::connect(OBOptimizer::Instance(),SIGNAL(signalOptimizationStarted()),this,SLOT(slotForOptimizationStarted()));
    QObject::connect(OBOptimizer::Instance(),SIGNAL(signalOptimizationFinished()),this,SLOT(slotForOptimizationFinished()));
    QObject::connect(OBOptimizer::Instance(),SIGNAL(signalOutput()),this,SLOT(postOutput()));

    // Give my buddy a lock object to hang onto
    OBOptimizer::Instance()->dataUpdateMutexPointer = &this->dataMutex;
}

MainVIew::~MainVIew()
{
    delete ui;
    OptimizationThread.join();
}

void MainVIew::on_runButton_clicked()
{
    /*
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, "Test", "Quit?",QMessageBox::Yes|QMessageBox::No);
    if (reply == QMessageBox::Yes) {
      qDebug() << "Yes was clicked";
      QApplication::quit();
    } else {
      qDebug() << "Yes was *not* clicked";
    }
    */
    try
    {
        QDebugStream qout(std::cout, ui->logTextBox); //Redirect Console output to logTextBox
        cout<< "Initializing Search Space..." << endl;
        int noOfParticles = stoi(ui->noOfParticlesBox->text().toStdString());
        int particleSize = stoi(ui->pWidthBox->text().toStdString()) * stoi(ui->pHeightBox->text().toStdString());
        int noOfIteration = stoi(ui->noOfIterations->text().toStdString());

        // Setting things before generating particles
        OBOptimizer::Instance()->meshWidth = stoi(ui->pWidthBox->text().toStdString());
        OBOptimizer::Instance()->meshHeight = stoi(ui->pHeightBox->text().toStdString());
        OBOptimizer::Instance()->routingTypeToOptimize = XY;
        OBOptimizer::Instance()->ParticleInertia = stod(ui->inertiaBox->text().toStdString());
        OBOptimizer::Instance()->ParticleSelfConfidence = stod(ui->selfConfidenceBox->text().toStdString());
        OBOptimizer::Instance()->SwarmConfidence = stod(ui->swarmConfidenceBox->text().toStdString());

        // Generating particles
        OBOptimizer::Instance()->generateParticles(noOfParticles);

        cout << "Going to run " << noOfIteration << " iterations." << endl;
        OBOptimizer::Instance()->iterationsToRun = noOfIteration;
        // OBOptimizer::Instance()->algorithmToRun = OptimizationAlgorithm::DPSO;
        if(OptimizationThread.joinable())
        {
            OptimizationThread.join();
        }
        // Run Optimization for number of iterations specified in GUI
        OptimizationThread = std::thread(&OBOptimizer::run, OBOptimizer::Instance());
        // OBOptimizer::Instance()->run();
    }
    catch(exception e)
    {
        cout << e.what() << endl;
    }
}

void MainVIew::onIteratedAlgorithm(Application changeApplication, int iterationNo)
{
    /*
    cout << "Iteration No. "<< iterationNo << "done." << endl;

    QStringListModel *model = new QStringListModel();
    QStringList List;
    // Plotting Current Generation Statistics
    for(int i = 0; i < OBOptimizer::Instance()->optimizationParticles.size(); i++)
    {
        Particle p = OBOptimizer::Instance()->optimizationParticles.at(i);
        List << QString("Particle %0").arg(p.ParticleID);
    }

    // Populate our model
    model->setStringList(List);
    parent->makeListOfParticles(model);

    // Plotting current generation statistics
    parent->plotParticleCosts(&OBOptimizer::Instance()->optimizationParticles);

    // Plotting overall iteration statistics
    parent->plotGlobalCosts(&OBOptimizer::Instance()->allGlobalBestCosts);
    */
}

void MainVIew::makeListOfParticles(QStringListModel* mod)
{
    /*
    MainVIew.ui->particleList->setModel(model);
    */
}

void MainVIew::on_particleList_clicked(const QModelIndex &index)
{
    // QMessageBox::information(this, "Test",  QString("Particle %0").arg(index.row()),QMessageBox::Ok);
    Particle selectedParticle = OBOptimizer::Instance()->optimizationParticles[index.row()];
    QStandardItemModel *model = new QStandardItemModel(4,1,this); //4 Rows and 2 Columns

    // Print Column Headers
    model->setHorizontalHeaderItem(0, new QStandardItem(QString("Value")));

    // Print Row Headers
    model->setVerticalHeaderItem(0, new QStandardItem(QString("ID")));
    model->setVerticalHeaderItem(1, new QStandardItem(QString("Cost")));
    model->setVerticalHeaderItem(2, new QStandardItem(QString("Size")));
    model->setVerticalHeaderItem(3, new QStandardItem(QString("-")));

    // Print Properties
    // Particle ID Property
    QStandardItem *ParticleValue1item = new QStandardItem(QString("%0").arg(selectedParticle.ParticleID));
    model->setItem(0,0,ParticleValue1item);

    // Particle Cost Property
    QStandardItem *ParticleValue2item = new QStandardItem(QString("%0").arg(selectedParticle.CurrentCost));
    model->setItem(1,0,ParticleValue2item);

    // Particle Size Property
    QStandardItem *ParticleValue3item = new QStandardItem(QString("%0").arg(selectedParticle.Size));
    model->setItem(2,0,ParticleValue3item);

    ui->particlePropertiesView->setModel(model);

    // Clear grid
    for(int i = 0;i<ui->particleDisplay->columnCount();i++){
        for(int j = 0;j<ui->particleDisplay->rowCount();j++){
            removeGridChildren(ui->particleDisplay,i,j,true);
        }
    }

    // Populate grid
    for(int i = 0; i < selectedParticle.Size; i++)
    {
        QLabel *b = new QLabel(QString("%0").arg(selectedParticle.CoreArrangement[i]));
        int Width = sqrt(selectedParticle.Size);
        int Height = sqrt(selectedParticle.Size);
        int row = i/Width;
        int col = i - (row*Height);
        ui->particleDisplay->addWidget(b,row,col,1,1);

        b->setFrameStyle(QFrame::StyledPanel);
        b->setLineWidth(1);
        b->setAlignment(Qt::AlignCenter);
    }
}


/**
 * Helper function. Deletes all child widgets of the given layout @a item.
 */
void MainVIew::deleteChildWidgets(QLayoutItem *item) {
    if (item->layout()) {
        // Process all child items recursively.
        for (int i = 0; i < item->layout()->count(); i++) {
            deleteChildWidgets(item->layout()->itemAt(i));
        }
    }
    delete item->widget();
}

/**
 * Helper function. Removes all layout items within the given layout
 * which either span the given row or column. If deleteWidgets
 * is true, all concerned child widgets become not only removed from the
 * layout, but also deleted.
 */
void MainVIew::removeGridChildren(QGridLayout *layout, int row, int column, bool deleteWidgets) {
    // We avoid usage of QGridLayout::itemAtPosition() here to improve performance.
    for (int i = layout->count() - 1; i >= 0; i--) {
        int r, c, rs, cs;
        layout->getItemPosition(i, &r, &c, &rs, &cs);
        if ((r <= row && r + rs - 1 >= row) || (c <= column && c + cs - 1 >= column)) {
            // This layout item is subject to deletion.
            QLayoutItem *item = layout->takeAt(i);
            if (deleteWidgets) {
                deleteChildWidgets(item);
            }
            delete item;
        }
    }
}

void MainVIew::plotParticleCosts(std::vector<Particle>* particlesToPlot)
{
    QCustomPlot *customPlot = this->ui->customPlot;
    // Clear Everything First
    customPlot->clearGraphs();
    customPlot->clearItems();
    customPlot->clearMask();
    customPlot->clearPlottables();
    customPlot->repaint();

    // Setting up Graph
    customPlot->legend->setVisible(true);
    customPlot->legend->setFont(QFont("Helvetica", 9));
    customPlot->legend->setRowSpacing(-3);
    QVector<QCPScatterStyle::ScatterShape> shapes;
    shapes << QCPScatterStyle::ssDot;

    // Drawing curve
    QPen pen;
    customPlot->addGraph();
    pen.setColor(QColor(255,25,25,255));
    // generate data:
    QVector<double> IDs(particlesToPlot->size()), Costs(particlesToPlot->size());
    for (int dataIndex = 0; dataIndex < particlesToPlot->size(); dataIndex++)
    {
        Particle* p = &particlesToPlot->at(dataIndex);
        IDs[dataIndex] = (double)(p->ParticleID);
        Costs[dataIndex] = (double)(p->CurrentCost);
        // QMessageBox::information(this, "Test",  QString("ID: %0, Cost: %1").arg(IDs[dataIndex]).arg(Costs[dataIndex]),QMessageBox::Ok);
    }

    // Setting data
    customPlot->graph()->setData(IDs, Costs);
    customPlot->graph()->rescaleAxes(true);
    customPlot->graph()->setPen(pen);
    customPlot->graph()->setName("Cost");
    customPlot->graph()->setLineStyle(QCPGraph::lsLine);

    // Set scatter style
    customPlot->graph()->setScatterStyle(QCPScatterStyle::ssCircle);

    // Set axis parameters
    customPlot->rescaleAxes();
    customPlot->xAxis->setTicks(true);
    customPlot->yAxis->setTicks(true);
    customPlot->xAxis->setTickLabels(true);
    customPlot->yAxis->setTickLabels(true);
    customPlot->xAxis->setLabel("Particle ID");
    customPlot->yAxis->setLabel("Cost");

    // Make top right axes clones of bottom left axes:
    customPlot->axisRect()->setupFullAxesBox();

    // Refresh plot view
    customPlot->replot();

    // Log to UI
    cout<<"All Particles Cost Graph Drawn...";
}

void MainVIew::setupScatterStyleDemo(QCustomPlot *customPlot)
{
  string demoName = "Scatter Style Demo";
  customPlot->legend->setVisible(true);
  customPlot->legend->setFont(QFont("Helvetica", 9));
  customPlot->legend->setRowSpacing(-3);
  QVector<QCPScatterStyle::ScatterShape> shapes;
  shapes << QCPScatterStyle::ssCross;
  shapes << QCPScatterStyle::ssPlus;
  shapes << QCPScatterStyle::ssCircle;
  shapes << QCPScatterStyle::ssDisc;
  shapes << QCPScatterStyle::ssSquare;
  shapes << QCPScatterStyle::ssDiamond;
  shapes << QCPScatterStyle::ssStar;
  shapes << QCPScatterStyle::ssTriangle;
  shapes << QCPScatterStyle::ssTriangleInverted;
  shapes << QCPScatterStyle::ssCrossSquare;
  shapes << QCPScatterStyle::ssPlusSquare;
  shapes << QCPScatterStyle::ssCrossCircle;
  shapes << QCPScatterStyle::ssPlusCircle;
  shapes << QCPScatterStyle::ssPeace;
  shapes << QCPScatterStyle::ssCustom;

  QPen pen;
  // add graphs with different scatter styles:
  for (int i=0; i<shapes.size(); ++i)
  {
    customPlot->addGraph();
    pen.setColor(QColor(qSin(i*0.3)*100+100, qSin(i*0.6+0.7)*100+100, qSin(i*0.4+0.6)*100+100));
    // generate data:
    QVector<double> x(10), y(10);
    for (int k=0; k<10; ++k)
    {
      x[k] = k/10.0 * 4*3.14 + 0.01;
      y[k] = 7*qSin(x[k])/x[k] + (shapes.size()-i)*5;
    }
    customPlot->graph()->setData(x, y);
    customPlot->graph()->rescaleAxes(true);
    customPlot->graph()->setPen(pen);
    customPlot->graph()->setName(QCPScatterStyle::staticMetaObject.enumerator(QCPScatterStyle::staticMetaObject.indexOfEnumerator("ScatterShape")).valueToKey(shapes.at(i)));
    customPlot->graph()->setLineStyle(QCPGraph::lsLine);
    // set scatter style:
    if (shapes.at(i) != QCPScatterStyle::ssCustom)
    {
      customPlot->graph()->setScatterStyle(QCPScatterStyle(shapes.at(i), 10));
    }
    else
    {
      QPainterPath customScatterPath;
      for (int i=0; i<3; ++i)
        customScatterPath.cubicTo(qCos(2*M_PI*i/3.0)*9, qSin(2*M_PI*i/3.0)*9, qCos(2*M_PI*(i+0.9)/3.0)*9, qSin(2*M_PI*(i+0.9)/3.0)*9, 0, 0);
      customPlot->graph()->setScatterStyle(QCPScatterStyle(customScatterPath, QPen(Qt::black, 0), QColor(40, 70, 255, 50), 10));
    }
  }
  // set blank axis lines:
  customPlot->rescaleAxes();
  customPlot->xAxis->setTicks(false);
  customPlot->yAxis->setTicks(false);
  customPlot->xAxis->setTickLabels(false);
  customPlot->yAxis->setTickLabels(false);
  // make top right axes clones of bottom left axes:
  customPlot->axisRect()->setupFullAxesBox();
  cout<<"Graph Drawing Done...";
}

void MainVIew::plotGlobalCosts(std::vector<double>* allGlobalCosts)
{
    QCustomPlot *customPlot = ui->iterationPlot;
    // Clear Everything First
    customPlot->clearGraphs();
    customPlot->clearItems();
    customPlot->clearMask();
    customPlot->clearPlottables();
    customPlot->repaint();

    // Setting up Graph
    customPlot->legend->setVisible(true);
    customPlot->legend->setFont(QFont("Helvetica", 9));
    customPlot->legend->setRowSpacing(-3);
    QVector<QCPScatterStyle::ScatterShape> shapes;
    shapes << QCPScatterStyle::ssDot;

    // Drawing curve
    QPen pen;
    customPlot->addGraph();
    pen.setColor(QColor(255,25,25,255));
    // generate data:
    QVector<double> iterationNo(allGlobalCosts->size()), GlobalCosts(allGlobalCosts->size());
    for (int dataIndex = 0; dataIndex < allGlobalCosts->size(); dataIndex++)
    {
        iterationNo[dataIndex] = (double)(dataIndex+1);
        GlobalCosts[dataIndex] = (double)(allGlobalCosts->at(dataIndex));
        // QMessageBox::information(this, "Test",  QString("ID: %0, Cost: %1").arg(IDs[dataIndex]).arg(Costs[dataIndex]),QMessageBox::Ok);
    }

    // Setting data
    customPlot->graph()->setData(iterationNo, GlobalCosts);
    customPlot->graph()->rescaleAxes(true);
    customPlot->graph()->setPen(pen);
    customPlot->graph()->setName("Global Cost");
    customPlot->graph()->setLineStyle(QCPGraph::lsLine);

    // Set scatter style
    customPlot->graph()->setScatterStyle(QCPScatterStyle::ssCircle);

    // Set axis parameters
    customPlot->rescaleAxes();
    customPlot->xAxis->setTicks(true);
    customPlot->yAxis->setTicks(true);
    customPlot->xAxis->setTickLabels(true);
    customPlot->yAxis->setTickLabels(true);
    customPlot->xAxis->setLabel("Iteration No.");
    customPlot->yAxis->setLabel("Global Cost");

    // Make top right axes clones of bottom left axes:
    customPlot->axisRect()->setupFullAxesBox();

    // Refresh plot view
    customPlot->replot();

    // Log to UI
    cout<<"All Particles Gobal Cost Graph Drawn...";
}

void MainVIew::printElementsInside(QDomNodeList root)
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

void MainVIew::on_importApplicationBtn_clicked()
{
    QDebugStream qout(std::cout, ui->logTextBox); //Redirect Console output to logTextBox
    //get a filename to open
    QString fileName = QFileDialog::getOpenFileName(this,tr("Open Application XML File"), "../TDPSO", tr("XML Files (*.xml)"));
    if(fileName != NULL)
    {
        XMLCoreGraphParser parser;
        Application a = parser.generateCoreGraphFromFile(fileName.toStdString());
        cout << a.toString();
        ui->applicationNameBox->setText(QString::fromStdString(a.Name));
        this->appToOptimize = a;
        stringstream ss;
        ss << (int) (ceil(sqrt(a.Cores.size())));
        string str = ss.str();
        ui->pHeightBox->setText(QString::fromStdString(str));
        ui->pWidthBox->setText(QString::fromStdString(str));
        stringstream gg;
        gg << a.Cores.size();
        string stra = gg.str();
        ui->noOfParticlesBox->setText(QString::fromStdString(stra));
        generateTreeViewFromApp(a);
        cout << "Traffic Matrix: " << endl;
        printAllTrafficMatrices(a);
        // For now let's optimize just first mode
        OBOptimizer::Instance()->appModesToOptimize.push_back(0);
        OBOptimizer::Instance()->appToOptimize = a;
    }
}

void MainVIew::printAllTrafficMatrices(Application anApp)
{
    for(int i = 0; i < anApp.Modes.size(); i++)
    {
        CoreGraph c = anApp.Modes.at(i);
        // MatrixM trafficMatrix = c.getTrafficMatrix();
        // cout << trafficMatrix;
    }
}

void MainVIew::generateTreeViewFromApp(Application anApp)
{
    ui->applicationTreeWidget->clear();
    // Set the number of columns in the tree
    ui->applicationTreeWidget->setColumnCount(2);
    ui->applicationTreeWidget->setColumnWidth(0,180);
    ui->applicationTreeWidget->setColumnWidth(1,130);

    // Set the headers
    ui->applicationTreeWidget->setHeaderLabels(QStringList() << "Object" << "Properties");

    if(anApp.Cores.size() > 0)
    {
        // Create cores root node
        stringstream ss;
        ss << "(" << anApp.Cores.size() << ")";
        string str1 = ss.str();
        QTreeWidgetItem *coreRoot = addTreeRoot(QString::fromStdString("Cores"), QString::fromStdString(str1));
        coreRoot->setIcon(0, QIcon(":/Icons/images/coreIcon.png"));
        for(int coreNo = 0; coreNo < anApp.Cores.size(); coreNo++)
        {
            Core aCore = anApp.Cores.at(coreNo);
            QTreeWidgetItem *singleCore = addTreeChild(coreRoot, "Core " + QString::fromStdString(to_string(aCore.Id)), QString::fromStdString(aCore.Name));
            singleCore->setIcon(0, QIcon(":/Icons/images/singleCore.png"));
        }
        coreRoot->setExpanded(true);
        // Create application modes root node
        stringstream tt;
        tt << "(" << anApp.Modes.size() << ")";
        string str2 = tt.str();
        QTreeWidgetItem *allModesRoot = addTreeRoot(QString::fromStdString("Application Modes"), QString::fromStdString(str2));
        allModesRoot->setIcon(0, QIcon(":/Icons/images/application.png"));
        for(int modeNo = 0; modeNo < anApp.Modes.size(); modeNo++)
        {
            CoreGraph aMode = anApp.Modes.at(modeNo);
            vector<int> coresBeingUsed = aMode.getCoresUsed();
            QTreeWidgetItem *modeRoot = addTreeChild(allModesRoot, "M" + QString::fromStdString(to_string(aMode.ID)) + ": " + QString::fromStdString(aMode.Name), " Cores Used: " + QString::fromStdString(to_string(coresBeingUsed.size())));
            modeRoot->setIcon(0, QIcon(":/Icons/images/mode.png"));
            for(int edgeNo = 0; edgeNo < aMode.Edges.size(); edgeNo++)
            {
                CommunicationEdge anEdge = aMode.Edges.at(edgeNo);
                stringstream uu;
                uu << anEdge.SourceID << " --- " << anEdge.Volume << " --> " << anEdge.DestinationID;
                string str3 = uu.str();
                QTreeWidgetItem *edgeNode = addTreeChild(modeRoot, "Edge " + QString::fromStdString(to_string(anEdge.ID)), QString::fromStdString(str3));
                edgeNode->setIcon(0, QIcon(":/Icons/images/edge.png"));
            }
            modeRoot->setExpanded(true);
        }
        allModesRoot->setExpanded(true);
    }
}

QTreeWidgetItem* MainVIew::addTreeRoot(QString name, QString description)
{
    // QTreeWidgetItem(QTreeWidget * parent, int type = Type)
    QTreeWidgetItem *treeItem = new QTreeWidgetItem(ui->applicationTreeWidget);

    // QTreeWidgetItem::setText(int column, const QString & text)
    treeItem->setText(0, name);
    treeItem->setText(1, description);
    return treeItem;
}

QTreeWidgetItem* MainVIew::addTreeChild(QTreeWidgetItem *parent, QString name, QString description)
{
    // QTreeWidgetItem(QTreeWidget * parent, int type = Type)
    QTreeWidgetItem *treeItem = new QTreeWidgetItem();

    // QTreeWidgetItem::setText(int column, const QString & text)
    treeItem->setText(0, name);
    treeItem->setText(1, description);

    // QTreeWidgetItem::addChild(QTreeWidgetItem * child)
    parent->addChild(treeItem);
    return treeItem;
}

void MainVIew::updateCurrentGenerationPlot(std::vector<Particle>* particlesToPlot)
{
    QCustomPlot *customPlot = ui->customPlot;
    // Clear Everything First
    customPlot->clearGraphs();
    customPlot->clearItems();
    customPlot->clearMask();
    customPlot->clearPlottables();
    customPlot->repaint();

    // Setting up Graph
    customPlot->legend->setVisible(true);
    customPlot->legend->setFont(QFont("Helvetica", 9));
    customPlot->legend->setRowSpacing(-3);
    QVector<QCPScatterStyle::ScatterShape> shapes;
    shapes << QCPScatterStyle::ssDot;

    // Drawing curve
    QPen pen;
    customPlot->addGraph();
    pen.setColor(QColor(255,25,25,255));
    // generate data:
    QVector<double> IDs(particlesToPlot->size()), Costs(particlesToPlot->size());
    for (int dataIndex = 0; dataIndex < particlesToPlot->size(); dataIndex++)
    {
        Particle* p = &particlesToPlot->at(dataIndex);
        IDs[dataIndex] = (double)(p->ParticleID);
        Costs[dataIndex] = (double)(p->CurrentCost);
        // QMessageBox::information(this, "Test",  QString("ID: %0, Cost: %1").arg(IDs[dataIndex]).arg(Costs[dataIndex]),QMessageBox::Ok);
    }

    // Setting data
    customPlot->graph()->setData(IDs, Costs);
    customPlot->graph()->rescaleAxes(true);
    customPlot->graph()->setPen(pen);
    customPlot->graph()->setName("Cost");
    customPlot->graph()->setLineStyle(QCPGraph::lsLine);

    // Set scatter style
    customPlot->graph()->setScatterStyle(QCPScatterStyle::ssCircle);

    // Set axis parameters
    customPlot->rescaleAxes();
    customPlot->xAxis->setTicks(true);
    customPlot->yAxis->setTicks(true);
    customPlot->xAxis->setTickLabels(true);
    customPlot->yAxis->setTickLabels(true);
    customPlot->xAxis->setLabel("Particle ID");
    customPlot->yAxis->setLabel("Cost");

    // Make top right axes clones of bottom left axes:
    customPlot->axisRect()->setupFullAxesBox();

    // Refresh plot view
    customPlot->replot();

    // Log to UI
    // cout<<"All Particles Cost Graph Drawn..." << endl;
}

void MainVIew::clearCurrentGenerationPlot()
{
    QCustomPlot *customPlot = ui->customPlot;
    // Clear Everything First
    customPlot->clearGraphs();
    customPlot->clearItems();
    customPlot->clearMask();
    customPlot->clearPlottables();
    customPlot->repaint();
}

void MainVIew::updateGlobalCostPlot()
{
    QCustomPlot *customPlot = ui->iterationPlot;
    // Clear Everything First
    customPlot->clearGraphs();
    customPlot->clearItems();
    customPlot->clearMask();
    customPlot->clearPlottables();
    customPlot->repaint();

    // Setting up Graph
    customPlot->legend->setVisible(true);
    customPlot->legend->setFont(QFont("Helvetica", 9));
    customPlot->legend->setRowSpacing(-3);
    QVector<QCPScatterStyle::ScatterShape> shapes;
    shapes << QCPScatterStyle::ssDot;

    // Drawing global curve
    QPen pen;
    customPlot->addGraph();
    pen.setColor(QColor(255,25,25,255));

    // generate data:
    vector<Reading>* allGlobalCosts = &OBOptimizer::Instance()->allGlobalBestCosts;
    QVector<double> iterationNo(allGlobalCosts->size()), GlobalCosts(allGlobalCosts->size());
    for (int dataIndex = 0; dataIndex < allGlobalCosts->size(); dataIndex++)
    {
        Reading* r = &allGlobalCosts->at(dataIndex);
        iterationNo[dataIndex] = (double)(r->iterationNo);
        GlobalCosts[dataIndex] = (double)(r->value);
    }

    // Setting data
    customPlot->graph()->setData(iterationNo, GlobalCosts);
    customPlot->graph()->rescaleAxes(true);
    customPlot->graph()->setPen(pen);
    customPlot->graph()->setName("Global Cost");
    customPlot->graph()->setLineStyle(QCPGraph::lsLine);

    // Set scatter style
    customPlot->graph()->setScatterStyle(QCPScatterStyle::ssCircle);

    if(OBOptimizer::Instance()->recordAllParticles)
    {

        QVector<QCPScatterStyle::ScatterShape> shapes;
        shapes << QCPScatterStyle::ssCross;
        shapes << QCPScatterStyle::ssPlus;
        shapes << QCPScatterStyle::ssCircle;
        shapes << QCPScatterStyle::ssDisc;
        shapes << QCPScatterStyle::ssSquare;
        shapes << QCPScatterStyle::ssDiamond;
        shapes << QCPScatterStyle::ssStar;
        shapes << QCPScatterStyle::ssTriangle;
        shapes << QCPScatterStyle::ssTriangleInverted;
        shapes << QCPScatterStyle::ssCrossSquare;
        shapes << QCPScatterStyle::ssPlusSquare;
        shapes << QCPScatterStyle::ssCrossCircle;
        shapes << QCPScatterStyle::ssPlusCircle;
        shapes << QCPScatterStyle::ssPeace;
        shapes << QCPScatterStyle::ssCustom;
        for(int i = 0; i < OBOptimizer::Instance()->allParticleCosts.size(); i++)
        {
            try
            {
                customPlot->addGraph();
                pen.setColor(QColor(qSin(i*0.3)*100+100, qSin(i*0.6+0.7)*100+100, qSin(i*0.4+0.6)*100+100,160));

                // Generate data vectors
                ReadingDB* readingData = &OBOptimizer::Instance()->allParticleCosts.at(i);

                vector<Reading>* particleAllCosts = &readingData->readings;
                QVector<double> particleCosts(particleAllCosts->size()), iterat(particleAllCosts->size());
                for (int di = 0; di < particleAllCosts->size(); di++)
                {
                    Reading* r = &particleAllCosts->at(di);
                    particleCosts[di] = (double)(r->value);
                    iterat[di] = (double)(r->iterationNo);
                }
                // Setting data
                customPlot->graph()->setData(iterat, particleCosts);
                customPlot->graph()->rescaleAxes(true);
                customPlot->graph()->setPen(pen);
                stringstream ss;
                ss << "Particle " << readingData->particleID;
                string s = ss.str();
                customPlot->graph()->setName(QString::fromStdString(s));
                customPlot->graph()->setLineStyle(QCPGraph::lsLine);
                int shapeIndex = (int) (i/shapes.size());
                shapeIndex = i - (shapeIndex*shapes.size());
                // Set scatter style
                customPlot->graph()->setScatterStyle(QCPScatterStyle(shapes.at(shapeIndex),5));
            }
            catch (int e)
            {
                cout << "error!" << endl;
            }
        }
    }

    // Set axis parameters
    customPlot->rescaleAxes();
    customPlot->xAxis->setTicks(true);
    customPlot->yAxis->setTicks(true);
    customPlot->xAxis->setTickLabels(true);
    customPlot->yAxis->setTickLabels(true);
    customPlot->xAxis->setLabel("Iteration No.");
    customPlot->yAxis->setLabel("Global Cost");

    // Make top right axes clones of bottom left axes:
    customPlot->axisRect()->setupFullAxesBox();

    // Refresh plot view
    customPlot->replot();

    // Log to UI
    // cout<<"All Particles Gobal Cost Graph Drawn..." << endl;
}

void MainVIew::clearGlobalCostPlot()
{
    QCustomPlot *customPlot = ui->iterationPlot;
    // Clear Everything First
    customPlot->clearGraphs();
    customPlot->clearItems();
    customPlot->clearMask();
    customPlot->clearPlottables();
    customPlot->repaint();
}

void MainVIew::makeListOfParticles(std::vector<Particle>* particlesToShow)
{
    QStringListModel *model = new QStringListModel();
    QStringList List;
    // Plotting Current Generation Statistics
    for(int i = 0; i < particlesToShow->size(); i++)
    {
        Particle p = particlesToShow->at(i);
        List << QString("Particle %0").arg(p.ParticleID);
    }

    // Populate our model
    model->setStringList(List);
    ui->particleList->setModel(model);
}

void MainVIew::slotForOptimizerIterated(int IterationNo, Application* app, vector<Particle>* particleList, Particle* globalBestParticle)
{
    // update Gobal Cost graph
    // allGlobalCosts.push_back(globalBestParticle->CurrentCost);

    // Draw all particle costs is the check box is active
    /*
    if(ui->drawParticlesCheckBox->isChecked())
    {
        vector<double> thisIterationAllCosts;
        for(int i = 0; i < particleList->size(); i++)
        {
            Particle* p = &particleList->at(i);
            thisIterationAllCosts.push_back(p->CurrentCost);
        }
        allParticleCosts.push_back(thisIterationAllCosts);
    }
    */
    // cout << "Particle Size: "<< allParticleCosts.size() <<endl;
    dataMutex.lock();
    stringstream ss;
    ss << IterationNo << ", " << globalBestParticle->ParticleID << ", " << globalBestParticle->CurrentCost;
    // ui->dataLogTextBox->append(QString::fromStdString(ss.str()));
    updateGlobalCostPlot();
    dataMutex.unlock();
    // cout << "Iterated Signal Received" << endl;
}

void MainVIew::slotForOptimizationStarted()
{
    // clear everything
    clearGlobalCostPlot();
    clearCurrentGenerationPlot();

    stringstream ss;
    ss << "Iteration No., Global Best Particle ID, Global Best Cost";
    // ui->dataLogTextBox->append(QString::fromStdString(ss.str()));
    // allGlobalCosts.clear();
    // allParticleCosts.clear();
}

void MainVIew::slotForOptimizationFinished()
{
    ui->logTextBox->append("Optimization finished \n");
    ui->logTextBox->append(QString::fromStdString(OBOptimizer::Instance()->GlobalBestParticle.toString()));
    // Now showing the particles and their properties
    updateCurrentGenerationPlot(&OBOptimizer::Instance()->optimizationParticles);
    makeListOfParticles(&OBOptimizer::Instance()->optimizationParticles);
}

void MainVIew::on_drawParticlesCheckBox_toggled(bool checked)
{
    OBOptimizer::Instance()->recordAllParticles = checked;
}

void MainVIew::on_optimizationTechniqueComboBox_currentIndexChanged(int index)
{
    switch(index)
    {
    case 0:
    {
        OBOptimizer::Instance()->algorithmToRun = OptimizationAlgorithm::DPSO;
        cout << "Optimization Algorithm changed to plain DPSO" << endl;
        break;
    }
    case 1:
    {
        OBOptimizer::Instance()->algorithmToRun = OptimizationAlgorithm::TDPSO;
        cout << "Optimization Algorithm changed to tabu-ed DPSO" << endl;
        break;
    }
    default:
    {
        OBOptimizer::Instance()->algorithmToRun = OptimizationAlgorithm::DPSO;
        cout << "Optimization Algorithm changed to plain DPSO" << endl;
        break;
    }
    }
}
void MainVIew::postOutput(string str)
{
    // ui->dataLogTextBox->append(QString::fromStdString(str));
}

void MainVIew::on_runButton_3_clicked()
{
    QString filename = QFileDialog::getSaveFileName(this, tr("Save Data"), QDir::currentPath(),tr("Comma Separated Values (*.csv)") );
    if( !filename.isNull() )
    {
      QFile file(filename);
      if (file.open(QIODevice::ReadWrite))
      {
          QTextStream stream(&file);
          // stream << ui->dataLogTextBox->toPlainText() << endl;
      }
    }
}
