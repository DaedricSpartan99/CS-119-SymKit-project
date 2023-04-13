#include "newtonparticle.h"
#include "descriptors/newton.h"

NewtonParticle::NewtonParticle( GLModel * model,
                    const double& mass,
                    const SVector<3>& position,
                    const SVector<3>& speed,
                    const QString &label,
                    specs_t flags)

    : Particle(NULL, model, label, flags)
{
    newtonDescriptor = new NewtonDescriptor(mass, position, speed);

    bind(newtonDescriptor);
}

NewtonParticle::NewtonParticle( const NewtonDescriptor &desc,
                    GLModel * model,
                    const QString &label,
                    specs_t flags)

    : Particle(NULL, model, label, flags)
{
    newtonDescriptor = new NewtonDescriptor(desc);

    bind(newtonDescriptor);
}

NewtonParticle::~NewtonParticle()
{
    release();

    /* Delete the instance */
    delete newtonDescriptor;
}

/* returns the position of the NewtonParticle */
SVector<3> NewtonParticle::position() const
{
    return newtonDescriptor->getPosition();
}

/* apply a force to the NewtonParticle */
void NewtonParticle::addForce(const SVector<3> &force)
{
    (*newtonDescriptor) += force;
}

/* get the mass of the NewtonParticle */
double NewtonParticle::mass() const
{
    return newtonDescriptor->getMass();
}

/* get the speed of the NewtonParticle */
const SVector<3>& NewtonParticle::speed() const
{
    return newtonDescriptor->getSpeed();
}

/* set the speed of the NewtonParticle */
void NewtonParticle::setSpeed(const SVector<3>& speed)
{
    newtonDescriptor->setSpeed(speed);
}

/* set the mass of the NewtonParticle */
void NewtonParticle::setMass(double mass)
{
    newtonDescriptor->setMass(mass);
}
