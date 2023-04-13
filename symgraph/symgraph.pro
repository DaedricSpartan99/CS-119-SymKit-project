TEMPLATE = lib

QT += core opengl
CONFIG += c++11 staticlib release warn_on

DESTDIR += lib

win32:LIBS += opengl32.lib

LIBS += -L../symath/lib/ -lsymath 

INCLUDEPATH += $$PWD/../symath

HEADERS += \
    scene.h \
    camera.h \
    actors/shape.h \
    skactor.h \
    specs/scalable.h \
    specs/positionable.h \
    specs/orientable.h \
    specs/renderable.h \
    specs/colorable.h \
    specs/specs.h \
    specs/evolvable.h \
    actors/decoration.h \
    listeners/keylistener.h \
    listeners/mouselistener.h \
    specs/describable.h \
    models/glsphere.h \
    models/glmarbled.h \
    glmodel.h \
    actors/particles/newtonparticle.h \
    actors/particle.h \
    actors/particles/oscillatorparticle.h \
    actors/systems/particlesystem.h \
    actors/systems/interactingsystem.h \
    scenewrapper.h \
    actors/systems/actorgroup.h \
    actors/systems/symsystem.h \
    graphtools.h \
    timercontrol.h

SOURCES += \
    scene.cpp \
    camera.cpp \
    actors/shape.cpp \
    actors/decoration.cpp \
    specs/describable.cpp \
    models/glsphere.cpp \
    models/glmarbled.cpp \
    glmodel.cpp \
    actors/particles/newtonparticle.cpp \
    actors/particle.cpp \
    actors/particles/oscillatorparticle.cpp \
    actors/systems/particlesystem.cpp \
    actors/systems/interactingsystem.cpp \
    scenewrapper.cpp \
    actors/systems/actorgroup.cpp \
    actors/systems/symsystem.cpp \
    graphtools.cpp

RESOURCES += \
    shaders.qrc
