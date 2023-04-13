#include "skplot2d.h"

using namespace std;
using namespace symkit;

color_s SKPlot2D::colorlist[6] =
        {
            color_s(1), // red
            color_s(0.75, 0.75), // yellow
            color_s(0, 1), // blue
            color_s(0, 0.75, 0.75), // cyan
            color_s(0, 0, 1), // blue
            color_s(0.75, 0, 0.75) // violet

        }; // size 6

color_s SKPlot2D::generateColor()
{
    return colorlist[functions.size() % 6];
}

SKPlot2D::SKPlot2D(float lineWidth, QWidget * parent)

    : SKPlot(lineWidth, parent)
{

}

#include <QGLShaderProgram>

void SKPlot2D::paintAxys(QGLShaderProgram *shaderProgram)
{
    glBegin(GL_LINES);

    const SKAxys* axys[] = {&getAxysX(), &getAxysY()};

    //cout << "Symplot: drawing axys" << endl;

    shaderProgram->setAttributeValue(AttributeID::color, COLOR_ARGS(axys[0]->color));

    // axys X

    shaderProgram->setAttributeValue(AttributeID::vertex, axys[0]->offset, 0.0f, 0.0f);
    shaderProgram->setAttributeValue(AttributeID::vertex, axys[0]->offset + axys[0]->range, 0.0f, 0.0f);

    shaderProgram->setAttributeValue(AttributeID::color, COLOR_ARGS(axys[1]->color));

    // axys Y

    shaderProgram->setAttributeValue(AttributeID::vertex, 0.0f, axys[1]->offset, 0.0f);
    shaderProgram->setAttributeValue(AttributeID::vertex, 0.0f, axys[1]->offset + axys[1]->range, 0.0f);

    glEnd();
}

void SKPlot2D::paintData(QGLShaderProgram * shaderProgram)
{
    for (const auto& function : functions)
    {
        shaderProgram->setAttributeValue(AttributeID::color, COLOR_ARGS(function.color));

        glBegin(GL_LINE_STRIP);

        for (const auto& point : function.stream)
            shaderProgram->setAttributeValue(AttributeID::vertex, point.args, point.img, 0);

        glEnd();
    }
}

size_t SKPlot2D::registerNewStream()
{
    ColoredFunction func;

    func.color = generateColor();
    functions.push_back(func);

    return functions.size() - 1;
}

PlotStream<double>& SKPlot2D::operator[](size_t n)
{
    return getFunctionStream(n);
}

PlotStream<double>& SKPlot2D::getFunctionStream(size_t n)
{
    return functions[n].stream;
}

const color_s& SKPlot2D::getFunctionColor(size_t n) const
{
    return functions[n].color;
}

PlotStream<double>& SKPlot2D::backStream()
{
    return functions.back().stream;
}

#include <QKeyEvent>

void SKPlot2D::keyPressEvent(QKeyEvent *ev)
{
    switch(ev->key())
    {
    case Qt::Key_W:
        getAxysX().zoom(1.25f);
        getAxysY().zoom(1.25f);
        break;

    case Qt::Key_S:
        getAxysX().zoom(0.8f);
        getAxysY().zoom(0.8f);
        break;

    case Qt::Key_L:
        getAxysX().translate(0.1);
        break;

    case Qt::Key_H:
        getAxysX().translate(-0.1);
        break;

    case Qt::Key_K:
        getAxysY().translate(0.1);
        break;

    case Qt::Key_J:
        getAxysY().translate(-0.1);
        break;

    default:
        return; // do not update anything
    }

    /* Update axys range */
    scheduleAxysUpdate();
}

void SKPlot2D::clearAll()
{
    for (auto& f : functions)
        f.stream.clear();
}
