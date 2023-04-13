#ifndef PENDSPHERE_H
#define PENDSPHERE_H

#include "actors/shape.h"
#include "specs/positionable.h"

class PenduleDesc;

class PendSphere : public Shape, public Positionable
{
    const unsigned int id; // 0 ou 1 pour identifier la particule
    const PenduleDesc * desc;

public:

    /* Constructor */

    PendSphere(unsigned int id,
               const PenduleDesc *,
               GLModel *,
               const QString& label = "",
               specs_t flags = S_RENDER | S_COLOR | S_POSITION);

    //Retourne la position en fonction de l'id
    virtual SVector<3> position() const override;

    SPECS_POSITION
};

#endif // PENDSPHERE_H
