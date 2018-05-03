#-------------------------------------------------
#
# Project created by QtCreator 2018-03-11T22:20:52
#
#-------------------------------------------------
QT += core widgets

TARGET = GraphicalShape
TEMPLATE = lib

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
        $$PWD/AbstractGraphicsItem.cpp \
        $$PWD/AbstractRegularItem.cpp \
        $$PWD/RectangleItem.cpp \
        $$PWD/GraphicsFactory.cpp \
    TextItem.cpp \
    ImageItem.cpp \
    WidgetItem.cpp \
    EllipseItem.cpp \
    LineItem.cpp \
    PolygonShapeItem.cpp \
    PointsItem.cpp \
    PolygonLineItem.cpp

HEADERS += \
        $$PWD/../include/Export.h \
        $$PWD/../include/AbstractGraphicsItem.h \
        $$PWD/AbstractRegularItem.h \
        $$PWD/RectangleItem.h \
        $$PWD/GraphicsFactory.h \
    TextItem.h \
    ImageItem.h \
    WidgetItem.h \
    EllipseItem.h \
    LineItem.h \
    PolygonLineItem.h \
    PolygonShapeItem.h \
    PointsItem.h

LIBS += -lPropertyBrowser

win32 {
    contains(TEMPLATE, lib):contains(CONFIG, shared):DEFINES += EXPORT_LIBRARY
}

COMMON_PRI = $$PWD/../common.pri
exists($$COMMON_PRI){
     include($$COMMON_PRI)
}
else{
    error(" Couldn't find the common.pri file! ")
}
