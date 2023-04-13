#ifndef SKPLOT2D_H
#define SKPLOT2D_H

#include "skplot.h"
#include "plotstream.h"

#include <vector>

struct ColoredFunction
{
    PlotStream<double> stream;
    symkit::color_s color;
};

class SKPlot2D : public SKPlot
{

    std::vector<ColoredFunction> functions;

    static symkit::color_s colorlist[6];

    // take a color from the color list
    symkit::color_s generateColor();

    virtual void keyPressEvent(QKeyEvent*) override;

public:

    SKPlot2D(float lineWidth, QWidget * parent = 0);

    virtual void paintData(QGLShaderProgram*) override;

    virtual void paintAxys(QGLShaderProgram*) override;

    std::size_t registerNewStream();

    PlotStream<double>& operator[](std::size_t n);

    PlotStream<double>& getFunctionStream(std::size_t n);

    const symkit::color_s& getFunctionColor(std::size_t n) const;

    PlotStream<double>& backStream();

    void clearAll();
};

#endif // SKPLOT2D_H
