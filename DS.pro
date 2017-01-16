#-------------------------------------------------
#
# Project created by QtCreator 2016-11-29T23:28:36
#
#-------------------------------------------------

QT       += core gui widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = DS
TEMPLATE = app

#GraphViz librairie
DEFINES += WITH_CGRAPH
INCLUDEPATH += private
QMAKE_CXXFLAGS += -DQGVCORE_LIB

VPATH += $$PWD/src
SOURCES += main.cpp\
        mainwindow.cpp \
    tabdockwidget.cpp \
    terminaldockwidget.cpp \
    dataStructures/tree.cpp \
    dataStructures/bst.cpp \
    dataStructures/tst.cpp \
    dataStructures/trie.cpp \
    dataStructures/linkedlist.cpp \
    src/terminal/ReplWidget.cpp \
    src/monitor.cpp \
    src/dataStructures/hash.cpp \
    src/tabdockright.cpp

HEADERS  += include/mainwindow.h \
    include/tabdockwidget.h \
    include/terminaldockwidget.h \
    include/base.h \
    include/dataStructures/tree.h \
    include/dataStructures/bst.h \
    include/dataStructures/tst.h \
    include/dataStructures/trie.h \
    include/trees.h \
    include/dataStructures/linkedlist.h \
    include/terminal/ReplWidget.h \
    include/monitor.h \
    include/dataStructures/stack.h \
    include/dataStructures/hash.h \
    include/tabdockright.h \
    include/dataStructures/queue.h \
    include/dataStructures/istack.h


INCLUDEPATH += $$PWD/include
INCLUDEPATH += /usr/local/Cellar/graphviz/2.40.1/include/
INCLUDEPATH += /usr/local/include

LIBS += -L/usr/local/Cellar/graphviz/2.40.1/lib -lgvc -lcgraph -lcdt
LIBS += -L/usr/local/lib -lQGVCore

OBJECTS_DIR = $$PWD/objs/
MOC_DIR = $$PWD/objs/


CONFIG += c++14

RESOURCES += \
    resource.qrc
