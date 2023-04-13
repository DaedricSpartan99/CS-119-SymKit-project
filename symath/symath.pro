TEMPLATE = lib

QT -= core gui
CONFIG += c++11 staticlib release warn_on

DESTDIR += lib

HEADERS += \
    vector.h \
    svector.h \
    svector.tpp \
    integrators.tpp \
    descriptor.h \
    skerror.h \
    descriptors/newton.h \
    descriptors/oscillateur.h \
    integrators.h \
    descriptors/oscillateursimple.h \
    skutils.h

SOURCES += \
    vector.cpp \
    skerror.cpp \
    descriptors/newton.cpp \
    descriptors/oscillateur.cpp \
    descriptor.cpp


