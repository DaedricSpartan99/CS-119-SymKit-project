#define _USE_SVECTOR_OSTREAM

#include "betascene.h"
#include <iostream>
#include "newtonsphere/newtonsphere.h"
#include "pendules/pendule.h"
#include "marbled.h"
#include "ressort/ressor.h"
#include "pendcouple/pendcouple.h"
#include "pendressort/penduleressort.h"
#include <QKeyEvent>
#include "skerror.h"

#include "models/glsphere.h"
#include "models/glmarbled.h"

#include "skplot2d.h"

#include "skviewer.h"

#include "pendcouple/pendcouplepanel.h"
#include "pendules/pendulepanel.h"
#include "ressort/ressortpanel.h"
#include "pendressort/penduleressortpanel.h"

using namespace std;
using namespace symkit;
using namespace models;

#include "camera.h"

#define DARK_BLUE 0.0f, 0.05f, 0.15f
#define BLUE_SKY 0.48f, 0.8f, 0.97f

#ifndef M_PI
#define M_PI 3.141592654
#endif

BetaScene::BetaScene(SKViewer *viewer, QWidget *parent)

    : Scene(parent),
      KeyListener(),
      viewer(viewer),
      freezed(false)

{   //initialize les actors en créant simultanéement leurs descriptors (si ils en ont besoin)
    sphereModel = new GLSphere();
    marbledModel = new GLMarbled();

    sphere = new NewtonSphere(sphereModel);

    pendule = new Pendule(sphereModel, {7, 0, 0}, "Pendule simple");
    ressor = new Ressor(sphereModel, {-3, 0, 5});

    penduleCouple = new PenduleCouple(sphereModel, {0, 1, 0}, "Pendule couple");
    penduleRessort = new PenduleR(sphereModel, {-10, 7, 8});
    //Exemple d'oscillateur construit avec un constructeur complet, décommenter pour verifier son fonctionnement
    //penduleCouple2 = new PenduleCouple(sphereModel, {M_PI, M_PI / 2}, {0, 0}, 10, 5, 2, 2);

    marbled = new Marbled(marbledModel);

    /* add phasespace to timer init control stack */
    //addTimerInitControl(penduleCouple->getPhaseSpace()->getPlot());

    /* Set the color of the sky */
    setClearColor(DARK_BLUE);

    try {

        /* Load shapes */
        addActor(sphere);
        addActor(pendule);
        addActor(marbled);
        addActor(ressor);
        //Exemple d'oscillateur construit avec un constructeur complet, décommenter pour verifier son fonctionnement
        //addActor(penduleCouple2);
        addActor(penduleCouple);
        addActor(penduleRessort);

    } catch (const SKError& err) {

        cerr << err << endl;
    }

    /* Set a camera offset */
    getCamera()->move(10, Z);

    // register key events
    addKeyListener(this);

    if (viewer)
    {
        /* Panels setup */
        viewer->addViewerPanel(pendule->getPanel());
        viewer->addViewerPanel(ressor->getPanel());
        viewer->addViewerPanel(penduleCouple->getViewer());
        viewer->addViewerPanel(penduleRessort->getPanel());

        connect(this, SIGNAL(freezeScene(bool)), pendule->getPanel(), SLOT(setDescribingState(bool)));
        connect(this, SIGNAL(freezeScene(bool)), ressor->getPanel(), SLOT(setDescribingState(bool)));
        connect(this, SIGNAL(freezeScene(bool)), penduleCouple->getViewer(), SLOT(setDescribingState(bool)));
        connect(this, SIGNAL(freezeScene(bool)), penduleRessort->getPanel(), SLOT(setDescribingState(bool)));

        connect(this, SIGNAL(freezeScene(bool)), pendule->getPanel(), SLOT(setEvolvingState(bool)));
        connect(this, SIGNAL(freezeScene(bool)), ressor->getPanel(), SLOT(setEvolvingState(bool)));
        connect(this, SIGNAL(freezeScene(bool)), penduleCouple->getViewer(), SLOT(setEvolvingState(bool)));
        connect(this, SIGNAL(freezeScene(bool)), penduleRessort->getPanel(), SLOT(setEvolvingState(bool)));
    }
}

BetaScene::~BetaScene()
{
    delete sphere;
    delete marbled;
    delete pendule;
    delete ressor;
    //Exemple d'oscillateur construit avec un constructeur complet, décommenter pour verifier son fonctionnement
    delete penduleCouple;
    delete penduleRessort;

    delete sphereModel;
    delete marbledModel;
}

#include "assets.h"

void BetaScene::initialize()
{
    sphereModel->initialize();
    marbledModel->initialize();
}

#include "pendcouple/penduledesc.h"

void BetaScene::tickPlugin(float)
{
    if (viewer && viewer->isEnabled())
    {
        viewer->updatePanels();
    }
}

void BetaScene::closeEvent(QCloseEvent*)
{
    /* Remove all shapes */
    this->removeAllActors();

    cout << "Closing OpenGL window" << endl;
}

#define T_UNIT 0.25
#define R_UNIT 2.5

void BetaScene::onKeyPress(int key)
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
        // stop the particles

        sphere->toggleEvolving();
        sphere->toggleRunningDescriptor();

        pendule->toggleEvolving();
        pendule->toggleRunningDescriptor();

        ressor->toggleEvolving();
        ressor->toggleRunningDescriptor();

        /* décommenter si l'on veut tester cet oscillateur
        penduleCouple2->toggleEvolving();
        penduleCouple2->toggleRunningDescriptor();
        */

        penduleCouple->toggleEvolving();
        penduleCouple->toggleRunningDescriptor();

        penduleRessort->toggleEvolving();
        penduleRessort->toggleRunningDescriptor();

        emit freezeScene(freezed);
        freezed = !freezed;

        break;

    case Qt::Key_V:
        // set the sphere to verbose mode
        sphere->setVerbose( !sphere->getVerbose() );
        break;

    //Pour le debugging (contrôler si le comportement est sensé)
    case Qt::Key_E:
        cout << "Pendule coupled first system energy: " << penduleRessort->energy() << endl;
        break;

    /* décommenter si l'on veut tester cet oscillateur
    case Qt::Key_F:
        cout << "Pendule coupled second system energy: " << penduleCouple2->energy() << endl;
        break;
     */

    case Qt::Key_1:
        cout << "Pendule Simple" << endl;
        cout << *pendule << endl;
        break;

    case Qt::Key_2:
        cout << "Ressort" << endl;
        cout << *ressor << endl;
        break;

    case Qt::Key_3:
        cout << "Pendule Charriot" << endl;
        cout << *penduleRessort << endl;
        break;

    case Qt::Key_4:
        cout << "Pendule Couple" << endl;
        cout << *penduleCouple << endl;
        break; 

    /* décommenter si l'on veut tester cet oscillateur
    case Qt::Key_6:
        cout << "Pendule Couple 2" << endl;
        cout << *penduleCouple2 << endl;
        break;
    */

    case Qt::Key_Escape:
        exit(0);
        break;


    default:
        break;
    }
}

void BetaScene::onKeyRelease(int)
{

}
