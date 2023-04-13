#include "particlesystem.h"
#include "actors/particle.h"

ParticleSystem::ParticleSystem(const SVector<3>& offset, const QString& label, specs_t flags)

    : SKActor(label, flags), offset(offset)
{

}

ParticleSystem::ParticleSystem(const std::initializer_list<Particle*>& init)

    : SKActor("", S_EVOLVE | S_RENDER | S_POSITION), particles(init)
{

}

void ParticleSystem::evolve(float dt)
{
    //Tout evolvable evolu, si il peut
    for (auto particle : particles)
    {
        Evolvable * ev = dynamic_cast<Evolvable*>(particle);

        if (ev && ev->isEvolving())
            ev->evolve(dt);
    }

    //tout descriptor est mise à jour
    for (auto particle : particles)
    {
        if (particle->isRunningDescriptor())
            particle->updateDescriptor(dt);
    }
}

ParticleSystem::iterator ParticleSystem::begin()
{
    return particles.begin();
}

ParticleSystem::iterator ParticleSystem::end()
{
    return particles.end();
}

ParticleSystem::const_iterator ParticleSystem::begin() const
{
    return particles.begin();
}

ParticleSystem::const_iterator ParticleSystem::end() const
{
    return particles.end();
}

void ParticleSystem::attach(Particle* actor)
{
    if (!actor)
    {
        ; // throw an error
    }

    particles.push_back(actor);
}

void ParticleSystem::detach(Particle* actor)
{
    if (!actor)
    {
        ; // throw an error
    }

    particles.remove(actor);
}

void ParticleSystem::detachAll()
{
    particles.clear();
}

SVector<3> ParticleSystem::position() const
{
   return offset;
}

void ParticleSystem::setOffset(const SVector<3>& offset)
{
    this->offset=offset;
}

// obtain static methods access
#include "graphtools.h"
#include "camera.h"
#include <QMatrix4x4>

#include "specs/scalable.h"
#include "specs/orientable.h"

void ParticleSystem::render(symkit::render_s args)
{
    /* Load position, scaling, color */

    QMatrix4x4 matrix;

    for (auto particle : particles)
    {
        if (particle->isRendering())
        {
            matrix.setToIdentity();

            symkit::loadActorPosition(particle, matrix);

            Orientable * orient = dynamic_cast<Orientable*>(particle);

            if (orient)
                symkit::loadActorOrientation(orient, matrix);

            Scalable * scal = dynamic_cast<Scalable*>(particle);

            if (scal)
                symkit::loadActorScaling(scal, matrix);

            args.camera->loadModelview(args.shaderProgram, args.matrix * matrix);

            symkit::loadActorPolygonMode(particle, args.polygonMode);

            symkit::loadActorColor(particle, args.shaderProgram);

            particle->render(args);
        }
    }

}
