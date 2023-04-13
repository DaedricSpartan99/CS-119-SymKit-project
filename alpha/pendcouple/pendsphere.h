#ifndef PENDSPHERE_H
#define PENDSPHERE_H

#include "actors/shape.h"
#include "specs/positionable.h"

class PenduleDesc;

class PendSphere : public Shape, public Positionable
{
    const int id; // 0 or 1
    const PenduleDesc * desc;

public:

    PendSphere(int id,
               const PenduleDesc *,
               GLModel *,
               const QString& label = "",
               specs_t flags = S_RENDER | S_COLOR | S_POSITION);

    virtual SVector<3> position() const override;

    SPECS_POSITION
};

#endif // PENDSPHERE_H
