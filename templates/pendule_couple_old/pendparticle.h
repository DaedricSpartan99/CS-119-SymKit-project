#ifndef PENDPARTICLE_H
#define PENDPARTICLE_H

#include "actors/particles/oscillatorparticle.h"

#include "specs/evolvable.h"

/* Forward declaration */
class PenduleC;

class PendParticle : public OscillatorParticle, public Evolvable
{
  public:

    PendParticle(PenduleC * pendulec = 0,
                GLModel * model = 0,
                const QString& label = "",
                specs_t flags = S_EVOLVE | S_RENDER | S_POSITION | S_COLOR | S_DESCRIPTOR);

    virtual void initialize() override;

    SPECS_EVOLVE

    virtual void evolve(float) override;

    const PenduleC* getPenduledescriptor() const;
};

#endif // PENDPARTICLE_H
