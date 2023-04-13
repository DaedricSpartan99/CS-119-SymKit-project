#include "scenewrapper.h"

#include "graphtools.h"
#include "skactor.h"
#include <QMatrix4x4>

#include "specs/describable.h"
#include "specs/colorable.h"

#include "specs/positionable.h"
#include "specs/orientable.h"
#include "specs/scalable.h"

#include "camera.h"

#include "skerror.h"
#include <iostream>

using namespace std;
using namespace symkit;

void SceneWrapper::loadActorMatrix(Renderable* actor, QMatrix4x4& matrix)
{
    Positionable * positionable = dynamic_cast<Positionable*>(actor);

    /* Translate world */
    if (positionable)
        symkit::loadActorPosition(positionable, matrix);

    Orientable * orientable = dynamic_cast<Orientable*>(actor);

    /* Rotate world */
    if (orientable)
        symkit::loadActorOrientation(orientable, matrix);

    Scalable * scalable = dynamic_cast<Scalable*>(actor);

    /* Scale world */
    if (scalable)
        symkit::loadActorScaling(scalable, matrix);
}

void SceneWrapper::initializeActors()
{
    try {

        /* Inizialize all actors */
        for (auto actor : actors)
            actor->initialize();

    } catch (const SKError &err) {

        cerr << "During initialization calls, " << endl;
        cerr << err << endl;

        if (err.fatal)
            exit(ERR_INIT);       // abort symulation
    }
}

void SceneWrapper::evolve(float dt)
{
    /* User updates all components */

    try {

        for (auto ev : evolvables)
        {
            /* Updating component */

            if (ev->isEvolving())
                ev->evolve(dt);
        }

    } catch (const SKError& err) {

        cerr << "During evolving calls, " << endl;
        cerr << err << endl;

        if (err.fatal)
            exit(ERR_EVOLVE);   // abort
    }

    /* Update all descriptors */

    try {

        for (auto desc : describables)
        {
            /*
             * Check wether description option is enabled
             * and then execute if bound
             */
            if (desc->isRunningDescriptor() && desc->isBound())
                desc->updateDescriptor(dt);
        }

    } catch (const SKError& err) {

        cerr << "During desctiptable calls, " << endl;
        cerr << err << endl;

        if (err.fatal)
            exit(ERR_EVOLVE);       // abort
    }
}

bool SceneWrapper::isEvolving() const
{
    return true;
}

void SceneWrapper::render(render_s args)
{
    QMatrix4x4 matrix;

    for (auto renderable : renderables)
    {
        /* Call  render function */
        if (renderable->isRendering())
        {
            matrix.setToIdentity();

            // load matrix
            loadActorMatrix(renderable, matrix);

            args.camera->loadModelview(args.shaderProgram, matrix * args.matrix);

            Colorable * colorable = dynamic_cast<Colorable*>(renderable);

            // load color
            if (colorable)
                symkit::loadActorColor(colorable, args.shaderProgram);

            // update polygon mode
            symkit::loadActorPolygonMode(renderable, args.polygonMode);

            try {

                // draw the renderable loaded model
                renderable->render(args.nextMatrix(matrix));

            } catch (const SKError& err) {

                cerr << "During rendering calls, " << endl;
                cerr << err << endl;

                if (err.fatal)
                    exit(ERR_RENDER);   // abort
            }
        }
    }
}

bool SceneWrapper::isRendering() const
{
    return true;
}

bool SceneWrapper::isFillMode() const
{
    return false;
}

SceneWrapper::iterator SceneWrapper::begin()
{
    return actors.begin();
}

SceneWrapper::iterator SceneWrapper::end()
{
    return actors.end();
}

SceneWrapper::const_iterator SceneWrapper::begin() const
{
    return actors.begin();
}

SceneWrapper::const_iterator SceneWrapper::end() const
{
    return actors.end();
}

void SceneWrapper::addActor(SKActor *actor)
{
    if (!actor)
        throw SKError( ERR_NULL_POINTER,
                       "symgraph.Scene",
                       "Scene::addActor(SKActor*)",
                       "Passing a null pointer as parameter",
                       false);

    actors.push_back(actor);

    /* Check for descriptable state */
    Describable * desc = dynamic_cast<Describable*>(actor);

    if (desc)
        describables.push_back(desc);

    Evolvable * ev = dynamic_cast<Evolvable*>(actor);

    if (ev)
        evolvables.push_back(ev);

    Renderable * rend = dynamic_cast<Renderable*>(actor);

    if (rend)
        renderables.push_back(rend);
}

void SceneWrapper::rmActor(SKActor *target)
{
    if (!target)
        throw SKError( ERR_NULL_POINTER,
                       "symgraph.Scene",
                       "Scene::rmActor(SKActor*)",
                       "Passing a null pointer as parameter",
                       false);

    actors.remove(target);

    /* Check for descriptable state */
    Describable * desc = dynamic_cast<Describable*>(target);

    if (desc)
        describables.remove(desc);

    Evolvable * ev = dynamic_cast<Evolvable*>(target);

    if (ev)
        evolvables.remove(ev);

    Renderable * rend = dynamic_cast<Renderable*>(target);

    if (rend)
        renderables.remove(rend);
}

list<SKActor*> SceneWrapper::findActorsByLabel(const QString& label) const
{
    list<SKActor*> actorsList;

    for (auto p : actors){

        if(p->getLabel()==label)
            actorsList.push_back(p);
    }

    return actorsList;
}

void SceneWrapper::removeActorsByLabel(const QString& label)
{
    iterator i = begin();

    list<SKActor*> rmlist;

    while (i != end())
    {
        if ((*i)->getLabel() == label)
            rmlist.push_back(*(i++));
    }

    for (auto act : rmlist)
        rmActor(act);

    rmlist.clear();
}

void SceneWrapper::removeAllActors()
{
    actors.clear();
    describables.clear();
    evolvables.clear();
    renderables.clear();
}
