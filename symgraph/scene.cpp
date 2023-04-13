#include "scene.h"

#include "skactor.h"
#include "specs/evolvable.h"
#include "specs/colorable.h"
#include "specs/orientable.h"
#include "specs/positionable.h"
#include "specs/renderable.h"
#include "specs/scalable.h"
#include "specs/describable.h"
#include "skerror.h"

#include "listeners/keylistener.h"
#include "listeners/mouselistener.h"

#include "camera.h"

/* includes from Qt library */
#include <QGLShaderProgram>
#include <QMatrix4x4>

#include <QKeyEvent>

#include <QApplication> // QApplication::exit(int)
#include <iostream> // std::cerr

#include "graphtools.h"

using namespace std;
using namespace symkit;

const QString Scene::vertex_shader = ":/vertex_shader.glsl";
const QString Scene::fragment_shader = ":/fragment_shader.glsl";

const QString Scene::attrib_vertex = "vertex";
const QString Scene::attrib_color = "color";
const char *  Scene::unif_projection = "projection";

/* Scene class implementation */

Scene::Scene(QWidget *parent) : QGLWidget(parent),

    timerControlCounter(0),
    camera( new Camera() ),
    timerId(0),
    delta_time(17),
    perspective_angle(70.0),
    width(0),
    height(0),
    clearColor{0.0, 0.0, 0.0, 1.0},  // black
    initialized(false)
{
    shaderProgram = new QGLShaderProgram(context(), this);
    // catch events
    this->installEventFilter(this);

    addTimerInitControl(this);

    /* Set the cursor a cross */
    //QCursor::setShape(Qt::CrossCursor);
}

Scene::~Scene()
{
    /* Class destruction */

    /* Camera destruction */
    delete camera;

    /* Shader program destruction */
    delete shaderProgram;
}

void Scene::initializeGL()
{
    cout << "Symgraph: initializing OpenGL context" << endl;

    if (initialized)
    {
        cerr << SKError(  ERR_INIT,
                        "symgraph.Scene",
                        "Scene::initializeGL(void)",
                        "Scene " + this->windowTitle().toStdString() + " already inizialized") << endl;

        exit(ERR_INIT);
    }

    /* Allow actions on openGL components */
    this->initialized = true;

    cout << "Symgraph: OpenGL running in context " << context() << endl;

    /* load set clear color, COLOR_ARGS is defined in "colorable.h" */
    glClearColor( COLOR_ARGS(clearColor) );

    Q_INIT_RESOURCE(shaders);

    cout << "Symgraph: Loading vertex shader: " << vertex_shader.toStdString() << endl;
    shaderProgram->addShaderFromSourceFile(QGLShader::Vertex, vertex_shader);
    cout << "Symgraph: Loading fragment shader: " << fragment_shader.toStdString() << endl;
    shaderProgram->addShaderFromSourceFile(QGLShader::Fragment, fragment_shader);

    shaderProgram->bindAttributeLocation(attrib_vertex, AttributeID::vertex);
    shaderProgram->bindAttributeLocation(attrib_color, AttributeID::color);

    cout << "Symgraph: Linking shaders" << endl;

    // build the shader
    if ( !shaderProgram->link() )
    {
        cerr << SKError(  ERR_INIT,
                        "symgraph.Scene",
                        "Scene::initializeGL(void)",
                        "Failed linking shaders, check for shaders existance") << endl;

        exit(ERR_INIT);
    }

    cout << "Symgraph: Binding shaders" << endl;

    // activate the shader
    bindShaderProgram();

    cout << "Symgraph: Initializing actors" << endl;

    try {

        initialize();

        initializeActors();

    } catch (const SKError &err) {

        cerr << "During initialization calls, " << endl;
        cerr << err << endl;

        if (err.fatal)
            exit(ERR_INIT);       // abort symulation
    }

    /* Enable superposition control for graphical objects */
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_CULL_FACE);

    /* say it's ready to start */
    emit canStart();

    // release Shader Program
    releaseShaderProgram();

    cout << "Symgraph: shader program ID = " << shaderProgram->programId() << endl;
    cout << shaderProgram->log().toStdString() << endl;
}

void Scene::initTimer()
{
    cout << "Symgraph: setting up tick timer" << endl;

    timerId = startTimer(this->delta_time);

    if (!timerId)
    {
        cerr << SKError(  ERR_INIT,
                        "symgraph.Scene",
                        "Scene::initializeGL(void)",
                        "Failed starting the symulation timer") << endl;

        timerId = startTimer(this->delta_time);

        if (!timerId)   // retry
            exit(ERR_INIT);
    }
}

void Scene::resizeGL(int width, int height)
{
    /* Set fields */
    this->width = width;
    this->height = height;

    bindShaderProgram();

    /* Update window viewport */
    glViewport(0, 0, width, height);    

    QMatrix4x4 matrix;

    /* Update perspective function */
    matrix.perspective(this->perspective_angle, this->resolution(), 1e-3f, 1e5f);

    /* Load the matrix to the shader */
    shaderProgram->setUniformValue(unif_projection, matrix);

    releaseShaderProgram();
}

void Scene::paintGL()
{
    /* clear screen */
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    /* Render iter */
    QMatrix4x4 matrix;

    bool polygonMode(true);

    /*
     * render_s program iter initialization
     */
    render_s args = { shaderProgram, camera, matrix, polygonMode };

    /* default polygon mode */
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    /* Render all components */

    SceneWrapper::render(args);
}

void Scene::checkEvents()
{
    // bind key listeners calls
    for (auto listener : keyListeners)
    {
        if (!listener->isKeyListenerEnabled())
            continue;

        for (auto pressed : key_pressed)
            listener->onKeyPress(pressed);

        for (auto released : key_released)
            listener->onKeyRelease(released);
    }

    // clear key released buffer
    key_released.clear();

    for (auto listener : mouseListeners)
    {
        if (!listener->isMouseListenerEnabled())
            continue;

        for (auto clicked : mouse_pressed)
            listener->onMouseClick(clicked);

        for (auto released : mouse_released)
            listener->onMouseRelease(released);

        for (auto moved : mouse_moving)
            listener->onMouseMove(moved);
    }

    // clear mouse buffers
    mouse_released.clear();
    mouse_moving.clear();
}

void Scene::timerEvent(QTimerEvent*)
{
    /* establish the correct delta time */
    float dt = timer.restart() / 1000.0f;

    /* check for events, keyboard or mouse */
    checkEvents();

    /* update all shapes */
    evolve(dt);

    // bind openGL context
    bindShaderProgram();

    /* update graphics engine */
    updateGL();

    // release current context
    releaseShaderProgram();

    /*
     * Eventually perform other actions by the
     * inherited classes
     */
    tickPlugin(dt);
}

bool Scene::eventFilter(QObject *, QEvent *event)
{
    QKeyEvent * keyevent = dynamic_cast<QKeyEvent*>(event);
    QMouseEvent * mouse_event = dynamic_cast<QMouseEvent*>(event);

    if (keyevent)
    {
        int key = keyevent->key();

        if (event->type() == QEvent::KeyPress)
            key_pressed.insert(key);

        if (event->type() == QEvent::KeyRelease)
        {
            key_pressed.erase(key);
            key_released.insert(key);
        }

    } else if (mouse_event) {

        mouse_s args (mouse_event->globalX(), mouse_event->globalY(), camera, mouse_event->button());

        if (event->type() == QEvent::MouseButtonPress)
            mouse_pressed.push_back(args);

        if (event->type() == QEvent::MouseButtonRelease)
        {
            mouse_pressed.remove(args);
            mouse_released.push_back(args);
        }

        if (event->type() == QEvent::MouseMove)
            mouse_moving.push_back(args);
    }

    return false; // continue filtering
}

void Scene::addKeyListener(KeyListener *listener)
{
    if (!listener)
        throw SKError( ERR_NULL_POINTER,
                       "symgraph.Scene",
                       "Scene::addKeyListener(KeyListener*)",
                       "Passing a null pointer as parameter",
                       false);

    keyListeners.push_back(listener);
}

void Scene::rmKeyListener(KeyListener *listener)
{
    if (!listener)
        throw SKError( ERR_NULL_POINTER,
                       "symgraph.Scene",
                       "Scene::rmKeyListener(KeyListener*)",
                       "Passing a null pointer as parameter",
                       false);

    keyListeners.remove(listener);
}

void Scene::addMouseListener(MouseListener *listener)
{
    if (!listener)
        throw SKError( ERR_NULL_POINTER,
                       "symgraph.Scene",
                       "Scene::addMouseListener(KeyListener*)",
                       "Passing a null pointer as parameter",
                       false);

    mouseListeners.push_back(listener);
}

void Scene::rmMouseListener(MouseListener *listener)
{
    if (!listener)
        throw SKError( ERR_NULL_POINTER,
                       "symgraph.Scene",
                       "Scene::rmMouseListener(KeyListener*)",
                       "Passing a null pointer as parameter",
                       false);

    mouseListeners.remove(listener);
}

Camera * Scene::getCamera()
{
    return this->camera;
}

void Scene::pause()
{
    if (timerId != 0)
    {
        killTimer(timerId);
        timerId = 0;
}   }

void Scene::resume()
{
    if (timerId == 0)
    {
        timerId = startTimer(delta_time);

        if (!timerId)
        {
            cerr << SKError( ERR_OTHERS,
                           "symgraph.Scene",
                           "Scene::resume(void)",
                           "Cannot the restart the timer") << endl;

            timerId = startTimer(delta_time); // retry

            if (!timerId)
                exit(ERR_OTHERS);
        }

        timer.restart();
    }
}

void Scene::setDeltaTime(int delta_time)
{
    if (delta_time <= 0)
        throw SKError( ERR_NUMERICAL,
                       "symgraph.Scene",
                       "Scene::setDeltaTime(int)",
                       "Cannot set a null or negative delta time");

    this->delta_time = delta_time;
}

int Scene::getDeltaTime() const
{
    return delta_time;
}

void Scene::setPerspectiveAngle(float angle)
{
    if (angle > 0 && angle < 90.0)
        perspective_angle = angle;
    else
        throw SKError( ERR_NUMERICAL,
                       "symgraph.Scene",
                       "Scene::setPerspectiveAngle(float)",
                       "Angle value must be bound between 0 and 90.0 degrees");
}

float Scene::getPerspectiveAngle() const
{
    return this->perspective_angle;
}

float Scene::resolution() const
{
    return float(width) / float( (height != 0) ? height : 1.0 );
}

int Scene::glWidth() const
{
    return width;
}

int Scene::glHeight() const
{
    return height;
}

void Scene::setClearColor(float r, float g, float b, float alpha)
{
    color_s color = {r, g, b, alpha};

    setClearColor(color);
}

void Scene::setClearColor(color_s color)
{
    if (initialized)
        glClearColor( COLOR_ARGS(color) );

    clearColor = color;
}

void Scene::bindShaderProgram()
{
    if ( !shaderProgram->bind() )
    {
        cerr << SKError(  ERR_INIT,
                        "symgraph.Scene",
                        "Scene::initializeGL(void)",
                        "Failed binding shader program, check for shaders compatibility") << endl;

        exit(ERR_INIT);
    }
}

void Scene::releaseShaderProgram()
{
    shaderProgram->release();
}

void Scene::exit(int code)
{
    QApplication::exit(code);
}

void Scene::addTimerInitControl(TimerControl *control)
{
    ++timerControlCounter;

    connect(control->getQObject(), SIGNAL(canStart()), this, SLOT(canStartCallback()));
}

void Scene::canStartCallback()
{
    --timerControlCounter;

    if (timerControlCounter == 0)
        initTimer();
}

QObject * Scene::getQObject()
{
    return this;
}

/* Warning, this method is detached from a scene object */
texture_t Scene::loadTexture(const QString& filename)
{
    texture_t tex;

    QGLContext* context =  const_cast<QGLContext*>(QGLContext::currentContext());
    tex = context->bindTexture(QPixmap(filename), GL_TEXTURE_2D);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);

    return tex;
}
