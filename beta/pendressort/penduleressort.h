#ifndef PENDULERESSORT_H
#define PENDULERESSORT_H

#include "actors/systems/symsystem.h"
#include "vector.h"

class PendrSphere;
class PenduleRessort;

class GLModel;

class PenduleRessortPanel;

class PenduleR : public SymSystem
{
    // system descriptor
    PenduleRessort * descriptor;

    // array of 2 spheres
    PendrSphere * sphere[2];

    PenduleRessortPanel * panel;

public:

    /* Constructor and Destructor */
    PenduleR(GLModel *, SVector<3> offset = SVector<3>::nullv);
    //Ce premier constructeur on l'utilise pour allégerer l'écriture dans betasce

    PenduleR(GLModel *, const Vector&, const Vector&, const double&, const double&, const double&, const double&, const double& fr1 = 0, const double& fr2 = 0, const double& g = 9.81, SVector<3> offset = SVector<3>::nullv);
    ~PenduleR();

    PendrSphere * getPendule();
    PendrSphere * getRessort();

    PenduleRessortPanel * getPanel();

    virtual void evolve(float dt) override;

    virtual void render(symkit::render_s) override;

    double energy() const;

    // constants
    static const Vector pos, speed;
    static const double l, k, m1, m2, fr1, fr2, g;
};


#endif // PENDULERESSORT_H
