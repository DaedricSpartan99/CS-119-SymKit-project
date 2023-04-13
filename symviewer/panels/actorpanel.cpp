#include "actorpanel.h"

#include <QSplitter>
#include <QVBoxLayout>
#include "specschecker.h"
#include "skactor.h"

#include "integratorchecker.h"

ActorPanel::ActorPanel(SKActor * actor, QWidget * parent)
    : SKViewerPanel(parent), actor(actor), integrators(0)
{
    splitter = new QSplitter(this);
    centering = new QVBoxLayout;

    centering->addWidget(splitter);

    dedicated = new QWidget;
    checkerContainer = new QWidget;

    checkerLayout = new QVBoxLayout;

    splitter->addWidget(dedicated);
    splitter->addWidget(checkerContainer);

    checkerSplitter = new QSplitter(checkerContainer);

    checkerLayout->addWidget(checkerSplitter);

    checkerContainer->setLayout(checkerLayout);

    checker = new SpecsChecker(actor);

    checkerSplitter->addWidget(checker);

    checkerSplitter->setOrientation(Qt::Vertical);

    Oscillateur * oscill = IntegratorChecker::getOscillator(actor);

    if (oscill)
    {
        integrators = new IntegratorChecker(oscill);
        checkerSplitter->addWidget(integrators);

        checkerSplitter->setStretchFactor(0, 7);
        checkerSplitter->setStretchFactor(1, 3);
    }

    splitter->setCollapsible(1, true);

    splitter->setStretchFactor(0, 9);
    splitter->setStretchFactor(1, 1);

    setLayout(centering);
}

ActorPanel::~ActorPanel()
{
    delete checker;
}

void ActorPanel::setActor(SKActor * actor)
{
    this->actor = actor;
    checker->setActor(actor);
}

SKActor * ActorPanel::getActor()
{
    return actor;
}

const SKActor * ActorPanel::getActor() const
{
    return actor;
}

SpecsChecker * ActorPanel::getChecker()
{
    return checker;
}

const SpecsChecker * ActorPanel::getChecker() const
{
    return checker;
}

QString ActorPanel::getLabel() const
{
    return actor->getLabel();
}


QWidget * ActorPanel::getDedicated()
{
    return dedicated;
}

QWidget * ActorPanel::actorPanelDedicated()
{
    return dedicated;
}

void ActorPanel::setEvolvingState(bool value)
{
    SpecsBox * box = checker->getByFlag(S_EVOLVE);

    if (box)
        box->setChecked(value);
}

void ActorPanel::setRenderingState(bool value)
{
    SpecsBox * box = checker->getByFlag(S_RENDER);

    if (box)
        box->setChecked(value);
}

void ActorPanel::setPositioningState(bool value)
{
    SpecsBox * box = checker->getByFlag(S_POSITION);

    if (box)
        box->setChecked(value);
}

void ActorPanel::setOrientingState(bool value)
{
    SpecsBox * box = checker->getByFlag(S_ORIENTATION);

    if (box)
        box->setChecked(value);
}

void ActorPanel::setScalingState(bool value)
{
    SpecsBox * box = checker->getByFlag(S_SCALING);

    if (box)
        box->setChecked(value);
}

void ActorPanel::setColoringState(bool value)
{
    SpecsBox * box = checker->getByFlag(S_COLOR);

    if (box)
        box->setChecked(value);
}

void ActorPanel::setDescribingState(bool value)
{
    SpecsBox * box = checker->getByFlag(S_DESCRIPTOR);

    if (box)
        box->setChecked(value);
}

