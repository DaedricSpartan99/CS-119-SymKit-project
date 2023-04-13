#ifndef PENDULE_H
#define PENDULE_H

#include "actors/particles/oscillatorparticle.h"
#include "specs/evolvable.h"

#include "vector.h"

namespace models
{
    class GLSphere;
}

class PenduleS;
class PenduleSimplePanel;

class Pendule : public OscillatorParticle, public Evolvable
{

public:

    /* Constructor and destructor */

    Pendule(models::GLSphere *, SVector<3> offset = SVector<3>::nullv, const QString& label = "");
    //Ce premier constructeur on l'utilise pour allégerer l'écriture dans betasce

    Pendule(models::GLSphere *, const Vector&, const Vector&, const double&, const double&, SVector<3> offset = SVector<3>::nullv);
    ~Pendule();

    /* initialize function */
    virtual void initialize() override;

    /* set color */
    virtual void evolve(float dt) override;

    SPECS_EVOLVE

    /* draw/render function */
    virtual void render(symkit::render_s) override;

    PenduleSimplePanel * getPanel();

private:

    PenduleS * pendule;

    PenduleSimplePanel * panel;

    static const Vector p;
    static const Vector p_prime;

    static const double l;
    static const double m;
};

#endif // PENDULE_H
