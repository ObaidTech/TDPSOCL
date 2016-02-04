#-------------------------------------------------
#
# Project created by QtCreator 2015-11-17T14:13:42
#
#-------------------------------------------------

QT       += core gui
QT       += svg
QT       += printsupport
QT       += xml

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TDPSO
TEMPLATE = app


SOURCES +=  main.cpp\
            mainview.cpp \
            coreGraph.cpp \
            particle.cpp \
    qcustomplot.cpp \
    oboptimizer.cpp \
    communicationedge.cpp \
    xmlcoregraphparser.cpp \
    core.cpp \
    application.cpp \
    swapmove.cpp \
    reading.cpp \
    readingdb.cpp \
    obtabuer.cpp

HEADERS  += mainview.h \
            coregraph.h \
            particle.h \
            q_debugstream.h \
    qcustomplot.h \
    oboptimizer.h \
    communicationedge.h \
    Matrix.hpp \
    xmlcoregraphparser.h \
    core.h \
    application.h \
    swapmove.h \
    reading.h \
    readingdb.h \
    obtabuer.h

FORMS    += mainview.ui
win32:CONFIG(release, debug|release): LIBS += -L$$quote(C:/Program Files (x86)/Microsoft SDKs/Windows/v7.1A/Lib/) -lshell32
else:win32:CONFIG(debug, debug|release): LIBS += -L$$quote(C:/Program Files (x86)/Microsoft SDKs/Windows/v7.1A/Lib/) -lshell32

INCLUDEPATH += $$quote(C:/Program Files (x86)/Microsoft SDKs/Windows/v7.1A/Include)
DEPENDPATH += $$quote(C:/Program Files (x86)/Microsoft SDKs/Windows/v7.1A/Include)

DISTFILES +=

RESOURCES += \
    imageresources.qrc
