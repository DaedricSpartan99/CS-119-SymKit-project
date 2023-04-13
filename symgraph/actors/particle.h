#ifndef PARTICLE_H
#define PARTICLE_H

#include "shape.h"
#include "specs/describable.h"
#include "specs/positionable.h"

class Particle : public Shape, public Positionable, public Describable
{

public:

    /* Constructor */
    Particle(   Descriptor * desc = 0,
                GLModel * model = 0,
                const QString &label = "",
                specs_t flags = S_RENDER | S_FILL_MODE | S_POSITION | S_COLOR | S_DESCRIPTOR);

    SPECS_POSITION

    SPECS_DESCRIPTOR
};

#endif // PARTICLE_H
