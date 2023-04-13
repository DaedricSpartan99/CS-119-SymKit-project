#ifndef ORIENTABLE_H
#define ORIENTABLE_H

#include "svector.h"

class Orientable
{

public:

    virtual ~Orientable() {}

    virtual SVector<3> orientation() const = 0;

    virtual bool isOrientating() const = 0;
};

#endif // ORIENTED_H
