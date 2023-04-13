#include "graphtools.h"

#include "specs/renderable.h"
#include "specs/colorable.h"
#include "specs/positionable.h"
#include "specs/orientable.h"
#include "specs/scalable.h"

#include <QGLShaderProgram>

void symkit::loadActorPosition(Positionable *positionable, QMatrix4x4 &matrix)
{
    if (positionable->isPositioning())
        matrix.translate(ARRAY_3D_FLOAT_ARGS(positionable->position()));
}

void symkit::loadActorOrientation(Orientable *orientable, QMatrix4x4 &matrix)
{
    if (orientable->isOrientating())
    {
        SVector<3> angles = - orientable->orientation();

        matrix.rotate((float)angles[0], {1, 0, 0});
        matrix.rotate((float)angles[1], {0, 1, 0});
        matrix.rotate((float)angles[2], {0, 0, 1});
    }
}

void symkit::loadActorScaling(Scalable *scalable, QMatrix4x4 &matrix)
{
    if (scalable->isScaling())
        matrix.scale( (float)scalable->scaling() );
}

void symkit::loadActorPolygonMode(Renderable *renderable, bool &polygonMode)
{
    if (renderable->isFillMode() && !polygonMode)
    {
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
        polygonMode = true;

    } else if (!renderable->isFillMode() && polygonMode) {

        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        polygonMode = false;
    }
}



void symkit::loadActorColor(Colorable *colorable, QGLShaderProgram *shaderProgram)
{
    if (colorable->isColoring())
        shaderProgram->setAttributeValue(AttributeID::color, COLOR_ARGS(colorable->color()));
}

symkit::mouse_s::mouse_s(int x, int y, Camera *camera, Qt::MouseButton button)

    :   x(x), y(y), camera(camera), button(button)
{

}

symkit::mouse_s::mouse_s(const mouse_s& other)
{
    *this = other;
}

bool symkit::mouse_s::operator==(const mouse_s & other) const
{
    return this->x == other.x && this->y == other.y && this->button == other.button;
}

void symkit::setGLColor(QGLShaderProgram * shaderProgram, color_s color)
{
    shaderProgram->setAttributeValue(AttributeID::color, COLOR_ARGS(color));
}

void symkit::drawGLSegment(QGLShaderProgram *shaderProgram, const SVector<3> &s1, const SVector<3> &s2)
{
    glBegin(GL_LINES);

    shaderProgram->setAttributeValue(AttributeID::vertex, ARRAY_3D_FLOAT_ARGS(s1));
    shaderProgram->setAttributeValue(AttributeID::vertex, ARRAY_3D_FLOAT_ARGS(s2));

    glEnd();
}

symkit::render_s symkit::render_s::nextMatrix(const QMatrix4x4& matrix) const
{
    render_s args = *this;
    args.matrix = matrix * this->matrix;

    return args;
}
