#include "oscillatorparticle.h"

#include "descriptors/oscillateursimple.h"

OscillatorParticle::OscillatorParticle(OscillateurSimple * oscillateur, GLModel * model, SVector<3> offset, const QString& label, specs_t flags)

    : Particle(oscillateur, model, label, flags), offset(offset)
{

}

//retourne la position absolu dans le monde 3D
SVector<3> OscillatorParticle::position() const
{
    return cast_descriptor<OscillateurSimple>()->cartesiennes() + offset;
}

const SVector<3>& OscillatorParticle::getOffset() const
{
    return offset;
}

void OscillatorParticle::setOffset(const SVector<3>& offset)
{
    this->offset=offset;
}

//retourne la position relative à l'offset du système
SVector<3> OscillatorParticle::relativePosition()
{
    return cast_descriptor<OscillateurSimple>()->cartesiennes();
}
