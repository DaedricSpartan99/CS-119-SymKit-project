#include "pendule.h"

#include "models/glsphere.h"
#include "pendules.h"

#include "graphtools.h"

#include "pendulepanel.h"

using namespace symkit;

#ifndef M_PI
#define M_PI 3.141592654
#endif

const Vector Pendule::p = {M_PI / 2};
const Vector Pendule::p_prime = {- M_PI / 4};

const double Pendule::l = 5.0;
const double Pendule::m = 1.0;

Pendule::Pendule(models::GLSphere * model, SVector<3> offset, const QString& label)

    : OscillatorParticle(NULL, model,  offset, label)
{
    /* initialize descriptor */
    pendule = new PenduleS(p, p_prime, l, m);

    /* bind the descriptor */
    bind(pendule);

    /* set fill mode to false (default true) */
    toggleFillMode();

    /* set evolving to true (default false) */
    toggleEvolving();

    panel = new PenduleSimplePanel(this);
}

Pendule::Pendule(models::GLSphere * model, const Vector& p, const Vector& p_prime, const double& l, const double& m, SVector<3> offset)

    : OscillatorParticle(NULL, model, offset, "Simple pendule")
{
    /* initialize descriptor */
    pendule = new PenduleS(p, p_prime, l, m);

    /* bind the descriptor */
    bind(pendule);

    /* set fill mode to false (default true) */
    toggleFillMode();

    /* set evolving to true (default false) */
    toggleEvolving();

    panel = new PenduleSimplePanel(this);
}


Pendule::~Pendule()
{
    /* Release descriptor */
    release();

    delete pendule;
    delete panel;
}

#include "skerror.h"

using namespace symkit;

void Pendule::initialize()
{
    if (!isBound())
        throw SKError(ERR_INIT,
                      "initialize",
                      "alpha.Pendule",
                      "Descriptor isn't bound");
}

#include "assets.h" // colorGradientFunction

/* set color */
void Pendule::evolve(float)
{
    setColor( beta::colorGradientFunction(pendule->kineticEnergy(), 80.0) );
}

#include <QGLShaderProgram>

/* draw/render function */
void Pendule::render(render_s args)
{
    OscillatorParticle::render(args);//dessine la particule

    glBegin(GL_LINES);

    //ensuite le fil
    args.shaderProgram->setAttributeValue(AttributeID::vertex, ARRAY_3D_FLOAT_ARGS(SVector<3>::nullv));    // centre la matrice sur la particule
    args.shaderProgram->setAttributeValue(AttributeID::vertex, ARRAY_3D_FLOAT_ARGS(-relativePosition()));  // dessine le fil sur lînverse du vecteur position de la particule

    glEnd();
}

PenduleSimplePanel * Pendule::getPanel()
{
    return panel;
}
