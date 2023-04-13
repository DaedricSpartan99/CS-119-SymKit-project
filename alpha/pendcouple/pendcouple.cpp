#include "pendcouple.h"
#include "pendsphere.h"
#include "penduledesc.h"

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
const Vector PenduleCouple::speed = {0, 0};

PenduleCouple::PenduleCouple(GLModel *model)

    : SymSystem(0)
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
}

PenduleCouple::~PenduleCouple()
{
    // release descriptor
    release();

    // free allocated memory
    delete sphere[0];
    delete sphere[1];

    delete descriptor;
}

#include "assets.h"

void PenduleCouple::evolve(float)
{
    sphere[0]->setColor(alpha::colorGradientFunction(descriptor->getAngularSpeed(0), 2));
    sphere[1]->setColor(alpha::colorGradientFunction(descriptor->getAngularSpeed(1), 2));
}

double PenduleCouple::energy() const
{
    double as1(descriptor->getAngularSpeed(0));
    double as2(descriptor->getAngularSpeed(1));
    double pos1(descriptor->getAngle(0));
    double pos2(descriptor->getAngle(1));

    double e(0.5*m1*l1*l1*as1*as1 + 0.5*m2*(l1*l1*as1*as1 + l2*l2*as2*as2 + 2*l1*l2*as1*as2*cos(pos1-pos2)));
    double u(-(l1+l2)*cos(pos1)*m1*g - l2*cos(pos2)*m2*g);

    return (e+u);
}

#include "sktools.h"

using namespace symkit;

void PenduleCouple::render(symkit::render_s &args)
{
    SymSystem::render(args);

    setGLColor(args.shaderProgram, color_s(1, 1, 1));

    SVector<3> delta = sphere[0]->position() - sphere[1]->position();

    drawGLSegment(args.shaderProgram, 0, delta);
    drawGLSegment(args.shaderProgram, delta, -sphere[1]->position());
}
