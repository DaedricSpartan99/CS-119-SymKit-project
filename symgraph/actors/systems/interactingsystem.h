#ifndef PARTICLESYSTEM_H
#define PARTICLESYSTEM_H


#include "particlesystem.h"

class InteractingSystem : public ParticleSystem
{
public:

    /*
     * Two times update call, for each particle
     * updateForces then evolve
     */
    virtual void evolve(float) override;

    /*
     * Overriding this methods allows to check
     * the type of the entries
     */

    virtual void attach(Particle *) override;

    /*
     * Interaction function between two particles
     */
    virtual void interaction(Particle*, Particle*) = 0;
};

#endif // PARTICLESYSTEM_H
