#include "assets.h"

using namespace symkit;

#include <cmath>

//fonction qui gère la coloration d'un objet selon sa vitesse
color_s beta::colorGradientFunction(double energy, double limit)
{
    /* Values in zero */
    color_s color = {1.0f / 32, 1.0f / 16, 1.0f, 1.0f};
    double ratio = energy / limit;

    if (ratio < 1)
    {
        color.red = pow(2, -5 * pow(ratio - 1, 2));

        double lambda = (ratio <= 1.0f / 3) ? -36 : - 45.0 / 4;

        color.green = pow(2, lambda * pow(ratio - 1.0f / 3, 2));

        if (ratio <= 0.5f)
            color.blue = pow(2, -20 * pow(ratio, 2));
        else
            color.blue = 1.0f / 32;

    } else {

        color.red = 1;
        color.green = 1.0f / 32;
        color.blue = 1.0f / 32;
    }

    return color; //retourne la couleur selon le protocol rouge, vert, bleu, alpha
                  //où alpha represente le facteur de transparence de la couleur (de 0 à 1)
}
