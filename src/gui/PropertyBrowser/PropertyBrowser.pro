QT += widgets

TARGET = PropertyBrowser
TEMPLATE = lib

DEFINES += QT_DEPRECATED_WARNINGS

INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD

DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0

SOURCES += $$PWD/qtpropertybrowser.cpp \
        $$PWD/qtpropertymanager.cpp \
        $$PWD/qteditorfactory.cpp \
        $$PWD/qtvariantproperty.cpp \
        $$PWD/qttreepropertybrowser.cpp \
        $$PWD/qtbuttonpropertybrowser.cpp \
        $$PWD/qtgroupboxpropertybrowser.cpp \
        $$PWD/qtpropertybrowserutils.cpp \
        $$PWD/EditorWidget/BrushLabel.cpp \
        PropertyBrowser.cpp


HEADERS += $$PWD/qtpropertybrowser.h \
        $$PWD/qtpropertymanager.h \
        $$PWD/qteditorfactory.h \
        $$PWD/qtvariantproperty.h \
        $$PWD/qttreepropertybrowser.h \
        $$PWD/qtbuttonpropertybrowser.h \
        $$PWD/qtgroupboxpropertybrowser.h \
        $$PWD/qtpropertybrowserutils_p.h \
        $$PWD/EditorWidget/BrushLabel.h \
        PropertyBrowser.h


RESOURCES += $$PWD/qtpropertybrowser.qrc


win32 {
    contains(TEMPLATE, lib):contains(CONFIG, shared):DEFINES += QT_QTPROPERTYBROWSER_EXPORT
}

COMMON_PRI = $$PWD/../common.pri
exists($$COMMON_PRI){
     include($$COMMON_PRI)
}
else{
    error(" Couldn't find the common.pri file! ")
}

