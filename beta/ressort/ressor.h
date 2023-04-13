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

class RessortPanel;

class Ressor : public OscillatorParticle, public Evolvable
{

public:

    /* Constructor and Destructor */
    Ressor(models::GLSphere *, SVector<3> offset = SVector<3>::nullv);
    //Ce premier constructeur on l'utilise pour allégerer l'écriture dans betasce

    Ressor(models::GLSphere *, const Vector&, const Vector&, const Vector&, const double, const double, const double, SVector<3> offset = SVector<3>::nullv);
    ~Ressor();

    SPECS_EVOLVE

    /* set color */
    virtual void evolve(float) override;

    /* draw/render function */
    virtual void render(symkit::render_s) override;

    /* initialize function */
    virtual void initialize() override;

    RessortPanel * getPanel();

private:

    Ressort * ressort;

    RessortPanel * panel;

    static const Vector p;
    static const Vector p_prime;

    static const Vector axys;

    static const double l;
    static const double m;
    static const double k;
};

#endif // RESSORT_H
