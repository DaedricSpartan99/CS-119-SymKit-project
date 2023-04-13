#include "pendulecoupl.h"


#include "descriptors/pendulec1.h"
#include "descriptors/pendulec2.h"

#include "sktools.h"

using namespace symkit;

#ifndef M_PI
#define M_PI 3.141592654
#endif

const Vector PenduleCoupl::p1 = {M_PI};
const Vector PenduleCoupl::p_prime1 = {0};
const Vector PenduleCoupl::p2 = {M_PI};
const Vector PenduleCoupl::p_prime2 = {0};

const double PenduleCoupl::l1 = 5.0;
const double PenduleCoupl::m1 = 10.0;
const double PenduleCoupl::l2= 5.0;
const double PenduleCoupl::m2 = 10.0;

PenduleCoupl::PenduleCoupl(GLModel * model)

    : ParticleSystem()
{
    /* initialize descriptors */
    pendulec1 = new PenduleC1(p1, p_prime1, l1, m1);
    pendulec2 = new PenduleC2(p2, p_prime2, l2, m2);

    //pendulec2->setIntegrationOperation(EULER_CROMER);
    //pendulec1->setIntegrationOperation(EULER_CROMER);

    pendulec1->setOtherPendule(pendulec2);
    pendulec2->setOtherPendule(pendulec1);

    /* initialize particles */

    pend1 = new PendParticle(pendulec1, model);
    pend2 = new PendParticle(pendulec2, model);

    attach(pend1);
    attach(pend2);
}

PenduleCoupl::~PenduleCoupl()
{
    detachAll();

    /* Deleting pointers */
    delete pend1;
    delete pend2;

    delete pendulec1;
    delete pendulec2;
}

#include <QGLShaderProgram>

/* draw/render function */
void PenduleCoupl::render(render_s& args)
{
    ParticleSystem::render(args);

    args.shaderProgram->setAttributeValue(AttributeId::color, 1, 1, 1);

    SVector<3> c1pos = pendulec1->cartesiennes() - pendulec2->cartesiennes();

    glBegin(GL_LINES);

    args.shaderProgram->setAttributeValue(AttributeId::vertex, ARRAY_3D_FLOAT_ARGS(SVector<3>::nullv));    // center
    args.shaderProgram->setAttributeValue(AttributeId::vertex, ARRAY_3D_FLOAT_ARGS(c1pos));

    glEnd();

    glBegin(GL_LINES);
    args.shaderProgram->setAttributeValue(AttributeId::vertex, ARRAY_3D_FLOAT_ARGS(c1pos));
    args.shaderProgram->setAttributeValue(AttributeId::vertex, ARRAY_3D_FLOAT_ARGS(-pendulec2->cartesiennes()));

    glEnd();
}

#include <cmath>


/* Fonction qui calcule l'énergie de l'oscillatoire
 * Utile pour le debugging
 */
double PenduleCoupl::energy() const
{
    double l1 = pendulec1->getl();
    double m = pendulec1->getm();

    double k1 = 0.5 * m * (pendulec1->getp_prime().sq_module() * l1 * l1);
    double u1 = m * PenduleC::g * l1 * (1 - cos(pendulec1->getp()[0]));

    double l2 = pendulec2->getl();
    m = pendulec2->getm();

    double k2 = 0.5 * m * (pendulec2->getp_prime().sq_module() * l2 * l2);
    double u2 = m * PenduleC::g * (l1 * (1 - cos(pendulec1->getp()[0]) + l2 * (1 - cos(pendulec2->getp()[0]))));

    return k1 + u1 + k2 + u2;
}
