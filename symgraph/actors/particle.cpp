#include "particle.h"

Particle::Particle(Descriptor * desc, GLModel *model, const QString &label, specs_t flags)

    : Shape(model, label, flags), Describable(desc)
{

}
