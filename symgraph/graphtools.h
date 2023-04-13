#ifndef SKTOOLS_H
#define SKTOOLS_H

class Positionable;
class Orientable;
class Scalable;
class Renderable;
class Colorable;

class QGLShaderProgram;

class QMatrix4x4;
class Camera;

#include "svector.h"
#include <Qt>

#include "skutils.h"

#include <QMatrix4x4>

/*
 * Same public rendering tools
 */

namespace symkit
{
    void loadActorPosition(Positionable*, QMatrix4x4&);

    void loadActorOrientation(Orientable*, QMatrix4x4&);

    void loadActorScaling(Scalable*, QMatrix4x4&);

    void loadActorPolygonMode(Renderable*, bool&);

    void loadActorColor(Colorable*, QGLShaderProgram*);

    /*
     * Mouse event structure
     */
    struct mouse_s
    {

        mouse_s(int x, int y, Camera *, Qt::MouseButton);
        mouse_s(const mouse_s&);

        int x, y;
        Camera * camera;
        Qt::MouseButton button;

        bool operator==(const mouse_s&) const;
    };

    /*
     * Render args structure
     */
    struct render_s
    {
        QGLShaderProgram * shaderProgram;
        Camera * camera;
        QMatrix4x4 matrix;
        bool& polygonMode;

        render_s nextMatrix(const QMatrix4x4& matrix) const;
    };

    /* Some utils to handle opengl easily */

    void setGLColor(QGLShaderProgram*, color_s);

    void drawGLSegment(QGLShaderProgram *, const SVector<3>&, const SVector<3>&);
}

bool operator==(const symkit::mouse_s&, const symkit::mouse_s&);

#endif // SKTOOLS_H
