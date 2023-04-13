#ifndef __SHAPE_H__
#define __SHAPE_H__

#include "svector.h"
#include "skactor.h"
#include "specs/renderable.h"
#include "specs/colorable.h"

/* basic object for a buffered rendering */

class GLModel;

/* 
 * Renderizable class
 * Every object inheriting Shape can be renderized by 
 * the Scene motor
 */
class Shape : public SKActor, public Renderable, public Colorable
{

public:

    /* Constructor and Destructor */
    Shape(  GLModel* model = 0,
            const QString &label = "",
            specs_t flags = S_RENDER | S_FILL_MODE | S_COLOR);

    virtual ~Shape() {}

    // set the graphical buffer
    void setGLModel(GLModel*);

    // returns the graphical buffer
    GLModel* getGLModel();

    /* graphical render function */
    virtual void render(symkit::render_s) override;

    virtual symkit::color_s color() const override;

    void setColor(symkit::color_s color);

    void setColor(float r, float g, float b, float alpha = 1.0);

    /* Generate specs render methods */
    SPECS_RENDER

    /* Generate fill mode settings methods */
    SPECS_FILL_MODE

    /* Generate color methods */
    SPECS_COLOR

private:

    /* OpenGL graphical components */

    GLModel * model;

    symkit::color_s renderColor;
};

#endif
