#ifndef PENDULE_H
#define PENDULE_H

#include "actors/particles/oscillatorparticle.h"
#include "descriptors/pendules.h"
#include "specs/evolvable.h"

namespace models
{
    class GLSphere;
}

class Pendule : public OscillatorParticle, public Evolvable
{

public:

    /* Constructor and destructor */

    Pendule(models::GLSphere *);

    ~Pendule();

    /* initialize function */
    virtual void initialize() override;

    /* set color */
    virtual void evolve(float dt) override;

    SPECS_EVOLVE

    /* draw/render function */
    virtual void render(symkit::render_s) override;

private:

    PenduleS * pendule;

    static const Vector p;
    static const Vector p_prime;

    static const double l;
    static const double m;
};

#endif // PENDULE_H
