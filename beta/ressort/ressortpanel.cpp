#include "ressortpanel.h"

#include "ressor.h"
#include "ressort.h"

#include <QVBoxLayout>
#include <QGridLayout>

#include <QSplitter>

#include "panels/phasespace.h"

#include "edit/valuedit.h"
#include "edit/vectoredit.h"

#include "skplot2d.h"

#include "skutils.h"

#include "skerror.h"
#include <iostream>

using namespace std;
using namespace symkit;

void RessortPanel::positionChanged(double value)
{
    desc->setp({value});
}

void RessortPanel::speedChanged(double value)
{
    desc->setp_prime({value});
}

void RessortPanel::kChanged(double value)
{
    try {

        desc->setk(value);

    } catch (const SKError& error) {

        cerr << error << endl;
        desc->setk(1);
        k->setValue(1, true);
    }
}

void RessortPanel::massChanged(double value)
{
    if (value < desc->getfr() / 100)
        value = desc->getfr() / 100;

    try {

        desc->setm(value);

    } catch (const SKError& error) {

        cerr << error << endl;
        value = 1;
        desc->setm(value);
    }

    mass->setValue(value, true);
}

void RessortPanel::frictionChanged(double value)
{
    if (value > 100 * desc->getm())
        value = 100 * desc->getm();

    try {

        desc->setfr(value);

    } catch (const SKError& error) {

        cerr << error << endl;
        value = 1;
        desc->setfr(value);
    }

    friction->setValue(value, true);
}

void RessortPanel::lengthChanged(double value)
{
    desc->setl(value);
}

void RessortPanel::gravityChanged(double value)
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

void RessortPanel::axysChange(std::size_t index, double value)
{
    Vector v = desc->getAxe();

    while(v.size() < 3)
        v.augmente();

    v[index] = value;

    desc->setAxe(v);
}

void RessortPanel::offsetChanged(std::size_t index, double value)
{
    SVector<3> out = ressor->getOffset();
    out[index] = value;
    ressor->setOffset(out);
}

RessortPanel::RessortPanel(Ressor *ressor, QWidget * parent)

    : ActorPanel(ressor, parent), ressor(ressor)
{
    desc = static_cast<Ressort*>(ressor->getDescriptor());

    /* setup splitter */

    centering = new QVBoxLayout;
    splitter = new QSplitter;

    splitter->setOrientation(Qt::Vertical);

    centering->addWidget(splitter);

    /* Phase space section */

    plot = new PhaseSpace("Ressort phase space", 2);

    plot->addFunction(desc, 0);

    plot->getPlot()->setBackgroundColor(color_s(0.95, 0.95, 0.95));

    plot->getPlot()->setAxysX(SKAxys(20, -10, color_s(0, 0, 1)));
    plot->getPlot()->setAxysY(SKAxys(10, -5, color_s(0, 1, 0)));

    splitter->addWidget(plot);

    /* Values section */

    valuepanel = new QWidget(splitter);

    valuesLayout = new QGridLayout;

    position = new Valuedit(tr("&Position"), desc->getp()[0], valuepanel);
    speed = new Valuedit(tr("&Speed"), desc->getp_prime()[0], valuepanel);

    offset = new VectorEdit(tr("&Offset"), Qt::Horizontal, ressor->getOffset().rawdata(), 3, valuepanel);

    k = new Valuedit(tr("&K"), desc->getk(), valuepanel);
    mass = new Valuedit(tr("&Mass"), desc->getm(), valuepanel);
    friction = new Valuedit(tr("&Friction"), desc->getfr(), valuepanel);
    length = new Valuedit(tr("&Length"), desc->getl(), valuepanel);
    gravity = new Valuedit(tr("&Gravity"), desc->getg(), valuepanel);

    axys = new VectorEdit(tr("&Translation axys"), Qt::Horizontal, desc->getAxe().rawdata(), 3, valuepanel);

    valuesLayout->addWidget(position, 0, 0);
    valuesLayout->addWidget(speed, 0, 1);
    valuesLayout->addWidget(offset, 0, 2);

    valuesLayout->addWidget(k, 1, 0);
    valuesLayout->addWidget(axys, 1, 1);
    valuesLayout->addWidget(mass, 1, 2);

    valuesLayout->addWidget(friction, 2, 0);
    valuesLayout->addWidget(length, 2, 1);
    valuesLayout->addWidget(gravity, 2, 2);

    connect(position, SIGNAL(valueChanged(double)), this, SLOT(positionChanged(double)));
    connect(speed, SIGNAL(valueChanged(double)), this, SLOT(speedChanged(double)));
    connect(offset, SIGNAL(valueChanged(std::size_t,double)), this, SLOT(offsetChanged(std::size_t,double)));

    connect(length, SIGNAL(valueChanged(double)), this, SLOT(lengthChanged(double)));
    connect(mass, SIGNAL(valueChanged(double)), this, SLOT(massChanged(double)));
    connect(friction, SIGNAL(valueChanged(double)), this, SLOT(frictionChanged(double)));
    connect(gravity, SIGNAL(valueChanged(double)), this, SLOT(gravityChanged(double)));

    connect(axys, SIGNAL(valueChanged(std::size_t,double)), this, SLOT(axysChange(std::size_t,double)));

    valuepanel->setLayout(valuesLayout);

    splitter->addWidget(valuepanel);

    /* Add to panels */

    splitter->setStretchFactor(0, 7);
    splitter->setStretchFactor(1, 3);

    addToDedicated(splitter);
    setDedicatedLayout(centering);
}

RessortPanel::~RessortPanel()
{
    /* it will delete recursively all added panels */
    delete splitter;
}

PhaseSpace * RessortPanel::getPhaseSpace()
{
    return plot;
}

void RessortPanel::updatePanel()
{
    plot->updatePanel();

    position->setValue(desc->getp()[0]);
    speed->setValue(desc->getp_prime()[0]);
}

