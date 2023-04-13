#include "interactingsystem.h"
#include "actors/particles/newtonparticle.h"

#include "graphtools.h"
#include "skerror.h"

using namespace symkit;

void InteractingSystem::attach(Particle * particle)
{
    if (!particle)
        throw SKError( ERR_NULL_POINTER,
                       "attach",
                       "InteractingSystem",
                       "Passing a null pointer as parameter");

    Evolvable * ev = dynamic_cast<Evolvable*>(particle);

    if (!ev)
        throw SKError( ERR_OTHERS,
                       "attach",
                       "InteractingSystem",
                       "Passing a non-evolvable parameter");

    ParticleSystem::attach(particle); //Ajoute la particule au système
}

/*
 * Two times update call, for each particle
 * updateForces then evolve
 */
void InteractingSystem::evolve(float dt)
{
    Evolvable * ev[2];

    /* Make particles interact each other */
    for (iterator iter_0 = begin(); iter_0 != end(); ++iter_0)
    {
        ev[0] = dynamic_cast<Evolvable*>(*iter_0);

        iterator iter_1 = iter_0;

        for (++iter_1; iter_1 != end(); ++iter_1)
       {
            ev[1] = dynamic_cast<Evolvable*>(*iter_1);

            if (ev[0]->isEvolving() && ev[1]->isEvolving())
            {
                ev[0]->evolve(dt);
                ev[1]->evolve(dt);
                interaction(*iter_0, *iter_1);
            }
        }
    }

    /* Call superclass method */
    ParticleSystem::evolve(dt);
}
