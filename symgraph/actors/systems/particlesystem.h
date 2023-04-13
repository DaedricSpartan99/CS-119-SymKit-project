#ifndef ABSTRACTSYSTEM_H
#define ABSTRACTSYSTEM_H

#include "skactor.h"
#include "specs/evolvable.h"
#include "specs/renderable.h"
#include "specs/positionable.h"

#include <list>

class Particle;

class ParticleSystem : public SKActor, public Evolvable, public Renderable, public Positionable
{
public:

    /* Constructors */

    ParticleSystem( const SVector<3>& offset = {0,0,0},
                    const QString& label = "",
                    specs_t flags = S_EVOLVE | S_RENDER | S_POSITION);

    ParticleSystem(const std::initializer_list<Particle*>&);

    virtual void evolve(float) override;

    SPECS_EVOLVE

    SPECS_RENDER

    /* A system doesn't implement a fill mode */
    virtual bool isFillMode() const override
    {
        return true;
    }

    /* Generate Positioning methods */
    SPECS_POSITION

    virtual SVector<3> position() const override;

    void setOffset(const SVector<3>&);

    /* Loop through the system components */

    typedef std::list<Particle*>::iterator iterator;
    typedef std::list<Particle*>::const_iterator const_iterator;

    iterator begin();
    iterator end();

    const_iterator begin() const;
    const_iterator end() const;

    /* Add/remove components */

    virtual void attach(Particle*);
    virtual void detach(Particle*);

    void detachAll();

    virtual void render(symkit::render_s) override;

private:

    //offset autour du quel les particules evoluent
    SVector<3> offset;

    //la liste de particules
    std::list<Particle*> particles;
};

#endif // ABSTRACTSYSTEM_H
