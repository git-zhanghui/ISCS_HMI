#-------------------------------------------------
#
# Project created by QtCreator 2018-03-09T23:39:11
#
#-------------------------------------------------

QT       += core gui
#CONFIG += console

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = GraphicalFrame
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
    main.cpp \
    CDesignFrame.cpp \
    CGraphicsScene.cpp \
    CGraphicsView.cpp \
    CToolList.cpp

HEADERS += \
    CDesignFrame.h \
    UIActions.h \
    CGraphicsScene.h \
    CGraphicsView.h \
    CToolList.h

FORMS += \
        CDesignFrame.ui

LIBS += -lPropertyBrowser -lGraphicalShape

COMMON_PRI = $$PWD/../common.pri
exists($$COMMON_PRI){
     include($$COMMON_PRI)
}
else{
    error(" Couldn't find the common.pri file! ")
}
