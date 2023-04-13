#ifndef __SCENE_H__
#define __SCENE_H__

/*
 * This namespace manages all "low level"
 * rendering state and functions
 *
 * Idea: All graphical components 
 *       are contained in a "linked" list such that,
 *       for every frame and for each component 
 *       their "update" and "render" method are called.
 *
 *
 *
 */

#include <QGLWidget>
#include <QTime>
#include <list>
#include <set>
#include "graphtools.h"

#include "scenewrapper.h"

#include "timercontrol.h"

/* Forward declarations */
class SKActor;
class Camera;
class QGLShaderProgram;

class Renderable;
class Evolvable;
class Describable;

class KeyListener;
class MouseListener;

/* typedef for visibility, main typedef in glbuffer.h */
typedef GLuint texture_t;

/* Graphics scene manager */

class Scene : public QGLWidget, public SceneWrapper, public TimerControl
{
    /* QObject macro, it expands to thread safe QWidget functionalities */
    Q_OBJECT
    Q_INTERFACES(TimerControl)

public:
    
    /* Windows constructor */
    Scene(QWidget* parent = 0);

    /* Destructor */
    ~Scene();

    /* Key listeners binding */

    void addKeyListener(KeyListener *listener);

    void rmKeyListener(KeyListener *listener);

    /* Mouse listener binding */

    void addMouseListener(MouseListener *listener);

    void rmMouseListener(MouseListener *listener);

    /* Camera settings */
    Camera * getCamera();

    /* Timer functions */
    void pause();
    void resume();

    /* Delta time settings */
    void setDeltaTime(int delta_time);
    int getDeltaTime() const;

    /* Perspective angle */
    void setPerspectiveAngle(float angle);
    float getPerspectiveAngle() const;

    /* Screen informations */
    float resolution() const;
    int glWidth() const;
    int glHeight() const;

    /* Background color */
    void setClearColor(float r, float g, float b, float alpha = 1.0);

    void setClearColor(symkit::color_s);

    /* Bind/release QGLShaderProgram */

    void bindShaderProgram();
    void releaseShaderProgram();

    /*
     * Quit the program with an exit code
     * Alias to QApplication::exit(int)
     */
    static void exit(int code = 0);

    /* Load a texture */
    static texture_t loadTexture(const QString& filename);

    /* Constants, filename of the shaders to load */
    static const QString vertex_shader;
    static const QString fragment_shader;

    /* Constants, shaders attribute and uniform locations */
    static const QString attrib_vertex;
    static const QString attrib_color;
    static const char *  unif_projection;

    /* Timer management */

    void addTimerInitControl(TimerControl*);

    virtual QObject * getQObject() override;

signals:

    void canStart();

private slots:

    void canStartCallback();

protected:

    virtual void initialize() {}

    virtual void tickPlugin(float) {}

private:
    
    /* 
     * Overridden methods from QGLWidget 
     * They implement all OpenGL calls
     */
    virtual void initializeGL()                     override;
    virtual void resizeGL(int width, int height)    override;
    virtual void paintGL()                          override;

    /* Timer callback */
    virtual void timerEvent(QTimerEvent *event)     override;

    /* Event listening calls */

    virtual bool eventFilter(QObject *watched, QEvent *event) override;

    void checkEvents();

    /*
     * Timer initialization management
     */

    int timerControlCounter;

    void initTimer();

    /*
     * Event listening buffers
     */

    std::set<int> key_pressed;
    std::set<int> key_released;

    std::list<KeyListener*> keyListeners;

    std::list<symkit::mouse_s> mouse_pressed;
    std::list<symkit::mouse_s> mouse_released;
    std::list<symkit::mouse_s> mouse_moving;

    std::list<MouseListener*> mouseListeners;

    /* A camera instance to be used */
    Camera * camera;

    /* Shader manager for detailed colors and vertices settings */
    QGLShaderProgram * shaderProgram;

    /* Time management */
    int timerId;
    QTime timer;

    /* Default delta time settings in milliseconds */
    int delta_time;

    /* Window and view settings */
    float perspective_angle;

    /* variables where are read only screen informations */
    int width;
    int height;

    /* screen clear color RGBA format */
    symkit::color_s clearColor;

    /* Initialized flag */
    bool initialized;
};

#endif
