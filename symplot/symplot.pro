TEMPLATE = lib

QT += core opengl
CONFIG += c++11 staticlib release warn_on

DESTDIR += lib

win32:LIBS += opengl32.lib

INCLUDEPATH += $$PWD/../symath \
               $$PWD/../symgraph

HEADERS += \
    plotdata.h \
    skplot.h \
    plotstream.h \
    skplot2d.h \
    plotutils.h

SOURCES += \
    skplot.cpp \
    skplot2d.cpp

RESOURCES += \
    plot_shaders.qrc

LIBS += \
    -L../symath/lib/ -lsymath \
    -L../symgraph/lib/ -lsymgraph \
