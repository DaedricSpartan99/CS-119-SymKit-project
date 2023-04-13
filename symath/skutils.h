#ifndef SKUTILS_H
#define SKUTILS_H

namespace symkit
{
    struct color_s
    {
        /*
        * Color array RGBA
        *
        * R := red
        * G := green
        * B := blue
        * A := alpha (transparency)
        *
        * All values must be bound in the range [0, 1]
        */
        color_s(float red = 0, float green = 0, float blue = 0, float alpha = 1)

            : red(red), green(green), blue(blue), alpha(alpha) {}

        float red, green, blue, alpha;
    };

    /*
     * Enumerator for the shader identities
     */
    enum AttributeID
    {
        vertex, color
    };
}

#define COLOR_ARGS(color) color.red, color.green, color.blue, color.alpha

#endif // SKUTILS_H
