#ifndef PENDULEDESC_H
#define PENDULEDESC_H

#include "descriptors/oscillateur.h"

class PenduleDesc : public Oscillateur
{
    double l[2];
    double m[2];
    double g;

public:

    /* Constructors */

    PenduleDesc(double l1, double l2, double m1, double m2,
                const Vector& p, const Vector& pp, double g = 9.81);

    /* set methods, index can be 0 or 1 */

    void setLength(double l, int index);
    void setMass(double m, int index);

    /* get methods */

    double getLength(int index) const;
    double getMass(int index) const;

    double getAngle(int index) const;
    double getAngularSpeed(int index) const;

protected:

    /* equation override */

    virtual Vector equation() const override;
};

#endif // PENDULEDESC_H
