#ifndef PENDCOUPLE_H
#define PENDCOUPLE_H

#include "actors/symsystem.h"
#include "vector.h"

class PendSphere;
class PenduleDesc;

class GLModel;

class PenduleCouple : public SymSystem
{
    // system descriptor
    PenduleDesc * descriptor;

    // array of 2 spheres
    PendSphere * sphere[2];

public:

    PenduleCouple(GLModel *);
    ~PenduleCouple();

    double energy() const;

    virtual void evolve(float dt) override;

    virtual void render(symkit::render_s &) override;

    // constants
    static const Vector pos, speed;
    static const double l1, l2, m1, m2, g;
};

#endif // PENDCOUPLE_H
