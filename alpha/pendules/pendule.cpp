#include "pendule.h"

#include "models/glsphere.h"

#include "sktools.h"

using namespace symkit;

#ifndef M_PI
#define M_PI 3.141592654
#endif

const Vector Pendule::p = {M_PI / 2};
const Vector Pendule::p_prime = {- M_PI / 4};

const double Pendule::l = 5.0;
const double Pendule::m = 1.0;

Pendule::Pendule(models::GLSphere * model)

    : OscillatorParticle(NULL, model)
{
    /* initialize descriptor */
    pendule = new PenduleS(p, p_prime, l, m);

    /* bind the descriptor */
    bind(pendule);

    /* set fill mode to false (default true) */
    toggleFillMode();

    /* set evolving to true (default false) */
    toggleEvolving();
}

Pendule::~Pendule()
{
    /* Release descriptor */
    release();

    delete pendule;
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
    setColor( alpha::colorGradientFunction(pendule->getp_prime().module(), 3.0) );
}

#include <QGLShaderProgram>

/* draw/render function */
void Pendule::render(render_s& args)
{
    OscillatorParticle::render(args);

    glBegin(GL_LINES);

    args.shaderProgram->setAttributeValue(AttributeId::vertex, ARRAY_3D_FLOAT_ARGS(SVector<3>::nullv));    // center
    args.shaderProgram->setAttributeValue(AttributeId::vertex, ARRAY_3D_FLOAT_ARGS( -position()  ));

    glEnd();
}
