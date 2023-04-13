#define _USE_SVECTOR_OSTREAM

#include "alphascene.h"
#include <iostream>
#include "newtonsphere.h"
#include "pendule.h"
#include "marbled.h"
#include "ressor.h"
#include "pendulecoupl.h"
#include <QKeyEvent>
#include "skerror.h"

#include "models/glsphere.h"
#include "models/glmarbled.h"

using namespace std;
using namespace symkit;
using namespace models;

#include "camera.h"

#define DARK_BLUE 0.0f, 0.05f, 0.15f
#define BLUE_SKY 0.48f, 0.8f, 0.97f

AlphaScene::AlphaScene(QWidget *parent)

    : Scene(parent),
      KeyListener() // enabled
{
    sphereModel = new GLSphere();
    marbledModel = new GLMarbled();

    sphere = new NewtonSphere(sphereModel);

    pendule = new Pendule(sphereModel);
    ressor = new Ressor(sphereModel);
    pendulecoupl = new PenduleCoupl(sphereModel);

    marbled = new Marbled(marbledModel);

    /* Set the color of the sky */
    setClearColor(DARK_BLUE);

    try {

        /* Load shapes */
        addActor(sphere);
        addActor(pendule);
        addActor(marbled);
        addActor(ressor);
        addActor(pendulecoupl);

    } catch (const SKError& err) {

        cerr << err << endl;
    }

    /* Set a camera offset */
    getCamera()->move(50, Z);

    // register key events
    addKeyListener(this);
}

AlphaScene::~AlphaScene()
{
    delete sphere;
    delete marbled;
    delete pendule;
    delete ressor;
    delete pendulecoupl;

    delete sphereModel;
    delete marbledModel;
}

#include "assets.h"

void AlphaScene::initialize()
{
    sphereModel->initialize();
    marbledModel->initialize();
}

void AlphaScene::closeEvent(QCloseEvent*)
{
    /* Remove all shapes */
    this->removeAllActors();

    cout << "Closing OpenGL window" << endl;
}

#define T_UNIT 0.25
#define R_UNIT 2.5

void AlphaScene::onKeyPress(int key)
{
    switch(key)
    {

    case Qt::Key_W:
        getCamera()->move(-T_UNIT, Z);
        break;

    case Qt::Key_S:
        getCamera()->move(T_UNIT, Z);
        break;

    case Qt::Key_A:
        getCamera()->move(-T_UNIT, X);
        break;

    case Qt::Key_D:
        getCamera()->move(T_UNIT, X);
        break;

    case Qt::Key_K:
        getCamera()->move(T_UNIT, Y);
        break;

    case Qt::Key_J:
        getCamera()->move(-T_UNIT, Y);
        break;

    case Qt::Key_Up:
        getCamera()->rotate(-R_UNIT, X);
        break;

    case Qt::Key_Down:
        getCamera()->rotate(R_UNIT, X);
        break;

    case Qt::Key_Right:
        getCamera()->rotate(-R_UNIT, Y);
        break;

    case Qt::Key_Left:
        getCamera()->rotate(R_UNIT, Y);
        break;

    case Qt::Key_Space:
        // give the sphere an impulse
        sphere->applyRepulsion( getCamera() );
        break;

    case Qt::Key_P:
        // stop the sphere
        sphere->toggleEvolving();
        sphere->toggleRunningDescriptor();

        pendule->toggleEvolving();
        pendule->toggleRunningDescriptor();

        ressor->toggleEvolving();
        ressor->toggleRunningDescriptor();

        pendulecoupl->toggleEvolving();

        break;

    case Qt::Key_V:
        // set the sphere to verbose mode
        sphere->setVerbose( !sphere->getVerbose() );
        break;

    case Qt::Key_E:
        //Print coupled pendules energy
        cout << "System energy: " << pendulecoupl->energy() << endl;
        break;

    case Qt::Key_Escape:
        QWidget::close();
        break;

    default:
        break;
    }
}

void AlphaScene::onKeyRelease(int)
{

}
