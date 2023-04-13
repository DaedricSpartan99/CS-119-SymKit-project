#include "pendcouple.h"
#include "pendsphere.h"
#include "penduledesc.h"
#include "pendcouplepanel.h"

#include "skplot.h"

#include "skutils.h"

using namespace symkit;

#include <cmath>

#ifndef M_PI
#define M_PI 3.141592654
#endif

const double PenduleCouple::l1 = 5;
const double PenduleCouple::l2 = 5;
const double PenduleCouple::m1 = 1;
const double PenduleCouple::m2 = 1;

const double PenduleCouple::g = 9.81;

const Vector PenduleCouple::pos = {M_PI, M_PI};
const Vector PenduleCouple::speed = {0, 0.1};

PenduleCouple::PenduleCouple(GLModel *model, SVector<3> offset, const QString& label)

    : SymSystem(0, offset, label)
{
    // initialize components
    descriptor = new PenduleDesc(l1, l2, m1, m2, pos, speed, g);

    sphere[0] = new PendSphere(0, descriptor, model, "Internal sphere");
    sphere[1] = new PendSphere(1, descriptor, model, "External sphere");

    // bind descriptor
    bind(descriptor);

    // bind actors to the scene
    addActor(sphere[0]);
    addActor(sphere[1]);

    sphere[0]->setColor(1, 0.5, 0.5);
    sphere[1]->setColor(0.5, 0.5, 1);

    panel = new PenduleCouplePanel(this);
}

PenduleCouple::PenduleCouple(GLModel * model, const Vector& pos, const Vector& speed, const double& l1, const double& l2, const double& m1, const double& m2, const double& g, SVector<3> offset)
    : SymSystem(0, offset)
{
    // initialize components
    descriptor = new PenduleDesc(l1, l2, m1, m2, pos, speed, g);

    sphere[0] = new PendSphere(0, descriptor, model);
    sphere[1] = new PendSphere(1, descriptor, model);

    // bind descriptor
    bind(descriptor);

    // bind actors to the scene
    addActor(sphere[0]);
    addActor(sphere[1]);

    sphere[0]->setColor(1, 0.5, 0.5);
    sphere[1]->setColor(0.5, 0.5, 1);

    panel = new PenduleCouplePanel(this);
}

PenduleCouple::~PenduleCouple()
{
    // release descriptor
    release();

    // free allocated memory
    delete sphere[0];
    delete sphere[1];

    delete descriptor;

    //delete plot;
}

PenduleCouplePanel * PenduleCouple::getViewer()
{
    return panel;
}

PhaseSpace * PenduleCouple::getPhaseSpace()
{
    return panel->getPhaseSpace();
}

PendSphere * PenduleCouple::getSphere(int index)
{
    if (index > 1 || index < 0)
        return 0;

    return sphere[index];
}

#include "assets.h"

void PenduleCouple::evolve(float dt)
{
    SymSystem::evolve(dt);

    sphere[0]->setColor(beta::colorGradientFunction(descriptor->kineticEnergy(0), 200));
    sphere[1]->setColor(beta::colorGradientFunction(descriptor->kineticEnergy(1), 200));
}

double PenduleCouple::energy() const
{
    return descriptor->energy();
}

const PenduleDesc * PenduleCouple::getPenduleDescriptor() const
{
    return descriptor;
}

#include "graphtools.h"

using namespace symkit;

void PenduleCouple::render(symkit::render_s args)
{
    SymSystem::render(args);//cela dessinne les particules

    setGLColor(args.shaderProgram, color_s(1, 1, 1));

    //ensuite on dessinne les fils
    SVector<3> delta = sphere[0]->position() - sphere[1]->position();

    drawGLSegment(args.shaderProgram, 0, delta);
    drawGLSegment(args.shaderProgram, delta, -sphere[1]->position());
}
