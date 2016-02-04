//=================================================================================================
// Name        : main.cpp
// Author      : Muhammad Obaidullah
// Version     : 0.1
// Copyright   : Electrical & Computer Engineering, Ryerson University ©2015
// Description : Main Program which executes all other classes for optimization of NoC
//=================================================================================================
#include <mainview.h>
#include <QApplication>
#include <QPushButton>
#include <QLabel>
#include <QWidget>
#include <QProgressBar>
#include <QSlider>
#include <QtGui>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainVIew w;
    w.show();
    return a.exec();
}
