#include "assets.h"

using namespace symkit;

#include <cmath>

color_s alpha::colorGradientFunction(double speed, double limit)
{
    color_s color = {0.96f, 0.56f, 0.1f, 1.0f};

    if (speed < limit)
    {
        color.red -= (1.0 - speed / limit) * 0.76f;

        color.green -= abs(1.0 - 2 * speed / limit) * 0.3f;

        if (speed < limit / 4)
            color.blue += (1.0 - 4 * speed / limit) * 0.86f;

    } else {

        color.green = 0.26f;
    }

    return color;
}

