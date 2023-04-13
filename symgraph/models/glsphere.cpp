#include "glsphere.h"

#define _USE_CMATH_DEFINES
#include <cmath>

#ifndef M_PI
#define M_PI 3.141592654
#endif

#include "skerror.h"

using namespace symkit;

void models::GLSphere::initialize()
{
    groups.reserve(3);

    registerGroup(GL_TRIANGLE_FAN);
    registerGroup(GL_QUADS);
    registerGroup(GL_TRIANGLE_FAN);

    QVector<GLfloat> positions;

    QVector<GLuint> indices0;
    QVector<GLuint> indices1;
    QVector<GLuint> indices2;

    GLuint size(2 + slices * (stacks - 1));

    positions.reserve(3 * size);

    const double alpha(M_PI / double(stacks));
    const double beta(2.0*M_PI / double(slices));

    positions << 0.0 << 0.0 << 1.0;

    for (GLuint i(1); i < stacks; ++i) {
      for (GLuint j(0); j < slices; ++j) {
        float r = sin(i*alpha);
        float z = cos(i*alpha);
        float y = sin(j*beta) * r;
        float x = cos(j*beta) * r;

        positions << x << y << z;
      }
    }

    positions << 0.0 << 0.0 << -1.0;

    indices0.reserve(slices+2);
    for (GLuint i(0); i <= slices; ++i)
      indices0 << i;
    indices0 << 1;

    indices1.reserve((stacks-2) * 4 * slices);
    for (GLuint i(0); i < stacks-2; ++i) {
      for (GLuint j(0); j < slices; ++j) {
        indices1 << 1+i*slices+j;
        indices1 << 1+(i+1)*slices+j;
        indices1 << 1+(i+1)*slices+(j+1)%slices;
        indices1 << 1+i*slices+(j+1)%slices;
      }
    }

    indices2.reserve(slices+2);
    for (GLuint i(1); i <= slices+1; ++i)
      indices2 << size-i;
    indices2 << size-2;

    /* initialize buffer */
    if (!enableVBO())
        throw SKError(  ERR_INIT,
                        "models::sphere",
                        "",
                        "Could not enable VBO GLBuffer");

    vbo_size = 3 * size * sizeof(GLfloat);

    if (!vbo.bind())
        throw SKError( ERR_INIT,
                       "models::sphere",
                       "",
                       "Could not bind VBO");

    vbo.allocate(positions.constData(), vbo_size);
    vbo.release();

#define IBO_SZ(i) groups[i].ibo_size

    IBO_SZ(0) = indices0.size() * sizeof(GLuint);
    IBO_SZ(1) = indices1.size() * sizeof(GLuint);
    IBO_SZ(2) = indices2.size() * sizeof(GLuint);

    if (!enableIBO())
        throw SKError(  ERR_INIT,
                        "models::sphere",
                        "",
                        "Could not enable IBO GLBuffer");

    if (!ibo.bind())
        throw SKError( ERR_INIT,
                       "models::sphere",
                       "",
                       "Could not bind IBO");

    ibo.allocate(IBO_SZ(0) + IBO_SZ(1) + IBO_SZ(2));
    ibo.write(0                    , indices0.constData(), IBO_SZ(0));
    ibo.write(IBO_SZ(0)            , indices1.constData(), IBO_SZ(1));
    ibo.write(IBO_SZ(0) + IBO_SZ(1), indices2.constData(), IBO_SZ(2));
    ibo.release();

}

models::GLSphere::GLSphere(GLuint slices, GLuint stacks)

    : GLModel(), slices(slices), stacks(stacks)
{

}

models::GLSphere::GLSphere(const GLSphere& init)

    : GLModel(init), slices(init.slices), stacks(init.stacks)
{

}
