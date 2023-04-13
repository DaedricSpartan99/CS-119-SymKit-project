#include "pendcouplepanel.h"

#include "pendcouple/pendsphere.h"
#include "pendcouple/penduledesc.h"

#include <QGridLayout>

#include "edit/valuedit.h"
#include "pendcouple.h"

#include "skplot.h"
#include "panels/phasespace.h"

#include "descriptors/oscillateur.h"

#include "skutils.h"

#include "skerror.h"
#include <iostream>

using namespace std;
using namespace symkit;

PenduleSpherePanel::PenduleSpherePanel(PendSphere *sphere, PenduleDesc * descriptor, int index, QWidget *parent)
    : ActorPanel(sphere, parent), descriptor(descriptor), index(index)
{
    layout = new QGridLayout;

    angle = new Valuedit("Angle", descriptor->getAngle(index));
    speed = new Valuedit("Angular speed", descriptor->getAngularSpeed(index));
    length = new Valuedit("Length", descriptor->getLength(index));
    mass = new Valuedit("Mass", descriptor->getMass(index));

    layout->addWidget(angle);
    layout->addWidget(speed);
    layout->addWidget(length);
    layout->addWidget(mass);

    ActorPanel::addToDedicated(angle);
    ActorPanel::addToDedicated(speed);
    ActorPanel::addToDedicated(length);
    ActorPanel::addToDedicated(mass);

    ActorPanel::setDedicatedLayout(layout);

    /* Connect signals */

    connect(angle, SIGNAL(valueChanged(double)), this, SLOT(angleChanged(double)));
    connect(speed, SIGNAL(valueChanged(double)), this, SLOT(speedChanged(double)));
    connect(length, SIGNAL(valueChanged(double)), this, SLOT(lengthChanged(double)));
    connect(mass, SIGNAL(valueChanged(double)), this, SLOT(massChanged(double)));
}

PenduleSpherePanel::~PenduleSpherePanel()
{
    delete angle;
    delete speed;
    delete length;
    delete mass;
    delete layout;
}

void PenduleSpherePanel::updatePanel()
{
    angle->setValue(descriptor->getAngle(index));
    speed->setValue(descriptor->getAngularSpeed(index));
}

void PenduleSpherePanel::angleChanged(double value)
{
    descriptor->setAngle(value, index);
}

void PenduleSpherePanel::speedChanged(double value)
{
    descriptor->setAngularSpeed(value, index);
}

void PenduleSpherePanel::lengthChanged(double l)
{
    if (l > 1000)
        l = 1000;

    try {

        descriptor->setLength(l, index);

    } catch (const SKError& error) {

        cerr << error << endl;
        l = 1;
        descriptor->setLength(l, index);
    }

    length->setValue(l, true);
}

void PenduleSpherePanel::massChanged(double m)
{
    if (index && m > 10 * descriptor->getMass(0))
        m = 10 * descriptor->getMass(0);

    try {

        descriptor->setMass(m, index);

    } catch (const SKError& error) {

        cerr << error << endl;
        m = 1;
        descriptor->setMass(m, index);
    }

    mass->setValue(m, true);
}

/* System panel section */

#include "edit/valuevisual.h"

void PenduleCouplePanel::gravityChange(double g)
{
    if (desc->getMass(0) >= 10 && g > 1000)
        g = 1000;
    else if (g > 500)
        g = 500;

    try {

        desc->setGravity(g);

    } catch (const SKError& error) {

        cerr << error << endl;
        g = 9.81;
        desc->setGravity(g);
    }

    gravity->setValue(g, true);
}

PenduleCouplePanel::PenduleCouplePanel(PenduleCouple* pendule, QWidget *parent)
    : SystemPanel(pendule, parent), pendule(pendule)
{
    desc = static_cast<PenduleDesc*>(pendule->getDescriptor());

    layout = new QHBoxLayout;

    gravity = new Valuedit("Gravity", desc->getGravity());
    energy = new Valuevisual("Total energy", pendule->energy());

    layout->addWidget(gravity);
    layout->addWidget(energy);

    SystemPanel::addToDedicated(gravity);
    SystemPanel::addToDedicated(energy);

    SystemPanel::setDedicatedLayout(layout);

    spheres[0] = new PenduleSpherePanel(pendule->getSphere(0), desc, 0);
    spheres[1] = new PenduleSpherePanel(pendule->getSphere(1), desc, 1);

    /* Setup plotting */

    plot = new PhaseSpace("Phase space", 2);

    plot->addFunction(desc, 0);
    plot->addFunction(desc, 1);

    plot->getPlot()->setBackgroundColor(color_s(0.95, 0.95, 0.95));

    plot->getPlot()->setAxysX(SKAxys(20, -10, color_s(0, 0, 1)));
    plot->getPlot()->setAxysY(SKAxys(10, -5, color_s(0, 1, 0)));

    pushToScreen(spheres[0]);
    pushToScreen(spheres[1]);

    /* Append to phase space */
    pushToScreen(plot);

    connect(gravity, SIGNAL(valueChanged(double)), this, SLOT(gravityChange(double)));
}

PenduleCouplePanel::~PenduleCouplePanel()
{
    delete gravity;
    delete energy;
    delete layout;
}

void PenduleCouplePanel::updatePlugin()
{
    energy->setValue(pendule->energy());
}

PhaseSpace * PenduleCouplePanel::getPhaseSpace()
{
    return plot;
}
