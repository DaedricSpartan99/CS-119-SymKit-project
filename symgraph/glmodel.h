#ifndef __GRAPHICS_BUFFER_H__
#define __GRAPHICS_BUFFER_H__

#include <QGLBuffer>
#include <vector>

struct GLGroup
{
    GLGroup(GLenum primitive = GL_TRIANGLES) : primitive(primitive), ibo_size(0) {}

    /* Render primitive type */
    GLenum primitive;

    /*
     * Memory allocated by the ibo
     * Each primitive type needs a certain number of vertices to
     * compose a geometrical face.
     *
     * POINTS       -> 1
     * LINES        -> 2
     * TRIANGLES    -> 3
     * QUADS        -> 4
     *
     * To better understand primitives: https://www.khronos.org/opengl/wiki/Primitive
     */
    GLuint ibo_size;
};

class QGLShaderProgram;

class GLModel
{

protected:

    /*
     * vbo := Vertex buffer object
     * ibo := Index buffer object
     *
     * The static rendering process is made to optimize/reduce the calls to the processor and
     * reduce drastically the memory occuped by a graphical object.
     *
     * A vbo is a list of all 3-dimensional coordinates in the space which correspond to
     * the vertices of the object to draw.
     * This list is not supposed to be ordered, but it's made to avoid repetitions on the coordinates.
     *
     * A ibo is a list which contains all the informations about how to combine all vertices
     * present in the vbo.
     * That information has a different format depending on the choise of the GLPrimitive.
     * In short it contains all indices combinations needed point to the right vertices in the
     * right order.
     *
     */
    QGLBuffer vbo, ibo;

    /* Virtual size of the vbo buffer (memsize) */
    GLuint vbo_size;

    /*
     * Array of groups which compose the ibo.
     * A ibo can be composed of a multitude of structures.
     * This parameter contains the information about the data structure
     * used to read/loop into the ibo.
     * (So an empty vector means an empty ibo too)
     */
    std::vector<GLGroup> groups;

public:

    /* Warning
     * Costructing an instance of this class will not allocate
     * any memory into the buffer.
     * In order to start allocating memory, call the
     * enable() methods first.
     */
    GLModel();

    GLModel(const GLModel&);

    GLModel& operator=(const GLModel&);

    /*
     * Initializer method
     */

    virtual void initialize() = 0;

    /*
     * Enable the buffer into the OpenGL
     * In case of failure, this method will return false,
     * otherwise it returns true.
     */

    bool enableVBO();

    bool enableIBO();

    void destroy();

    /*
     * Check for enabled status
     */

    bool isVBOEnabled() const;
    bool isIBOEnabled() const;

    /*
     * Destructor
     * Warning, destroying an instance of this struct
     * will deallocate the buffer memory
     */

    virtual ~GLModel();

    /*
     * Drawing function
     */

    void draw(QGLShaderProgram *);

    /*
     * Buffers accessors
     */

    QGLBuffer * vertexBuffer();
    QGLBuffer * indexBuffer();

    /* VBO size */

    void setVboSize(GLuint);

    GLuint vboSize() const;

    /*
     * Groups accessors and modifiers
     */

    void reserveGroups(std::size_t);

    GLGroup * registerGroup(GLenum type);

    std::vector<GLGroup*>& getGroupsByPrimitive(GLenum primitive, std::vector<GLGroup*>& buffer);

    void clearGroups();
};

#endif
