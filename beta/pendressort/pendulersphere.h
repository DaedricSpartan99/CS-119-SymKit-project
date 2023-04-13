#ifndef PENDULERSPHERE_H
#define PENDULERSPHERE_H


#include "actors/shape.h"
#include "specs/positionable.h"

class PenduleRessort;

class PendrSphere : public Shape, public Positionable
{
    const unsigned int id; // 0 or 1
    const PenduleRessort * desc;

public:

    PendrSphere(unsigned int id,
               const PenduleRessort *,
               GLModel *,
               const QString& label = "",
               specs_t flags = S_RENDER | S_COLOR | S_POSITION);

    virtual SVector<3> position() const override;

    SPECS_POSITION

    bool isPendule() const;
};

#endif // PENDULERSPHERE_H
