#include "pendparticle.h"
#include "descriptors/pendulec.h"

PendParticle::PendParticle( PenduleC * pendulec,
                            GLModel * model,
                            const QString& label,
                            specs_t flags)

    : OscillatorParticle(pendulec, model, SVector<3>::nullv, label, flags)
{
    setColor(1, 1, 1);
}

const PenduleC* PendParticle::getPenduledescriptor() const
{
    return cast_descriptor<PenduleC>();
}

#include "skerror.h"

using namespace symkit;

void PendParticle::initialize()
{
    if (!isBound())
        throw SKError(ERR_INIT,
                      "initialize",
                      "alpha.PendParticle"
                      "Descriptor ins't bound");
}

#include "assets.h"

void PendParticle::evolve(float)
{
    setColor( alpha::colorGradientFunction(getPenduledescriptor()->getp_prime().module(), 3.0) );
}
