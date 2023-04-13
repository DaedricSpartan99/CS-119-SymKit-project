#ifndef PLOTUTILS_H
#define PLOTUTILS_H

#include "skutils.h"

//contient les infos utiles pour le dessin d'un graph
struct SKAxys
{
    SKAxys(double range = 2, double offset = -1, symkit::color_s color = symkit::color_s(0, 0, 0, 1))
        : range(range), offset(offset), color(color) {}

    double range;
    double offset;
    symkit::color_s color;

    void zoom(float ratio)
    {
        offset -= range * (1.0f / ratio - 1) / 2;
        range /= ratio;
    }

    void translate(float ratio)
    {
        offset += range * ratio / 2;
    }
};

#endif // PLOTUTILS_H
