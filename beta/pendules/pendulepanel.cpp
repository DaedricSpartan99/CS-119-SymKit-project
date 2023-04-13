#include "pendulepanel.h"

#include "pendules.h"
#include "pendule.h"

#include <QGridLayout>
#include <QVBoxLayout>
#include <QSplitter>

#include "edit/valuedit.h"
#include "edit/vectoredit.h"
#include "panels/phasespace.h"

#include "skutils.h"

#include "skplot.h"

#include "skerror.h"
#include <iostream>

using namespace std;
using namespace symkit;

void PenduleSimplePanel::angleChanged(double value)
{
    desc->setp({value});
}

void PenduleSimplePanel::speedChanged(double value)
{
    desc->setp_prime({value});
}

void PenduleSimplePanel::lengthChanged(double value)
{
    if (value > 1.0e5)
        value = 1.0e5;

    try {

        desc ->setl(value);

    } catch (const SKError& error) {

        cerr << error << endl;
        value = 1;
        desc->setl(value);
    }

    length->setValue(value, true);
}

void PenduleSimplePanel::massChanged(double value)
{
    if (value > 1.0e4)
        value = 1.0e4;

    try {

        desc->setm(value);

    } catch (const SKError& error) {

        cerr << error << endl;
        value = 1;
        desc->setm(value);
    }

    mass->setValue(value, true);
}

void PenduleSimplePanel::frictionChanged(double value)
{
    if (value > 1000)
        value = 1000;

    try {

        desc->setfr(value);

    } catch (const SKError& error) {

        cerr << error << endl;
        value = 0;
        desc->setfr(value);
    }

    friction->setValue(value, true);
}

void PenduleSimplePanel::gravityChanged(double value)
{
    try {

        desc->setg(value);

    } catch (const SKError& error) {

        cerr << error << endl;
        value = 9.81;
        desc->setg(value);
    }

    gravity->setValue(value, true);
}

void PenduleSimplePanel::offsetChanged(std::size_t index, double value)
{
    SVector<3> out = pendule->getOffset();
    out[index] = value;
    pendule->setOffset(out);
}


PenduleSimplePanel::PenduleSimplePanel(Pendule *pendule, QWidget * parent)

    : ActorPanel(pendule, parent), pendule(pendule)
{
    desc = static_cast<PenduleS*>(pendule->getDescriptor());

    /* setup splitter */

    centering = new QVBoxLayout;
    splitter = new QSplitter;

    splitter->setOrientation(Qt::Vertical);

    centering->addWidget(splitter);

    /* Phase space section */

    plot = new PhaseSpace("Simple pendule phase space", 2);

    plot->addFunction(desc, 0);

    plot->getPlot()->setBackgroundColor(color_s(0.95, 0.95, 0.95));

    plot->getPlot()->setAxysX(SKAxys(20, -10, color_s(0, 0, 1)));
    plot->getPlot()->setAxysY(SKAxys(10, -5, color_s(0, 1, 0)));

    splitter->addWidget(plot);

    /* Values section */

    valuepanel = new QWidget(splitter);

    valuesLayout = new QGridLayout;

    angle = new Valuedit(tr("&Angle"), desc->getp()[0], valuepanel);
    speed = new Valuedit(tr("&Angular speed"), desc->getp_prime()[0], valuepanel);

    length = new Valuedit(tr("&Length"), desc->getl(), valuepanel);
    mass = new Valuedit(tr("&Mass"), desc->getm(), valuepanel);
    friction = new Valuedit(tr("&Friction"), desc->getfr(), valuepanel);
    gravity = new Valuedit(tr("&Gravity"), desc->getg(), valuepanel);

    offset = new VectorEdit(tr("&Offset"), Qt::Horizontal, pendule->getOffset().rawdata(), 3, valuepanel);

    valuesLayout->addWidget(angle, 0, 0);
    valuesLayout->addWidget(speed, 0, 1);
    valuesLayout->addWidget(length, 0, 2);
    valuesLayout->addWidget(mass, 1, 0);
    valuesLayout->addWidget(friction, 1, 1);
    valuesLayout->addWidget(gravity, 1, 2);
    valuesLayout->addWidget(offset, 2, 0);

    connect(angle, SIGNAL(valueChanged(double)), this, SLOT(angleChanged(double)));
    connect(speed, SIGNAL(valueChanged(double)), this, SLOT(speedChanged(double)));
    connect(length, SIGNAL(valueChanged(double)), this, SLOT(lengthChanged(double)));
    connect(mass, SIGNAL(valueChanged(double)), this, SLOT(massChanged(double)));
    connect(friction, SIGNAL(valueChanged(double)), this, SLOT(frictionChanged(double)));
    connect(gravity, SIGNAL(valueChanged(double)), this, SLOT(gravityChanged(double)));
    connect(offset, SIGNAL(valueChanged(std::size_t,double)), this, SLOT(offsetChanged(std::size_t, double)));

    valuepanel->setLayout(valuesLayout);

    splitter->addWidget(valuepanel);

    /* Add to panels */

    splitter->setStretchFactor(0, 8);
    splitter->setStretchFactor(1, 2);

    addToDedicated(splitter);
    setDedicatedLayout(centering);
}

PenduleSimplePanel::~PenduleSimplePanel()
{
    /* it will delete recursively the others */
    delete splitter;
}

PhaseSpace * PenduleSimplePanel::getPhaseSpace()
{
    return plot;
}

void PenduleSimplePanel::updatePanel()
{
    plot->updatePanel();

    angle->setValue(desc->getp()[0]);
    speed->setValue(desc->getp_prime()[0]);
}

