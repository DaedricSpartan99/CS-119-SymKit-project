#ifndef OSCILLATEURSIMPLE_H
#define OSCILLATEURSIMPLE_H

#include "oscillateur.h"
#include "svector.h"

class OscillateurSimple : public Oscillateur
{

public:

    OscillateurSimple(const Vector& p, const Vector& p_prime, integral_operation op = NEWMARK)

        : Oscillateur(p, p_prime, op) {}

    OscillateurSimple(const std::vector<double>& p, const std::vector<double>& p_prime, integral_operation op = NEWMARK)

        : Oscillateur(p, p_prime, op) {}

        //retourne le vecteur position
    virtual SVector<3> cartesiennes() const = 0;
};

#endif // OSCILLATEURSIMPLE_H
