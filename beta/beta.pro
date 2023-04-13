TEMPLATE = app

QT += opengl
CONFIG += c++11 release warn_on

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

DESTDIR += bin
TARGET = beta

INCLUDEPATH += \
    $$PWD/../symath \
    $$PWD/../symgraph \
    $$PWD/../symplot \
    $$PWD/../symviewer

HEADERS += \
    betascene.h \
    ressort/ressort.h \
    pendules/pendules.h \
    marbled.h \
    pendules/pendule.h \
    ressort/ressor.h \
    assets.h \
    newtonsphere/newtonsphere.h \
    pendcouple/penduledesc.h \
    pendcouple/pendcouple.h \
    pendcouple/pendsphere.h \
    pendressort/penduleressortdesc.h \
    pendressort/pendulersphere.h \
    pendressort/penduleressort.h \
    pendcouple/pendcouplepanel.h \
    pendules/pendulepanel.h \
    ressort/ressortpanel.h \
    pendressort/penduleressortpanel.h

SOURCES += \
    main.cpp \
    betascene.cpp \
    ressort/ressort.cpp \
    pendules/pendules.cpp \
    marbled.cpp \
    pendules/pendule.cpp \
    ressort/ressor.cpp \
    assets.cpp \
    newtonsphere/newtonsphere.cpp \
    pendcouple/penduledesc.cpp \
    pendcouple/pendcouple.cpp \
    pendcouple/pendsphere.cpp \
    pendressort/penduleressortdesc.cpp \
    pendressort/pendulersphere.cpp \
    pendressort/penduleressort.cpp \
    pendcouple/pendcouplepanel.cpp \
    ../symplot/skplot2d.cpp \
    pendules/pendulepanel.cpp \
    ressort/ressortpanel.cpp \
    pendressort/penduleressortpanel.cpp

win32:LIBS += opengl32.lib

LIBS += \
    -L../symath/lib/ -lsymath \
    -L../symgraph/lib/ -lsymgraph \
    -L../symplot/lib/ -lsymplot \
    -L../symviewer/lib/ -lsymviewer
