#include "specschecker.h"

#include <QVBoxLayout>
#include "skactor.h"
#include <QLabel>
#include <QCheckBox>

#include "specs/evolvable.h"
#include "specs/renderable.h"
#include "specs/positionable.h"
#include "specs/orientable.h"
#include "specs/scalable.h"
#include "specs/colorable.h"
#include "specs/describable.h"

SpecsBox::SpecsBox(const QString& text, SKActor *actor, specs_t flag, QWidget *parent)
    : QCheckBox(text, parent), actor(actor), flag(flag)
{
    connect(this, SIGNAL(clicked(bool)), this, SLOT(toggleSpecs(bool)));
}

void SpecsBox::toggleSpecs(bool state)
{
    actor->setSpecsState(flag, state);
}

specs_t SpecsBox::getFlag() const
{
    return flag;
}


/* Specs checker group section */

SpecsChecker::SpecsChecker(SKActor * actor, QWidget * parent)

    : QGroupBox("Specs flags", parent)
{
    layout = new QVBoxLayout();

    setActor(actor, false);

    setLayout(layout);
}

SpecsChecker::~SpecsChecker()
{
    delete layout;
}

SpecsBox * SpecsChecker::registerBox(specs_t flag)
{
    QString text;

    switch(flag)
    {
    case S_EVOLVE:
        text = tr("&Evolve");
        break;
    case S_RENDER:
        text = tr("&Render");
        break;
    case S_POSITION:
        text = tr("&Positioning");
        break;
    case S_ORIENTATION:
        text = tr("&Orienting");
        break;
    case S_SCALING:
        text = tr("&Scaling");
        break;
    case S_COLOR:
        text = tr("&Coloring");
        break;
    case S_DESCRIPTOR:
        text = tr("&Evolving descriptor");
        break;
    default:
        // TODO, throw error
        break;
    }

    SpecsBox * box = new SpecsBox(text, actor, flag, this);
    box->setChecked((actor->getSpecs() & flag) != 0);

    layout->addWidget(box);

    return box;
}

SpecsBox * SpecsChecker::getByFlag(specs_t flag)
{
    for (auto box : boxes)
    {
        if (box->getFlag() == flag)
            return box;
    }

    return 0;
}


void SpecsChecker::setActor(SKActor *actor, bool reset)
{
    if (!actor)
    {
        ;// TODO throw error
        return;
    }

    this->actor = actor;

    if (reset)
    {
        for (auto box : boxes)
        {
            layout->removeWidget(box);
            disconnect(box, SIGNAL(clicked(bool)), this, 0);
        }

        boxes.clear();
    }

    Evolvable * ev = dynamic_cast<Evolvable*>(actor);

    if (ev)
        boxes.push_back(registerBox(S_EVOLVE));

    Renderable * rend = dynamic_cast<Renderable*>(actor);

    if (rend)
        boxes.push_back(registerBox(S_RENDER));

    Positionable * pos = dynamic_cast<Positionable*>(actor);

    if (pos)
        boxes.push_back(registerBox(S_POSITION));

    Orientable * orient = dynamic_cast<Orientable*>(actor);

    if (orient)
        boxes.push_back(registerBox(S_ORIENTATION));

    Scalable * scal = dynamic_cast<Scalable*>(actor);

    if (scal)
        boxes.push_back(registerBox(S_SCALING));

    Colorable * col = dynamic_cast<Colorable*>(actor);

    if (col)
        boxes.push_back(registerBox(S_COLOR));

    Describable * desc = dynamic_cast<Describable*>(actor);

    if (desc)
        boxes.push_back(registerBox(S_DESCRIPTOR));
}

SKActor * SpecsChecker::getActor()
{
    return actor;
}

const SKActor * SpecsChecker::getActor() const
{
    return actor;
}
