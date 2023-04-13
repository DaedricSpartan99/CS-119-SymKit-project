#ifndef __CAMERA_H__
#define __CAMERA_H__

#include "svector.h"
#include <QMatrix4x4>

class QGLShaderProgram;

enum Axys
{
    X = 0, Y, Z
};

class Camera
{

public:

    /* Constructor and Destructor */
    Camera();

    ~Camera();

    // position modifiers
    const SVector<3>& getPosition() const;

    void move(const SVector<3>&);

    void move(float, Axys);

    // rotation modifier
    void rotate(float, Axys);

    // get position relative to the axys
    double get(Axys);

    // get the angles relative to the camera view
    double verticalAngle() const;
    double horizontalAngle() const;

    // reset to the origin
    void home();

    /* It determines the result from the view matrix and another one passed as argument */
    QMatrix4x4 resolve(const QMatrix4x4&);

    const QMatrix4x4& getMatrix() const;

    void loadModelview(QGLShaderProgram*, const QMatrix4x4&);

    static const char * unif_modelview;

private:

    /* Absolute position x, y, z */
    SVector<3> position;

    /*
     * Absolute angular view orientation
     *
     * First angle: orientation following the Y axys
     * Second angle: orientation following the X axys
     */
    SVector<2> angles;

    QMatrix4x4 matrix;
};

#endif
