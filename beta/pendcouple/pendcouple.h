#ifndef PENDCOUPLE_H
#define PENDCOUPLE_H

#include "actors/systems/symsystem.h"
#include "vector.h"

class PendSphere;
class PenduleDesc;
class PhaseSpace;

class GLModel;

class PenduleCouplePanel;

class PenduleCouple : public SymSystem
{
    // system descriptor
    PenduleDesc * descriptor;

    // array of 2 spheres
    PendSphere * sphere[2];

    PenduleCouplePanel * panel;

public:

    /* Constructor and Desstructor */
    PenduleCouple(GLModel *, SVector<3> offset = SVector<3>::nullv, const QString& label = "");
    //Ce premier constructeur on l'utilise pour allégerer l'écriture dans betasce

    PenduleCouple(GLModel *, const Vector&, const Vector&, const double&, const double&, const double&, const double&, const double& g = 9.81, SVector<3> offset = SVector<3>::nullv);
    ~PenduleCouple();

    /* Pour controler si l'énergie reste constant, éviter divergernces */
    double energy() const;

    PendSphere * getSphere(int index);

    const PenduleDesc * getPenduleDescriptor() const;

    PenduleCouplePanel * getViewer();

    PhaseSpace * getPhaseSpace();

    virtual void evolve(float dt) override;

    virtual void render(symkit::render_s) override;

    // constantes pour la construction par defaut du système
    static const Vector pos, speed;
    static const double l1, l2, m1, m2, g;
};

#endif // PENDCOUPLE_H
