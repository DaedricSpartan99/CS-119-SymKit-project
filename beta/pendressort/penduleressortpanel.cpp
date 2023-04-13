#include "penduleressortpanel.h"
#include "penduleressortdesc.h"
#include "pendulersphere.h"

#include "penduleressort.h"

#include <QGridLayout>

#include "edit/valuedit.h"
#include "edit/valuevisual.h"

#include "skplot.h"
#include "panels/phasespace.h"

#include "skutils.h"

#include <QHBoxLayout>

#include "skerror.h"
#include <iostream>

using namespace std;
using namespace symkit;

/* PendSphere section */

void PendSpherePanel::angleChanged(double value)
{
    descriptor->setPenduleAngle(value);
}

void PendSpherePanel::speedChanged(double value)
{
    descriptor->setPenduleSpeed(value);
}

void PendSpherePanel::lengthChanged(double value)
{
    try {

        descriptor->setLenght(value);

    } catch (const SKError& error) {

        cerr << error << endl;
        descriptor->setLenght(1);
        length->setValue(1, true);
    }
}

void PendSpherePanel::massChanged(double value)
{
    if (descriptor->getg() > 0 && value > 10000 / descriptor->getg())
        value = 10000 / descriptor->getg();

    try {

        descriptor->setMass(value, 1);

    } catch (const SKError& error) {

        cerr << error << endl;
        value = 1;

        descriptor->setMass(value, 1);
    }

    mass->setValue(value, true);
}

void PendSpherePanel::gravityChange(double value)
{
    if (value > 10000 / descriptor->getMass(1))
        value = 10000 / descriptor->getMass(1);

    try {

        descriptor->setg(value);

    } catch (const SKError& error) {

        cerr << error << endl;
        value = 9.81;

        descriptor->setg(value);
    }

    gravity->setValue(value, true);
}

void PendSpherePanel::frictionChanged(double value)
{
    if (value > 1000)
        value = 1000;

    try {

        descriptor->setFrottement(value, 1);

    } catch (const SKError& error) {

        cerr << error << endl;
        value = 0;

        descriptor->setFrottement(value, 1);
    }

    friction->setValue(value, true);
}

PendSpherePanel::PendSpherePanel(PendrSphere *sphere, PenduleRessort *descriptor, QWidget *parent)

    : ActorPanel(sphere, parent), descriptor(descriptor)
{
    layout = new QGridLayout;

    angle = new Valuedit("Angle", descriptor->getPenduleAngle());
    speed = new Valuedit("Angular speed", descriptor->getPenduleSpeed());
    length = new Valuedit("Length", descriptor->getLenght());
    mass = new Valuedit("Mass", descriptor->getMass(1));
    gravity = new Valuedit("Gravity", descriptor->getg());
    friction = new Valuedit("Friction", descriptor->getFrottement(1));

    layout->addWidget(angle);
    layout->addWidget(speed);
    layout->addWidget(length);
    layout->addWidget(mass);
    layout->addWidget(gravity);
    layout->addWidget(friction);

    ActorPanel::addToDedicated(angle);
    ActorPanel::addToDedicated(speed);
    ActorPanel::addToDedicated(length);
    ActorPanel::addToDedicated(mass);
    ActorPanel::addToDedicated(gravity);
    ActorPanel::addToDedicated(friction);

    ActorPanel::setDedicatedLayout(layout);

    /* Connect signals */

    connect(angle, SIGNAL(valueChanged(double)), this, SLOT(angleChanged(double)));
    connect(speed, SIGNAL(valueChanged(double)), this, SLOT(speedChanged(double)));
    connect(length, SIGNAL(valueChanged(double)), this, SLOT(lengthChanged(double)));
    connect(mass, SIGNAL(valueChanged(double)), this, SLOT(massChanged(double)));
    connect(gravity, SIGNAL(valueChanged(double)), this, SLOT(gravityChange(double)));
    connect(friction, SIGNAL(valueChanged(double)), this, SLOT(frictionChanged(double)));
}

PendSpherePanel::~PendSpherePanel()
{
    delete angle;
    delete speed;
    delete length;
    delete mass;
    delete friction;
    delete layout;
}

void PendSpherePanel::updatePanel()
{
    angle->setValue(descriptor->getPenduleAngle());
    speed->setValue(descriptor->getPenduleSpeed());
}

/* Ressort Sphere section */

void RessortSpherePanel::positionChanged(double value)
{
    descriptor->setRessortPosition(value);
}

void RessortSpherePanel::speedChanged(double value)
{
    descriptor->setRessortSpeed(value);
}

void RessortSpherePanel::kChanged(double value)
{
    if (value > 10000)
        value = 10000;

    try {

        descriptor->setk(value);

    } catch (const SKError& error) {

        cerr << error << endl;
        value = 1;

        descriptor->setk(value);
    }

    k->setValue(value, true);
}

void RessortSpherePanel::massChanged(double value)
{
    if (value < 0.001)
        value = 0.001;

    try {

        descriptor->setMass(value, 0);

    } catch (const SKError& error) {

        cerr << error << endl;
        value = 1;

        descriptor->setMass(value, 0);
    }

    mass->setValue(value, true);
}

void RessortSpherePanel::frictionChanged(double value)
{
    if (value > 100 * descriptor->getMass(0))
        value = 100 * descriptor->getMass(0);

    try {

        descriptor->setFrottement(value, 0);

    } catch (const SKError& error) {

        cerr << error << endl;
        value = 0;

        // reset to a non-error value
        descriptor->setFrottement(value, 0);
    }

    friction->setValue(value, true);
}

RessortSpherePanel::RessortSpherePanel(PendrSphere* sphere, PenduleRessort *descriptor, QWidget *parent)

    : ActorPanel(sphere, parent), descriptor(descriptor)
{
    layout = new QGridLayout;

    position = new Valuedit("Position", descriptor->getRessortPosition());
    speed = new Valuedit("Speed", descriptor->getRessortSpeed());
    k = new Valuedit("Ressort constant", descriptor->getk());
    mass = new Valuedit("Mass", descriptor->getMass(0));
    friction = new Valuedit("Friction", descriptor->getFrottement(0));

    layout->addWidget(position);
    layout->addWidget(speed);
    layout->addWidget(k);
    layout->addWidget(mass);
    layout->addWidget(friction);

    ActorPanel::addToDedicated(position);
    ActorPanel::addToDedicated(speed);
    ActorPanel::addToDedicated(k);
    ActorPanel::addToDedicated(mass);
    ActorPanel::addToDedicated(friction);

    ActorPanel::setDedicatedLayout(layout);

    connect(position, SIGNAL(valueChanged(double)), this, SLOT(positionChanged(double)));
    connect(speed, SIGNAL(valueChanged(double)), this, SLOT(speedChanged(double)));
    connect(k, SIGNAL(valueChanged(double)), this, SLOT(kChanged(double)));
    connect(mass, SIGNAL(valueChanged(double)), this, SLOT(massChanged(double)));
    connect(friction, SIGNAL(valueChanged(double)), this, SLOT(frictionChanged(double)));
}

RessortSpherePanel::~RessortSpherePanel()
{
    delete position;
    delete speed;
    delete k;
    delete mass;
    delete friction;

    delete layout;
}

void RessortSpherePanel::updatePanel()
{
    position->setValue(descriptor->getRessortPosition());
    speed->setValue(descriptor->getRessortSpeed());
}

/* Entire system section */

void PenduleRessortPanel::updatePlugin()
{
    energy->setValue(desc->energy());
}


PenduleRessortPanel::PenduleRessortPanel(PenduleR *pend_ressort, QWidget *parent)

    : SystemPanel(pend_ressort, parent), pend_ressort(pend_ressort)
{
    desc = static_cast<PenduleRessort*>(pend_ressort->getDescriptor());

    layout = new QHBoxLayout;

    energy = new Valuevisual("Total energy", desc->energy());

    layout->addWidget(energy);

    SystemPanel::addToDedicated(energy);

    SystemPanel::setDedicatedLayout(layout);

    ressort = new RessortSpherePanel(pend_ressort->getRessort(), desc);
    pendule = new PendSpherePanel(pend_ressort->getPendule(), desc);

    /* Setup plotting */

    plot = new PhaseSpace("Phase space", 2);

    plot->addFunction(desc, 0);
    plot->addFunction(desc, 1);

    plot->getPlot()->setBackgroundColor(color_s(0.95, 0.95, 0.95));

    plot->getPlot()->setAxysX(SKAxys(20, -10, color_s(0, 0, 1)));
    plot->getPlot()->setAxysY(SKAxys(10, -5, color_s(0, 1, 0)));

    pushToScreen(ressort);
    pushToScreen(pendule);

    /* Append to phase space */
    pushToScreen(plot);
}

PenduleRessortPanel::~PenduleRessortPanel()
{
    delete energy;
    delete layout;
}

PhaseSpace * PenduleRessortPanel::getPhaseSpace()
{
    return plot;
}
