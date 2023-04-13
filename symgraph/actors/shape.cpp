#include "shape.h"
#include <QMatrix4x4>
#include <QGLShaderProgram>
#include "glmodel.h"
#include "camera.h"

#include "graphtools.h"

using namespace symkit;

Shape::Shape(GLModel * model, const QString& label, specs_t flags)

    : SKActor(label, flags), model(model)
{
    // empty
}

void Shape::setGLModel(GLModel* model)
{
    this->model = model;
}

GLModel * Shape::getGLModel()
{
    return model;
}

color_s Shape::color() const
{
    return renderColor;
}

void Shape::setColor(color_s color)
{
    renderColor = color;
}

void Shape::setColor(float r, float g, float b, float alpha)
{
    color_s color = {r, g, b, alpha};

    setColor(color);
}

void Shape::render(render_s args)
{
    if (model)
        model->draw(args.shaderProgram);
}
