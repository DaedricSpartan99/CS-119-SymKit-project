#ifndef SCALABLE_H
#define SCALABLE_H

#include "svector.h"

class Scalable
{

public:

    virtual ~Scalable() {}

    virtual double scaling() const = 0;

    virtual bool isScaling() const = 0;
};

#endif
