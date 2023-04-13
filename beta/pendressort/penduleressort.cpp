#include "penduleressort.h"
#include "pendulersphere.h"
#include "penduleressortdesc.h"

#include "penduleressortpanel.h"

#include <cmath>

#ifndef M_PI
#define M_PI 3.141592654
#endif

const double PenduleR::l = 5;
const double PenduleR::k = 2;
const double PenduleR::m1 = 1;
const double PenduleR::m2 = 1;
const double PenduleR::fr1 = 0;
const double PenduleR::fr2 = 0;

const double PenduleR::g = 9.81;

const Vector PenduleR::pos = {10, 0};
const Vector PenduleR::speed = {0, 0};

PenduleR::PenduleR(GLModel *model, SVector<3> offset)

    : SymSystem(0, offset, "Pendule ressort")
{
    // initialize components
    descriptor = new PenduleRessort( pos, speed, k, l, m1, m2, fr1, fr2, g);

    sphere[0] = new PendrSphere(0, descriptor, model, "Ressort node");
    sphere[1] = new PendrSphere(1, descriptor, model, "Pendule node");

    // bind descriptor
    bind(descriptor);

    // bind actors to the scene
    addActor(sphere[0]);
    addActor(sphere[1]);

    sphere[0]->setColor(1, 0.5, 0.5);
    sphere[1]->setColor(0.5, 0.5, 1);

    panel = new PenduleRessortPanel(this);
}

PenduleR::PenduleR(GLModel * model, const Vector& pos, const Vector& speed, const double& k, const double& l, const double& m1, const double& m2, const double& fr1, const double& fr2, const double& g, SVector<3> offset)

    : SymSystem(0, offset)
{
    // initialize components
    descriptor = new PenduleRessort( pos, speed, k, l, m1, m2, fr1, fr2, g);

    sphere[0] = new PendrSphere(0, descriptor, model);
    sphere[1] = new PendrSphere(1, descriptor, model);

    // bind descriptor
    bind(descriptor);

    // bind actors to the scene
    addActor(sphere[0]);
    addActor(sphere[1]);

    sphere[0]->setColor(1, 0.5, 0.5);
    sphere[1]->setColor(0.5, 0.5, 1);
}


PenduleR::~PenduleR()
{
    // release descriptor
    release();

    // free allocated memory
    delete sphere[0];
    delete sphere[1];

    delete descriptor;
}

#include "assets.h"

void PenduleR::evolve(float)
{
    sphere[0]->setColor(beta::colorGradientFunction(descriptor->ressortKineticEnergy(), 80));
    sphere[1]->setColor(beta::colorGradientFunction(descriptor->penduleKineticEnergy(), 120));
}

#include "graphtools.h"

using namespace symkit;

void PenduleR::render(symkit::render_s args)
{
    SymSystem::render(args); //dessinne les particules

    setGLColor(args.shaderProgram, color_s(1, 1, 1));

    SVector<3> delta = sphere[0]->position() - sphere[1]->position();

    //ensuite les fils
    drawGLSegment(args.shaderProgram, 0, delta);
    drawGLSegment(args.shaderProgram, delta, -sphere[1]->position());
}

 PendrSphere * PenduleR::getPendule()
 {
     return sphere[1];
 }

 PendrSphere * PenduleR::getRessort()
 {
     return sphere[0];
 }

 PenduleRessortPanel * PenduleR::getPanel()
 {
     return panel;
 }

 double PenduleR::energy() const
 {
     return descriptor->energy();
 }
