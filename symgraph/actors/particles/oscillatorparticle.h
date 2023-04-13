#ifndef OSCILLATOR_PARTICLE_H
#define OSCILLATOR_PARTICLE_H

#include "actors/particle.h"

class OscillateurSimple;

class OscillatorParticle : public Particle
{
private:
    SVector<3> offset;

public:

    /* Constructor */

    OscillatorParticle( OscillateurSimple * oscillateur = 0,
                        GLModel * model = 0,
                        SVector<3> offset = SVector<3>::nullv,
                        const QString& label = "",
                        specs_t flags = S_RENDER | S_FILL_MODE | S_POSITION | S_COLOR | S_DESCRIPTOR);

    /* Pour obtenir la position de la particule */
    virtual SVector<3> position() const override;

    /* Accesseur et Manipulateur à l'offset */
    const SVector<3>& getOffset() const;
    void setOffset(const SVector<3>&);

    /* Utile pour le dessin du fil dans la scène*/
    SVector<3> relativePosition();

};

#endif // OSCILLATOR_PARTICLE_H
