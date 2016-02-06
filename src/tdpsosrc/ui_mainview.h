/********************************************************************************
** Form generated from reading UI file 'mainview.ui'
**
** Created by: Qt User Interface Compiler version 5.4.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINVIEW_H
#define UI_MAINVIEW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableView>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QWidget>
#include "qcustomplot.h"

QT_BEGIN_NAMESPACE

class Ui_MainVIew
{
public:
    QWidget *centralWidget;
    QTabWidget *tabWidget;
    QWidget *logTab;
    QTextEdit *logTextBox;
    QWidget *statiticsTab;
    QCustomPlot *customPlot;
    QWidget *IterationStatistics;
    QCustomPlot *iterationPlot;
    QWidget *dataLogPage;
    QTextEdit *logTextBox_2;
    QPushButton *runButton_2;
    QPushButton *runButton_3;
    QGroupBox *particleInfoBox;
    QLabel *particleView;
    QTableView *particlePropertiesView;
    QLabel *particlePropertyLabel;
    QWidget *gridLayoutWidget;
    QGridLayout *particleDisplay;
    QLabel *particleListLabel;
    QListView *particleList;
    QTabWidget *tabWidget_2;
    QWidget *tab;
    QLineEdit *applicationNameBox;
    QPushButton *importApplicationBtn;
    QLabel *label_8;
    QTreeWidget *applicationTreeWidget;
    QWidget *tab_2;
    QLineEdit *pWidthBox;
    QPushButton *runButton;
    QLabel *label_4;
    QLabel *label_5;
    QLineEdit *noOfIterations;
    QLabel *label_3;
    QLineEdit *noOfParticlesBox;
    QLabel *label_2;
    QComboBox *topologyComboBox;
    QLineEdit *pHeightBox;
    QLabel *label_6;
    QComboBox *optimizationTechniqueComboBox;
    QLabel *label_7;
    QLabel *label;
    QLabel *label_9;
    QLineEdit *inertiaBox;
    QLineEdit *selfConfidenceBox;
    QLabel *label_10;
    QLabel *label_11;
    QLineEdit *swarmConfidenceBox;
    QCheckBox *drawParticlesCheckBox;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainVIew)
    {
        if (MainVIew->objectName().isEmpty())
            MainVIew->setObjectName(QStringLiteral("MainVIew"));
        MainVIew->resize(950, 680);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainVIew->sizePolicy().hasHeightForWidth());
        MainVIew->setSizePolicy(sizePolicy);
        MainVIew->setMinimumSize(QSize(950, 680));
        MainVIew->setMaximumSize(QSize(950, 680));
        centralWidget = new QWidget(MainVIew);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        tabWidget = new QTabWidget(centralWidget);
        tabWidget->setObjectName(QStringLiteral("tabWidget"));
        tabWidget->setGeometry(QRect(10, 345, 931, 276));
        tabWidget->setTabShape(QTabWidget::Rounded);
        tabWidget->setIconSize(QSize(16, 20));
        logTab = new QWidget();
        logTab->setObjectName(QStringLiteral("logTab"));
        logTextBox = new QTextEdit(logTab);
        logTextBox->setObjectName(QStringLiteral("logTextBox"));
        logTextBox->setGeometry(QRect(5, 10, 916, 226));
        logTextBox->setAutoFillBackground(false);
        QIcon icon;
        icon.addFile(QStringLiteral(":/Icons/images/file_extension_qbb.png"), QSize(), QIcon::Normal, QIcon::Off);
        tabWidget->addTab(logTab, icon, QString());
        statiticsTab = new QWidget();
        statiticsTab->setObjectName(QStringLiteral("statiticsTab"));
        customPlot = new QCustomPlot(statiticsTab);
        customPlot->setObjectName(QStringLiteral("customPlot"));
        customPlot->setGeometry(QRect(0, 0, 931, 241));
        QIcon icon1;
        icon1.addFile(QStringLiteral(":/Icons/images/node-tree.png"), QSize(), QIcon::Normal, QIcon::Off);
        tabWidget->addTab(statiticsTab, icon1, QString());
        IterationStatistics = new QWidget();
        IterationStatistics->setObjectName(QStringLiteral("IterationStatistics"));
        iterationPlot = new QCustomPlot(IterationStatistics);
        iterationPlot->setObjectName(QStringLiteral("iterationPlot"));
        iterationPlot->setGeometry(QRect(0, 0, 931, 241));
        QIcon icon2;
        icon2.addFile(QStringLiteral(":/Icons/images/statistics.png"), QSize(), QIcon::Normal, QIcon::Off);
        tabWidget->addTab(IterationStatistics, icon2, QString());
        dataLogPage = new QWidget();
        dataLogPage->setObjectName(QStringLiteral("dataLogPage"));
        logTextBox_2 = new QTextEdit(dataLogPage);
        logTextBox_2->setObjectName(QStringLiteral("logTextBox_2"));
        logTextBox_2->setGeometry(QRect(5, 40, 916, 201));
        logTextBox_2->setAutoFillBackground(false);
        runButton_2 = new QPushButton(dataLogPage);
        runButton_2->setObjectName(QStringLiteral("runButton_2"));
        runButton_2->setGeometry(QRect(860, 4, 61, 31));
        QIcon icon3;
        icon3.addFile(QStringLiteral(":/Icons/images/draw_eraser.png"), QSize(), QIcon::Normal, QIcon::Off);
        runButton_2->setIcon(icon3);
        runButton_2->setIconSize(QSize(32, 32));
        runButton_3 = new QPushButton(dataLogPage);
        runButton_3->setObjectName(QStringLiteral("runButton_3"));
        runButton_3->setGeometry(QRect(755, 4, 101, 31));
        QIcon icon4;
        icon4.addFile(QStringLiteral(":/Icons/images/document_black.png"), QSize(), QIcon::Normal, QIcon::Off);
        runButton_3->setIcon(icon4);
        runButton_3->setIconSize(QSize(32, 32));
        QIcon icon5;
        icon5.addFile(QStringLiteral(":/Icons/images/action_log.png"), QSize(), QIcon::Normal, QIcon::Off);
        tabWidget->addTab(dataLogPage, icon5, QString());
        particleInfoBox = new QGroupBox(centralWidget);
        particleInfoBox->setObjectName(QStringLiteral("particleInfoBox"));
        particleInfoBox->setGeometry(QRect(10, 10, 561, 331));
        particleView = new QLabel(particleInfoBox);
        particleView->setObjectName(QStringLiteral("particleView"));
        particleView->setGeometry(QRect(10, 20, 91, 16));
        particlePropertiesView = new QTableView(particleInfoBox);
        particlePropertiesView->setObjectName(QStringLiteral("particlePropertiesView"));
        particlePropertiesView->setGeometry(QRect(360, 230, 196, 96));
        particlePropertyLabel = new QLabel(particleInfoBox);
        particlePropertyLabel->setObjectName(QStringLiteral("particlePropertyLabel"));
        particlePropertyLabel->setGeometry(QRect(360, 210, 91, 16));
        gridLayoutWidget = new QWidget(particleInfoBox);
        gridLayoutWidget->setObjectName(QStringLiteral("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(9, 39, 341, 286));
        particleDisplay = new QGridLayout(gridLayoutWidget);
        particleDisplay->setSpacing(6);
        particleDisplay->setContentsMargins(11, 11, 11, 11);
        particleDisplay->setObjectName(QStringLiteral("particleDisplay"));
        particleDisplay->setContentsMargins(0, 0, 0, 0);
        particleListLabel = new QLabel(particleInfoBox);
        particleListLabel->setObjectName(QStringLiteral("particleListLabel"));
        particleListLabel->setGeometry(QRect(360, 20, 91, 16));
        particleList = new QListView(particleInfoBox);
        particleList->setObjectName(QStringLiteral("particleList"));
        particleList->setGeometry(QRect(360, 40, 196, 171));
        tabWidget_2 = new QTabWidget(centralWidget);
        tabWidget_2->setObjectName(QStringLiteral("tabWidget_2"));
        tabWidget_2->setGeometry(QRect(580, 10, 361, 331));
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        applicationNameBox = new QLineEdit(tab);
        applicationNameBox->setObjectName(QStringLiteral("applicationNameBox"));
        applicationNameBox->setGeometry(QRect(110, 70, 241, 20));
        importApplicationBtn = new QPushButton(tab);
        importApplicationBtn->setObjectName(QStringLiteral("importApplicationBtn"));
        importApplicationBtn->setGeometry(QRect(210, 10, 141, 51));
        QIcon icon6;
        icon6.addFile(QStringLiteral("../../Downloads/Adobe_Illustrator_XML (1).png"), QSize(), QIcon::Normal, QIcon::Off);
        importApplicationBtn->setIcon(icon6);
        importApplicationBtn->setIconSize(QSize(32, 32));
        label_8 = new QLabel(tab);
        label_8->setObjectName(QStringLiteral("label_8"));
        label_8->setGeometry(QRect(10, 70, 91, 16));
        applicationTreeWidget = new QTreeWidget(tab);
        QTreeWidgetItem *__qtreewidgetitem = new QTreeWidgetItem();
        __qtreewidgetitem->setText(0, QStringLiteral("1"));
        applicationTreeWidget->setHeaderItem(__qtreewidgetitem);
        applicationTreeWidget->setObjectName(QStringLiteral("applicationTreeWidget"));
        applicationTreeWidget->setGeometry(QRect(10, 100, 341, 201));
        tabWidget_2->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QStringLiteral("tab_2"));
        pWidthBox = new QLineEdit(tab_2);
        pWidthBox->setObjectName(QStringLiteral("pWidthBox"));
        pWidthBox->setGeometry(QRect(170, 130, 66, 20));
        runButton = new QPushButton(tab_2);
        runButton->setObjectName(QStringLiteral("runButton"));
        runButton->setGeometry(QRect(260, 5, 91, 51));
        QIcon icon7;
        icon7.addFile(QStringLiteral("../../Downloads/fatcow-hosting-icons-3000/fatcow-hosting-icons-3000/32x32/lightning_go.png"), QSize(), QIcon::Normal, QIcon::On);
        runButton->setIcon(icon7);
        runButton->setIconSize(QSize(32, 32));
        label_4 = new QLabel(tab_2);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setGeometry(QRect(10, 130, 61, 16));
        label_5 = new QLabel(tab_2);
        label_5->setObjectName(QStringLiteral("label_5"));
        label_5->setGeometry(QRect(245, 130, 41, 20));
        noOfIterations = new QLineEdit(tab_2);
        noOfIterations->setObjectName(QStringLiteral("noOfIterations"));
        noOfIterations->setGeometry(QRect(70, 30, 71, 20));
        label_3 = new QLabel(tab_2);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setGeometry(QRect(10, 100, 61, 16));
        noOfParticlesBox = new QLineEdit(tab_2);
        noOfParticlesBox->setObjectName(QStringLiteral("noOfParticlesBox"));
        noOfParticlesBox->setGeometry(QRect(130, 160, 221, 20));
        label_2 = new QLabel(tab_2);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(10, 70, 111, 16));
        topologyComboBox = new QComboBox(tab_2);
        topologyComboBox->setObjectName(QStringLiteral("topologyComboBox"));
        topologyComboBox->setGeometry(QRect(130, 100, 221, 22));
        pHeightBox = new QLineEdit(tab_2);
        pHeightBox->setObjectName(QStringLiteral("pHeightBox"));
        pHeightBox->setGeometry(QRect(285, 130, 66, 20));
        label_6 = new QLabel(tab_2);
        label_6->setObjectName(QStringLiteral("label_6"));
        label_6->setGeometry(QRect(130, 130, 31, 20));
        optimizationTechniqueComboBox = new QComboBox(tab_2);
        optimizationTechniqueComboBox->setObjectName(QStringLiteral("optimizationTechniqueComboBox"));
        optimizationTechniqueComboBox->setGeometry(QRect(130, 70, 221, 22));
        label_7 = new QLabel(tab_2);
        label_7->setObjectName(QStringLiteral("label_7"));
        label_7->setGeometry(QRect(10, 160, 81, 16));
        label = new QLabel(tab_2);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(10, 30, 61, 16));
        label_9 = new QLabel(tab_2);
        label_9->setObjectName(QStringLiteral("label_9"));
        label_9->setGeometry(QRect(10, 190, 81, 16));
        inertiaBox = new QLineEdit(tab_2);
        inertiaBox->setObjectName(QStringLiteral("inertiaBox"));
        inertiaBox->setGeometry(QRect(130, 190, 221, 20));
        selfConfidenceBox = new QLineEdit(tab_2);
        selfConfidenceBox->setObjectName(QStringLiteral("selfConfidenceBox"));
        selfConfidenceBox->setGeometry(QRect(130, 220, 221, 20));
        label_10 = new QLabel(tab_2);
        label_10->setObjectName(QStringLiteral("label_10"));
        label_10->setGeometry(QRect(10, 220, 121, 16));
        label_11 = new QLabel(tab_2);
        label_11->setObjectName(QStringLiteral("label_11"));
        label_11->setGeometry(QRect(10, 250, 121, 16));
        swarmConfidenceBox = new QLineEdit(tab_2);
        swarmConfidenceBox->setObjectName(QStringLiteral("swarmConfidenceBox"));
        swarmConfidenceBox->setGeometry(QRect(130, 250, 221, 20));
        drawParticlesCheckBox = new QCheckBox(tab_2);
        drawParticlesCheckBox->setObjectName(QStringLiteral("drawParticlesCheckBox"));
        drawParticlesCheckBox->setGeometry(QRect(10, 280, 101, 17));
        drawParticlesCheckBox->setChecked(false);
        tabWidget_2->addTab(tab_2, QString());
        MainVIew->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainVIew);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 950, 21));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QStringLiteral("menuFile"));
        MainVIew->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainVIew);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainVIew->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainVIew);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainVIew->setStatusBar(statusBar);

        menuBar->addAction(menuFile->menuAction());

        retranslateUi(MainVIew);

        tabWidget->setCurrentIndex(0);
        tabWidget_2->setCurrentIndex(1);
        topologyComboBox->setCurrentIndex(0);
        optimizationTechniqueComboBox->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(MainVIew);
    } // setupUi

    void retranslateUi(QMainWindow *MainVIew)
    {
        MainVIew->setWindowTitle(QApplication::translate("MainVIew", "Tabu-ed Discrete Particle Swarm Optimization", 0));
        tabWidget->setTabText(tabWidget->indexOf(logTab), QApplication::translate("MainVIew", "All Logs", 0));
        tabWidget->setTabText(tabWidget->indexOf(statiticsTab), QApplication::translate("MainVIew", "Current Generation Statistics", 0));
        tabWidget->setTabText(tabWidget->indexOf(IterationStatistics), QApplication::translate("MainVIew", "Iteration Statistics", 0));
        runButton_2->setText(QApplication::translate("MainVIew", "Clear", 0));
        runButton_3->setText(QApplication::translate("MainVIew", "Save to File", 0));
        tabWidget->setTabText(tabWidget->indexOf(dataLogPage), QApplication::translate("MainVIew", "Data Log", 0));
        particleInfoBox->setTitle(QApplication::translate("MainVIew", "Particle Information", 0));
        particleView->setText(QApplication::translate("MainVIew", "Structure", 0));
        particlePropertyLabel->setText(QApplication::translate("MainVIew", "Properties", 0));
        particleListLabel->setText(QApplication::translate("MainVIew", "Particles", 0));
        applicationNameBox->setText(QApplication::translate("MainVIew", "- Not Selected -", 0));
        importApplicationBtn->setText(QApplication::translate("MainVIew", "Import Application", 0));
        label_8->setText(QApplication::translate("MainVIew", "Application Name:", 0));
        tabWidget_2->setTabText(tabWidget_2->indexOf(tab), QApplication::translate("MainVIew", "Input", 0));
        pWidthBox->setText(QApplication::translate("MainVIew", "8", 0));
        runButton->setText(QApplication::translate("MainVIew", "Run", 0));
        label_4->setText(QApplication::translate("MainVIew", "Size:", 0));
        label_5->setText(QApplication::translate("MainVIew", "Height:", 0));
        noOfIterations->setText(QApplication::translate("MainVIew", "25", 0));
        label_3->setText(QApplication::translate("MainVIew", "Topology:", 0));
        noOfParticlesBox->setText(QApplication::translate("MainVIew", "64", 0));
        label_2->setText(QApplication::translate("MainVIew", "Optimizaion Technique:", 0));
        topologyComboBox->clear();
        topologyComboBox->insertItems(0, QStringList()
         << QApplication::translate("MainVIew", "Mesh", 0)
         << QApplication::translate("MainVIew", "Torus", 0)
         << QApplication::translate("MainVIew", "Ring", 0)
         << QApplication::translate("MainVIew", "Butterfly", 0)
         << QApplication::translate("MainVIew", "Hypercube", 0)
        );
        pHeightBox->setText(QApplication::translate("MainVIew", "8", 0));
        label_6->setText(QApplication::translate("MainVIew", "Width:", 0));
        optimizationTechniqueComboBox->clear();
        optimizationTechniqueComboBox->insertItems(0, QStringList()
         << QApplication::translate("MainVIew", "Discrete Particle Swarm", 0)
         << QApplication::translate("MainVIew", "Tabu-ed Discrete Particle Swarm", 0)
         << QApplication::translate("MainVIew", "Tabu-Search", 0)
         << QApplication::translate("MainVIew", "Genetic Algorithm", 0)
         << QApplication::translate("MainVIew", "Branch and Bound", 0)
        );
        label_7->setText(QApplication::translate("MainVIew", "No. of Particles:", 0));
        label->setText(QApplication::translate("MainVIew", "Iterations:", 0));
        label_9->setText(QApplication::translate("MainVIew", "Particle Inertia:", 0));
        inertiaBox->setText(QApplication::translate("MainVIew", "1.0", 0));
        selfConfidenceBox->setText(QApplication::translate("MainVIew", "0.04", 0));
        label_10->setText(QApplication::translate("MainVIew", "Self Confidence:", 0));
        label_11->setText(QApplication::translate("MainVIew", "Swarm Confidence:", 0));
        swarmConfidenceBox->setText(QApplication::translate("MainVIew", "0.02", 0));
        drawParticlesCheckBox->setText(QApplication::translate("MainVIew", "Plot all Particles", 0));
        tabWidget_2->setTabText(tabWidget_2->indexOf(tab_2), QApplication::translate("MainVIew", "Optimization Settings", 0));
        menuFile->setTitle(QApplication::translate("MainVIew", "File", 0));
    } // retranslateUi

};

namespace Ui {
    class MainVIew: public Ui_MainVIew {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINVIEW_H
