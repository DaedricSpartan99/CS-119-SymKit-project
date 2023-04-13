#ifndef NEWTON_PARTICLE_H
#define NEWTON_PARTICLE_H

#include "actors/particle.h"
#include "specs/evolvable.h"

class NewtonDescriptor;

class NewtonParticle : public Particle, public Evolvable
{
public:

    /* Constructors and Desructor */

    NewtonParticle(   GLModel * model = 0,
                const double& mass = 1.0,
                const SVector<3>& position = SVector<3>::nullv,
                const SVector<3>& speed = SVector<3>::nullv,
                const QString &label = "",
                specs_t flags = S_EVOLVE | S_RENDER | S_FILL_MODE | S_POSITION | S_COLOR | S_DESCRIPTOR);

    NewtonParticle(   const NewtonDescriptor&,
                GLModel * model = 0,
                const QString &label = "",
                specs_t flags = S_EVOLVE | S_RENDER | S_FILL_MODE | S_POSITION | S_COLOR | S_DESCRIPTOR);

    ~NewtonParticle();

    SPECS_EVOLVE

    /* returns the position of the particle */
    virtual SVector<3> position() const override;

    /* apply a force to the particle */
    void addForce(const SVector<3>&);

    /* get the mass of the particle */
    double mass() const;

    /* get the speed of the particle */
    const SVector<3>& speed() const;

    /* set the speed of the particle */
    void setSpeed(const SVector<3>& speed);

    /* set the mass of the particle */
    void setMass(double mass);

private:

    /* Pointer to a NewtonDescriptor,
     * needed for evolving purpose */

    NewtonDescriptor * newtonDescriptor;
};

#endif // NEWTON_PARTICLE_H
