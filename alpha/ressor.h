#ifndef RESSORT_H
#define RESSORT_H

class Ressort;

#include "actors/particles/oscillatorparticle.h"

#include "vector.h"
#include "specs/evolvable.h"

namespace models
{
    class GLSphere;
}

class Ressor : public OscillatorParticle, public Evolvable
{
public:

    /* Constructor and Destructor */
    Ressor(models::GLSphere *);
    ~Ressor();

    SPECS_EVOLVE

    /* set color */
    virtual void evolve(float) override;

    /* draw/render function */
    virtual void render(symkit::render_s) override;

    /* initialize function */
    virtual void initialize() override;

private:

    Ressort * ressort;

    static const Vector p;
    static const Vector p_prime;

    static const Vector axys;

    static const double l;
    static const double m;
    static const double k;
};

#endif // RESSORT_H
