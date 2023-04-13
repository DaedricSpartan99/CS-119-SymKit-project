#define _USE_SVECTOR_OSTREAM

#include "ressor.h"
#include <iostream>

#include <QGLShaderProgram>

#include "descriptors/ressort.h"
#include "models/glsphere.h"

#include "graphtools.h"

using namespace symkit;
using namespace std;

const Vector Ressor::p = {0};
const Vector Ressor::p_prime = {10};

const Vector Ressor::axys = {1, -0.5, 1};

const double Ressor::l = 0.0;
const double Ressor::m = 1.0;
const double Ressor::k = 0.5;

Ressor::Ressor(models::GLSphere * model)

    : OscillatorParticle(NULL, model)
{
    /* initialize descriptor */
    ressort = new Ressort(p, p_prime, axys, l, m, k);

    /* bind the descriptor */
    bind(ressort);

    /* set fill mode to false (default true) */
    toggleFillMode();

    /* set evolving to true (default false) */
    toggleEvolving();
}

Ressor::~Ressor()
{

    /* delete descriptor */
    delete ressort;
}

#include "assets.h" // colorGradientFunction

/* set color */
void Ressor::evolve(float)
{
    setColor( alpha::colorGradientFunction(ressort->getp_prime().module(), 15.0) );
}

#include "skerror.h"

using namespace symkit;

void Ressor::initialize()
{
    if (!isBound())
        throw SKError(ERR_INIT,
                      "initialize",
                      "alpha.Ressor"
                      "Descriptor ins't bound");
}

/* draw/render function */
void Ressor::render(render_s args)
{
    OscillatorParticle::render(args);

    glBegin(GL_LINES);

    args.shaderProgram->setAttributeValue(AttributeID::vertex, ARRAY_3D_FLOAT_ARGS(SVector<3>::nullv));    // center
    args.shaderProgram->setAttributeValue(AttributeID::vertex, ARRAY_3D_FLOAT_ARGS( -position()  ));

    glEnd();
}
