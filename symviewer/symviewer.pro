TEMPLATE = lib

QT += core gui opengl
CONFIG += c++11 staticlib release warn_on

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

DESTDIR += lib

INCLUDEPATH += \
    $$PWD/../symath \
    $$PWD/../symgraph \
    $$PWD/../symplot

HEADERS += \
    skviewerpanel.h \
    panels/actorpanel.h \
    panels/specschecker.h \
    panels/descriptorviewer.h \
    panels/systempanel.h \
    edit/valuedit.h \
    edit/valuevisual.h \
    edit/vectoredit.h \
    skviewerscreen.h \
    skviewer.h \
    consoleviewer.h \
    panels/plotpanel.h \
    panels/phasespace.h \
    panels/integratorchecker.h

SOURCES += \
    panels/specschecker.cpp \
    panels/actorpanel.cpp \
    panels/descriptorviewer.cpp \
    panels/systempanel.cpp \
    edit/valuevisual.cpp \
    edit/valuedit.cpp \
    skviewerscreen.cpp \
    skviewer.cpp \
    edit/vectoredit.cpp \
    consoleviewer.cpp \
    panels/plotpanel.cpp \
    skviewerpanel.cpp \
    panels/phasespace.cpp \
    panels/integratorchecker.cpp

LIBS += \
    -L../symath/lib/ -lsymath \
    -L../symgraph/lib/ -lsymgraph \
    -L../symplot/lib/ -lsymplot
