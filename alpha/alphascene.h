#ifndef __ALPHA_SCENE_H__
#define __ALPHA_SCENE_H__

#include "scene.h"
#include "listeners/keylistener.h"

//Forward include
class NewtonSphere;
class Marbled;
class Pendule;
class Ressor;
class PenduleCoupl;

namespace models
{
    class GLSphere;
    class GLMarbled;
}

class AlphaScene : public Scene, KeyListener
{

public:

    /* Constructor and destructor */

    AlphaScene(QWidget* parent = 0);

    ~AlphaScene();

private:

    /* initialize in order to load sphere buffer */
    virtual void initialize() override;

    /* Window close qt handler */
    virtual void closeEvent(QCloseEvent*) override;

    virtual void onKeyPress(int key) override;

    virtual void onKeyRelease(int key) override;

    /* A sphere object */
    NewtonSphere * sphere;

    /* The murbled plan */
    Marbled * marbled;

    /* The pendule */
    Pendule * pendule;

    /* The ressor */
    Ressor * ressor;

    /* The pendulecoupl */
    PenduleCoupl * pendulecoupl;

    models::GLSphere * sphereModel;
    models::GLMarbled * marbledModel;
};

#endif
