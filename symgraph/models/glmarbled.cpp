#include "glmarbled.h"

#include "skerror.h"

using namespace symkit;

models::GLMarbled::GLMarbled(GLuint stacks)

    : GLModel(), stacks(stacks)
{

}

models::GLMarbled::GLMarbled(const GLMarbled& init)

    : GLModel(init), stacks(init.stacks)
{

}

void models::GLMarbled::initialize()
{
    GLGroup * group = registerGroup(GL_QUADS);

    QVector<GLfloat> vertices;

    vertices.reserve((stacks+1) * (stacks+1));

    QVector<GLuint> indices;

    for (GLuint i = 0; i <= stacks; ++i)
    {
        for (GLuint j = 0; j <= stacks; ++j)
            vertices << (GLfloat) i / stacks - 0.5
                        << 0
                        << (GLfloat) j / stacks - 0.5;
    }

    indices.reserve(4 * stacks * stacks);

    for (GLuint i = 0; i < stacks; ++i)
    {
        for (GLuint j = 0; j < stacks; ++j)
            indices << i * (stacks+1) + j
                    << i * (stacks+1) + j + 1
                    << (i+1) * (stacks+1) + j + 1
                    << (i+1) * (stacks+1) + j;
    }

    if (!enableVBO())
        throw SKError(  ERR_INIT,
                        "models::marbled",
                        "",
                        "Could not enable VBO GLBuffer");

    vbo_size = 3 * sizeof(GLfloat) * (stacks+1) * (stacks+1);

    vbo.bind();
    vbo.allocate(vertices.constData(), vbo_size);
    vbo.release();

    group->ibo_size = indices.size() * sizeof(GLuint);

    if (!enableIBO())
        throw SKError(  ERR_INIT,
                        "models::marbled",
                        "",
                        "Could not enable IBO GLBuffer");

    ibo.bind();
    ibo.allocate(group->ibo_size);
    ibo.write(0, indices.constData(), group->ibo_size);
    ibo.release();
}

