#include "glmodel.h"
#include <QGLShaderProgram>
#include "graphtools.h"

using namespace symkit;

GLModel::GLModel()

    : vbo(QGLBuffer::VertexBuffer), ibo(QGLBuffer::IndexBuffer)
{

}

GLModel::GLModel(const GLModel & init)
{
    *this = init;
}

GLModel& GLModel::operator=(const GLModel& cpy)
{
    vbo = cpy.vbo;
    ibo = cpy.ibo;
    vbo_size = cpy.vbo_size;
    groups = cpy.groups;

    return *this;
}

bool GLModel::enableVBO()
{
    return vbo.create();
}

bool GLModel::enableIBO()
{
    return ibo.create();
}

void GLModel::destroy()
{
    if (vbo.isCreated())
        vbo.destroy();

    if (ibo.isCreated())
        ibo.destroy();
}

bool GLModel::isVBOEnabled() const
{
    return vbo.isCreated();
}

bool GLModel::isIBOEnabled() const
{
    return ibo.isCreated();
}

GLModel::~GLModel()
{
    destroy();
}

#define _USE_MATH_DEFINES
#include <cmath>

#define BUFFER_OFFSET(a) ((char*)nullptr + (a))

#include "skerror.h"

using namespace symkit;

void GLModel::draw(QGLShaderProgram *shaderProgram)
{
    /* Draws the object */

    /* bind buffers */
    if (!vbo.bind())
        throw SKError(ERR_RENDER,
                      "draw",
                      "GLModel",
                      "Could not bind VBO");

    if (!ibo.bind())
        throw SKError(ERR_RENDER,
                      "draw",
                      "GLModel",
                      "Could not bind IBO");

    /*
     * enable GL_FLOAT formatting
     * set a ibo offset, ! qt magical memory workaround !
     */
    shaderProgram->setAttributeBuffer(AttributeID::vertex, GL_FLOAT, 0, 3);
    shaderProgram->enableAttributeArray(AttributeID::vertex);

    GLuint counter = 0;

    /* loop through GLGroups */
    for (auto group : groups)
    {
        /* Finally draw onto the graphics OpenGL engine */
        glDrawElements( group.primitive,
                        group.ibo_size / sizeof(GLuint),
                        GL_UNSIGNED_INT,
                        BUFFER_OFFSET(counter));

        /* Increase elements memory counter */
        counter += group.ibo_size;
    }

    /* Disable GL_FLOAT formatting */
    shaderProgram->disableAttributeArray(AttributeID::vertex);

    /* release buffers */
    ibo.release();
    vbo.release();
}

QGLBuffer * GLModel::vertexBuffer()
{
    return &vbo;
}

QGLBuffer * GLModel::indexBuffer()
{
    return &ibo;
}

void GLModel::setVboSize(GLuint size)
{
    vbo_size = size;
}

GLuint GLModel::vboSize() const
{
    return vbo_size;
}

void GLModel::reserveGroups(std::size_t n)
{
    groups.reserve(n);
}

GLGroup * GLModel::registerGroup(GLenum type)
{
    groups.push_back(GLGroup(type));

    return &groups.back();
}

using namespace std;

vector<GLGroup*>& GLModel::getGroupsByPrimitive(GLenum primitive, vector<GLGroup*>& buffer)
{
    for (auto& group : groups)
    {
        if (group.primitive == primitive)
            buffer.push_back(&group);
    }

    return buffer;
}

void GLModel::clearGroups()
{
    groups.clear();
}
