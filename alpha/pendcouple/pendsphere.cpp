#include "pendsphere.h"
#include "penduledesc.h"

PendSphere::PendSphere( int id,
                        const PenduleDesc *desc,
                        GLModel *model,
                        const QString &label, specs_t flags)

    : Shape(model, label, flags), id(id), desc(desc)
{

}

#include <cmath>

SVector<3> PendSphere::position() const
{
    SVector<3> out;

    double angle = desc->getAngle(0);
    double l = desc->getLength(0);

    out += {sin(angle) * l, - cos(angle) * l, 0};

    if (id > 0)
    {
        angle = desc->getAngle(1);
        l = desc->getLength(1);
        out += {sin(angle) * l, - cos(angle) * l, 0};
    }

    return out;
}
