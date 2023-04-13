#ifndef PENDULECOUPL_H
#define PENDULECOUPL_H

#include "pendparticle.h"
#include "actors/particlesystem.h"
#include "vector.h"

/* Forward declaration */
class PendParticle;
class PenduleC1;
class PenduleC2;

class GLModel;

class PenduleCoupl : public ParticleSystem
{
public:

    /* Constructor and Destructor */
    PenduleCoupl(GLModel * model);
    ~PenduleCoupl();

    /* initialize function */
    //virtual void initialize() override;

    virtual void render(symkit::render_s &) override;

    double energy() const;

private:

    /* Descriptors */
    PenduleC1 * pendulec1;
    PenduleC2 * pendulec2;

    /* Particles */

    PendParticle * pend1;
    PendParticle * pend2;

    /* Initialization values */

    static const Vector p1;
    static const Vector p_prime1;
    static const Vector p2;
    static const Vector p_prime2;

    static const double l1;
    static const double m1;
    static const double l2;
    static const double m2;
};

#endif // PENDULEC_H
