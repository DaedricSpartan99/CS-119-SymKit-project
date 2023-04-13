#include "pendulersphere.h"
#include "penduleressortdesc.h"

PendrSphere::PendrSphere(unsigned int id,
                        const PenduleRessort *desc,
                        GLModel *model,
                        const QString &label, specs_t flags)

    : Shape(model, label, flags), id(id), desc(desc)
{

}

#include <cmath>

SVector<3> PendrSphere::position() const
{
    SVector<3> out;

    // position si ressort
    double position = desc->getp()[0];

    out += { position, 0, 0};

    // position si pendule
    if (isPendule())
    {
    double angle = desc->getp()[1];
    double l = desc->getLenght();

    out += {sin(angle) * l, - cos(angle) * l, 0};
    }

    return out;
}

bool PendrSphere::isPendule() const
{
    return id > 0;
}
