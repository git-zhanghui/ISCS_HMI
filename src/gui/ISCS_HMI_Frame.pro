TEMPLATE = subdirs

SUBDIRS = \
    PropertyBrowser \
    GraphicalShape \
    GraphicalFrame

GraphicalShape.depends = PropertyBrowser
GraphicalFrame.depends = GraphicalShape

CONFIG += ordered

message(QMAKESPEC: $$QMAKESPEC)

