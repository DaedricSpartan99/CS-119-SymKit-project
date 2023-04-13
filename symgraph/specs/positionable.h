#ifndef POSITIONABLE_H
#define POSITIONABLE_H

#include "svector.h"

class Positionable
{

public:

    virtual ~Positionable() {}

    virtual SVector<3> position() const = 0;

    virtual bool isPositioning() const = 0;
};

#endif
