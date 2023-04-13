#ifndef __ALPHA_SCENE_H__
#define __ALPHA_SCENE_H__

#include "scene.h"
#include "listeners/keylistener.h"

//Forward include
class NewtonSphere;
class Marbled;
class Pendule;
class Ressor;
class SKViewer;
class PenduleCouple;
class PenduleR;

class SKPlot2D;

namespace models
{
    class GLSphere;
    class GLMarbled;
}

class BetaScene : public Scene, KeyListener
{

public:

    /* Constructor and destructor */

    BetaScene(SKViewer * viewer, QWidget* parent = 0);

    ~BetaScene();

signals:

    void freezeScene(bool);

private:

    Q_OBJECT

    /* initialize in order to load sphere buffer */
    virtual void initialize() override;

    /* In order to update plotting */
    virtual void tickPlugin(float dt) override;

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

    /* The pendulecouple */

    //Exemple de d'oscillateur construit avec un constructeur complet, décommenter pour verifier son fonctionnement
    //PenduleCouple * penduleCouple2;

    PenduleCouple * penduleCouple;

    /* The penduleressort */

    PenduleR * penduleRessort;

    /* Models used */

    models::GLSphere * sphereModel;
    models::GLMarbled * marbledModel;

    /* Viewer class */
    SKViewer * viewer;

    bool freezed;
};

#endif
