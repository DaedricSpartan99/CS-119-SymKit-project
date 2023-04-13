#ifndef SKPLOT_H
#define SKPLOT_H

#include <QGLWidget>

#include "plotutils.h"

#include "timercontrol.h"

class QGLShaderProgram;

class SKPlot : public QGLWidget, public TimerControl
{
    Q_OBJECT
    Q_INTERFACES(TimerControl)

signals:

    void canStart();

public slots:

    void scheduleAxysUpdate();

public:

    SKPlot(float lineWidth = 1, QWidget * parent = 0);

    ~SKPlot();

    /* Axys management */

    void setAxysX(const SKAxys&);
    void setAxysY(const SKAxys&);


    const SKAxys& getAxysX() const;
    const SKAxys& getAxysY() const;

    /* Background handlers */

    void setBackgroundColor(const symkit::color_s&);
    const symkit::color_s& getBackgroundColor() const;

    /* Bind/release QGLShaderProgram */

    void bindShaderProgram();
    void releaseShaderProgram();

    /* Update graph */

    void updateGraph();

    /* Get closed state */

    bool isClosed() const;

    /* Axys scheduling informations */

    bool isAxysUpdateScheduled() const;

    /* Line width */

    void setLineWidth(float);
    float getLineWidth() const;

    /* Virtual events */

    virtual void mousePressEvent(QMouseEvent *event) override;

    virtual void closeEvent(QCloseEvent *) override;

    virtual QObject * getQObject() override;

protected:

    /* Choose paint mode */
    virtual void paintData(QGLShaderProgram*) = 0;

    virtual void paintAxys(QGLShaderProgram*) = 0;

    virtual void updateAxysRange();

    SKAxys& getAxysX();
    SKAxys& getAxysY();

private:

    virtual void initializeGL() override;

    virtual void paintGL() override;

    virtual void resizeGL(int, int) override;

    QGLShaderProgram * shaderProgram;

    symkit::color_s clearColor;

    SKAxys axys[2]; // X, Y

    bool initialized;
    bool closed;

    bool axysRangeUpdateScheduled;

    float lineWidth;

    /* Constants */

    static const QString vertex_shader;
    static const QString fragment_shader;

    static const QString attrib_vertex;
    static const QString attrib_color;
    static const char * unif_projection;
};

#endif // SKPLOT_H
