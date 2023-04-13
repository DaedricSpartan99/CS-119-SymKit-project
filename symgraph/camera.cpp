#include "camera.h"
#include "svector.h"
#include <QMatrix4x4>
#include <cmath>

#ifndef M_PI
#define M_PI 3.142592654
#endif

const char * Camera::unif_modelview = "modelview";

Camera::Camera() : position(0), angles(0)
{
    home(); 
}

Camera::~Camera()
{

}

void Camera::move(const SVector<3> &delta)
{
    position += delta;

    // A bit inefficient, but it works for the moment
    move( delta[X] , X);
    move( delta[Y] , Y);
    move( delta[Z] , Z);
}

void Camera::move(float delta, Axys axys)
{
    QMatrix4x4 supp;
    bool done = true;

    switch(axys)
    {
    case X:

        position[X] += delta * cos( M_PI * horizontalAngle() / 180.0);
        position[Z] -= delta * sin( M_PI * horizontalAngle() / 180.0);

        supp.translate( (float) -delta, 0, 0);
        break;

    case Y:

        // increase vertical location
        position[Y] += delta;

        // project translation relative to the current Y angle
        // it corresponds to a translation Y positive and Z positive
        supp.translate( 0,
                        (float) - cos( M_PI * verticalAngle() / 180.0) * delta,
                        (float) - sin( M_PI * verticalAngle() / 180.0) * delta);
        break;

    case Z:

        position[X] += delta * sin( M_PI * horizontalAngle() / 180.0);
        position[Z] += delta * cos( M_PI * horizontalAngle() / 180.0);

        supp.translate(0,
                       (float) delta * sin( M_PI * verticalAngle() / 180.0),
                       (float) - delta * cos( M_PI * verticalAngle() / 180.0));
        break;


    default:
        done = false;
        break;
    }

    // update only if modified
    if (done)
        matrix = supp * matrix;
}

void Camera::rotate(float delta, Axys axys)
{
    QMatrix4x4 supp;
    bool done = true;

    switch(axys)
    {
    case X:

        angles[1] += delta;

        supp.rotate(delta, 1, 0, 0);
        break;

    case Y:

        angles[0] += delta;

        supp.rotate(delta, 0,
                            -cos(M_PI * verticalAngle() / 180.0),
                            -sin(M_PI * verticalAngle() / 180.0));
        break;

    default:
        done = false;
        break;
    }

    if (done)
        matrix = supp * matrix;
}

const SVector<3>& Camera::getPosition() const {

    return position;
}

double Camera::get(Axys axys)
{
    return position[axys];
}

double Camera::verticalAngle() const
{
    return angles[1];
}

double Camera::horizontalAngle() const
{
    return angles[0];
}

void Camera::home()
{
    // reset the matrix
    matrix.setToIdentity();

    // reset counting
    position.null();
    angles.null();

}

QMatrix4x4 Camera::resolve(const QMatrix4x4& matrix)
{
    return this->matrix * matrix;
}

const QMatrix4x4& Camera::getMatrix() const
{
    return matrix;
}

#include <QGLShaderProgram>

void Camera::loadModelview(QGLShaderProgram* program, const QMatrix4x4& matrix)
{
    program->setUniformValue(unif_modelview, this->matrix * matrix);
}
