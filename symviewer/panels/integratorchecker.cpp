#include "integratorchecker.h"

#include <QRadioButton>

#include <QVBoxLayout>

#include "descriptors/oscillateur.h"

void IntegratorChecker::switchToEulerCromer()
{
    desc->setIntegrationOperation(EULER_CROMER);

    newmark->setChecked(false);
}

void IntegratorChecker::switchToNewmark()
{
    desc->setIntegrationOperation(NEWMARK);

    euler_cromer->setChecked(false);
}

IntegratorChecker::IntegratorChecker(Oscillateur *desc, QWidget * parent)

    : QGroupBox(tr("&Integrators"), parent), desc(desc)
{
    layout = new QVBoxLayout;

    euler_cromer = new QRadioButton(tr("&Euler-Cromer"), this);
    newmark = new QRadioButton(tr("&Newmark"), this);

    layout->addWidget(euler_cromer);
    layout->addWidget(newmark);

    connect(euler_cromer, SIGNAL(pressed()), this, SLOT(switchToEulerCromer()));
    connect(newmark, SIGNAL(pressed()), this, SLOT(switchToNewmark()));

    euler_cromer->setChecked(desc->getIntegrationOperation() == EULER_CROMER);
    newmark->setChecked(desc->getIntegrationOperation() == NEWMARK);

    setLayout(layout);
}

IntegratorChecker::~IntegratorChecker()
{
    delete euler_cromer;
    delete newmark;
}

#include "skactor.h"
#include "specs/describable.h"

Oscillateur * IntegratorChecker::getOscillator(SKActor *actor)
{
    Describable * d = dynamic_cast<Describable*>(actor);

    if (!d)
        return 0;

    return dynamic_cast<Oscillateur*>(d->getDescriptor());
}
