#ifndef ACTORGROUP_H
#define ACTORGROUP_H

#include "scenewrapper.h"
#include "skactor.h"

class ActorGroup : public SKActor, public SceneWrapper
{

public:

    /* Constructor */
    ActorGroup(const QString& label = "", specs_t flags = S_EVOLVE | S_RENDER);

    SPECS_EVOLVE

    SPECS_RENDER
};

#endif // ACTORGROUP_H
