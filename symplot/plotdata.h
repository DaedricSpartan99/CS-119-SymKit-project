#ifndef PLOTDATA_H
#define PLOTDATA_H

/*
 * Structure for data plotting storage
 */

//represente tout point d'un graphe de type (préimage, image)
template<typename T>
struct plot_data
{
    plot_data(const T& args, double img)

        : args(args), img(img) {}

    T args;
    double img;
};

//Pour un graphe 2D
typedef plot_data<double> Point2D;

#endif // PLOTDATA_H
