#ifndef __COLORABLE_H__
#define __COLORABLE_H__

#include "graphtools.h"


class Colorable
{

public:

    virtual ~Colorable() {}

    virtual symkit::color_s color() const = 0;

    virtual bool isColoring() const = 0;
};

#endif
