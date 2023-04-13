TEMPLATE = app

QT += opengl
CONFIG += c++11 release warn_on

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

DESTDIR += bin
TARGET = alpha

INCLUDEPATH += \
    $$PWD/../symath \
    $$PWD/../symgraph

HEADERS += \
    alphascene.h \
    descriptors/ressort.h \
    descriptors/pendules.h \
    marbled.h \
    pendule.h \
    ressor.h \
    assets.h \
    newtonsphere.h \
    descriptors/pendulec1.h \
    descriptors/pendulec2.h \
    descriptors/pendulec.h \
    pendulecoupl.h \
    pendparticle.h \
    descriptors/penduleressort.h

SOURCES += \
    main.cpp \
    alphascene.cpp \
    descriptors/ressort.cpp \
    descriptors/pendules.cpp \
    marbled.cpp \
    pendule.cpp \
    ressor.cpp \
    assets.cpp \
    newtonsphere.cpp \
    descriptors/pendulec1.cpp \
    descriptors/pendulec2.cpp \
    descriptors/pendulec.cpp \
    pendulecoupl.cpp \
    pendparticle.cpp \
    descriptors/penduleressort.cpp

win32:LIBS += opengl32.lib

LIBS += -L../symath/lib/ \
        -L../symgraph/lib/ \
        -lsymath \
        -lsymgraph

