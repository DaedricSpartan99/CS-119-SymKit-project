#define _USE_SVECTOR_OSTREAM

#include "newtonsphere.h"
#include "descriptors/newton.h"
#include "models/glsphere.h"

#include "graphtools.h"

#include "camera.h"

using namespace symkit;



const double NewtonSphere::K = 400.0;

const double NewtonSphere::pendule_l = 12.0;

const SVector<3> NewtonSphere::gravity = {0, -9.81, 0};

const double NewtonSphere::friction = 0.1;

const double NewtonSphere::mass = 5.0;

const SVector<3> NewtonSphere::init_position = { NewtonSphere::pendule_l, 0, 0 };

const SVector<3> NewtonSphere::init_speed = SVector<3>::nullv;

const NewtonDescriptor NewtonSphere::init_desc(mass, init_position, init_speed);


NewtonSphere::NewtonSphere(models::GLSphere * model)

    : NewtonParticle(model, mass, init_position, init_speed), verbose(false)
{
    /* Set the polygon mode to GL_LINE */
    toggleFillMode();

    counter = 0;
}

using namespace std;
#include <iostream>

#include "assets.h" // colorGradientFunction

void NewtonSphere::evolve(float)
{
    SVector<3> x = position();
    SVector<3> l0 = x.directional() *pendule_l;

    if (verbose)
    {
#define VERBOSE_PERIOD 50

        if (counter % VERBOSE_PERIOD == 0)
            cout << *this << endl;
    }

    ++counter;

    /* Elastic force F = -k (x - l0) */
    addForce( (l0 - x) * NewtonSphere::K );

    /* Gravity force */
    addForce(gravity * mass);

    /* Friction force */
    addForce( - speed() * friction );

    /* Set the color basing on the speed */
    setColor( beta::colorGradientFunction( 0.5 * mass * speed().sq_module(), 2000));
}

void NewtonSphere::applyRepulsion(const Camera *camera)
{
#define PULSE_K 1000.0

    SVector<3> pos = position() - camera->getPosition();

    pos *= PULSE_K / pos.sq_module();//plus proche la camera, plus forte la repulsion

    // repulse
    addForce(pos);
}

void NewtonSphere::setVerbose(bool value)
{
    this->verbose = value;
}

bool NewtonSphere::getVerbose() const
{
    return verbose;
}

#include <QGLShaderProgram>

void NewtonSphere::render(render_s args)
{
    NewtonParticle::render(args); //cela dessine la particule

    //Ensuite on dessinne le fil
    glBegin(GL_LINES);

    args.shaderProgram->setAttributeValue(AttributeID::vertex, ARRAY_3D_FLOAT_ARGS(SVector<3>::nullv));    // on centre la matrice sur la particule
    args.shaderProgram->setAttributeValue(AttributeID::vertex, ARRAY_3D_FLOAT_ARGS( -position()  ));    // on dessinne un fil sur l'inverse du vecteur position de la particule

    glEnd();
}

#include <ostream>
#include <iomanip>

ostream& operator<<(ostream& os, const NewtonSphere& sphere)
{
    os << "Yellow sphere data: " << endl << setw(4);
    os << "Position: " << sphere.position() << endl;
    os << "Speed: " << sphere.speed() << "," << "V = " << sphere.speed().module() << endl;
    os << "Mass: " << sphere.NewtonParticle::mass() << endl;

    os << setw(0);

    return os;
}
