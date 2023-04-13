#include "skplot.h"

#include <QGLShaderProgram>
#include <iostream>
#include "skerror.h"

using namespace std;
using namespace symkit;

const QString SKPlot::vertex_shader = ":/plot_vertex_shader.glsl";
const QString SKPlot::fragment_shader = ":/plot_fragment_shader.glsl";

const QString SKPlot::attrib_vertex = "vertex";
const QString SKPlot::attrib_color = "color";

const char * SKPlot::unif_projection = "projection";

SKPlot::SKPlot(float lineWidth, QWidget * parent)

    : QGLWidget(parent),
      clearColor( color_s(0.9, 0.9, 0.9)),
      initialized(false),
      closed(true),
      axysRangeUpdateScheduled(false),
      lineWidth(lineWidth)
{
    shaderProgram = new QGLShaderProgram(context(), this);

    axys[0] = SKAxys(2, -1, color_s(0, 0, 1));
    axys[1] = SKAxys(2, -1, color_s(0, 1, 0));
}

SKPlot::~SKPlot()
{
    delete shaderProgram;
}

void SKPlot::setAxysX(const SKAxys& axys)
{
    this->axys[0] = axys;

    if (initialized)
        updateAxysRange();
}

void SKPlot::setAxysY(const SKAxys& axys)
{
    this->axys[1] = axys;

    if (initialized)
        updateAxysRange();
}

const SKAxys& SKPlot::getAxysX() const
{
    return axys[0];
}

const SKAxys& SKPlot::getAxysY() const
{
    return axys[1];
}

SKAxys& SKPlot::getAxysX()
{
    return axys[0];
}

SKAxys& SKPlot::getAxysY()
{
    return axys[1];
}

void SKPlot::setBackgroundColor(const color_s &color)
{
    if (initialized)
        glClearColor( COLOR_ARGS(color));

    clearColor = color;

}

const color_s& SKPlot::getBackgroundColor() const
{
    return clearColor;
}

void SKPlot::updateGraph()
{
    bindShaderProgram();

    updateGL();

    releaseShaderProgram();
}

void SKPlot::mousePressEvent(QMouseEvent *)
{
    setFocus();
}

void SKPlot::closeEvent(QCloseEvent *event)
{
    QGLWidget::closeEvent(event);

    closed = true;
}

bool SKPlot::isClosed() const
{
    return closed;
}

void SKPlot::initializeGL()
{
    cout << "Symplot: initializing OpenGL context" << endl;

    if (initialized)
    {
        cerr << SKError(  ERR_INIT,
                        "symplot.SKPlot",
                        "SKPlot::initializeGL(void)",
                        "Plotting window" + this->windowTitle().toStdString() + " already inizialized") << endl;

        exit(ERR_INIT);
    }

    this->initialized = true;
    this->closed = false;

    cout << "Symplot: OpenGL running in context " << context() << endl;

    glClearColor( COLOR_ARGS(clearColor));

    Q_INIT_RESOURCE(plot_shaders);

    cout << "Symplot: Loading vertex shader: " << vertex_shader.toStdString() << endl;
    if ( !shaderProgram->addShaderFromSourceFile(QGLShader::Vertex, vertex_shader) )
    {
        cerr << SKError(ERR_INIT, "symplot.SKPlot",
                        "SKPlot::initializeGL(void)",
                        "Failed loading vertex shader") << endl;

        exit(ERR_INIT);
    }

    cout << "Symplot: Loading fragment shader: " << fragment_shader.toStdString() << endl;
    if ( !shaderProgram->addShaderFromSourceFile(QGLShader::Fragment, fragment_shader) )
    {
        cerr << SKError(ERR_INIT, "symplot.SKPlot",
                        "SKPlot::initializeGL(void)",
                        "Failed loading fragment shader") << endl;

        exit(ERR_INIT);
    }

    shaderProgram->bindAttributeLocation(attrib_vertex, AttributeID::vertex);
    shaderProgram->bindAttributeLocation(attrib_color, AttributeID::color);

    cout << "Symplot: Linking shaders" << endl;

    if ( !shaderProgram->link() )
    {
        cerr << SKError( ERR_INIT,
                         "symplot.SKPlot",
                         "SKPlot::initializeGL(void)",
                         "Failed linking shaders, check for shaders existance") << endl;

        exit(ERR_INIT);
    }

    cout << "Symplot: shader program ID = " << shaderProgram->programId() << endl;
    cout << shaderProgram->log().toStdString() << endl;

    /* say to symgraph scene that it's ready to start */
    emit canStart();

    //cout << "Symplot: Binding shaders" << endl;
    //bindShaderProgram();

    //glEnable(GL_DEPTH_TEST);
    //glEnable(GL_CULL_FACE);

    glEnable(GL_LINE_SMOOTH);

    cout << "Symplot: line width " << lineWidth << endl;
    glLineWidth(lineWidth);

    /*
     * override this function and extend it
     * if a 3D environment is implemented
     */
}

void SKPlot::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT);
    // clear with background

    /* Manage range update */
    if (axysRangeUpdateScheduled)
    {
        updateAxysRange();
        axysRangeUpdateScheduled = false;
    }

    paintAxys(shaderProgram);
    paintData(shaderProgram);

    //glFlush();
}

void SKPlot::bindShaderProgram()
{
    if ( !shaderProgram->bind() )
    {
        cerr << SKError(  ERR_INIT,
                        "symplot.SKPlot",
                        "SKPlot::initializeGL(void)",
                        "Failed binding shader program, check for shaders compatibility") << endl;

            exit(ERR_INIT);
    }
}

void SKPlot::releaseShaderProgram()
{
    shaderProgram->release();
}


#include <QMatrix4x4>

void SKPlot::updateAxysRange()
{
    QMatrix4x4 matrix;

    cout << "Symplot: Setting ortho system, " << endl
        << "    Left: " << axys[0].offset << endl
        << "    Right: " << axys[0].offset + axys[0].range << endl
        << "    Bottom: " << axys[1].offset << endl
        << "    Up: " << axys[1].offset + axys[1].range << endl << endl;

    matrix.ortho(   axys[0].offset,
                    axys[0].offset + axys[0].range,
                    axys[1].offset,
                    axys[1].offset + axys[1].range,
                    -1.0f, 1.0f);

    //matrix.perspective(60, 1200.0 / 800, 1e-3f, 1e5f);
    shaderProgram->setUniformValue(unif_projection, matrix);
}


void SKPlot::resizeGL(int width, int height)
{
    cout << "Symplot: resize event, adapting viewport to: "
         << "(" << width << ", " << height << ")" << endl;

    bindShaderProgram();

    glViewport(0, 0, width, height);

    updateAxysRange();

    releaseShaderProgram();
}

QObject * SKPlot::getQObject()
{
    return this;
}

void SKPlot::scheduleAxysUpdate()
{
    axysRangeUpdateScheduled = true;
}

bool SKPlot::isAxysUpdateScheduled() const
{
    return axysRangeUpdateScheduled;
}

void SKPlot::setLineWidth(float width)
{
    if (initialized)
        glLineWidth(width);

    lineWidth = width;
}

float SKPlot::getLineWidth() const
{
    return lineWidth;
}
