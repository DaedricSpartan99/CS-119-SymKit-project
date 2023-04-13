#ifndef SCENEWRAPPER_H
#define SCENEWRAPPER_H

#include <list>
#include "specs/evolvable.h"
#include "specs/renderable.h"

#include "specs/specs.h"

class SKActor;
class Describable;

class QMatrix4x4;
class QString;

class SceneWrapper : public Evolvable, public Renderable
{

    std::list<SKActor*> actors;
    std::list<Evolvable*> evolvables;
    std::list<Describable*> describables;
    std::list<Renderable*> renderables;

    void loadActorMatrix(Renderable*, QMatrix4x4&);

protected:

    void initializeActors();

public:

    /* take this class abstract */
    virtual ~SceneWrapper() {}

    virtual void evolve(float dt) override;

    virtual bool isEvolving() const override;

    virtual void render(symkit::render_s) override;

    virtual bool isRendering() const override;

    virtual bool isFillMode() const override;

    /* Iterator definition to loop through all SKActors */
    typedef std::list<SKActor*>::iterator iterator;
    typedef std::list<SKActor*>::const_iterator const_iterator;

    iterator begin();
    iterator end();

    const_iterator begin() const;
    const_iterator end() const;

    /* Add and remove SKActor functions */
    void    addActor(SKActor *);
    void    rmActor(SKActor *);

    /* Returns a list of actors that match the given label */
    std::list<SKActor*> findActorsByLabel(const QString&) const;

    void removeActorsByLabel(const QString&);

    void removeAllActors();
};

#endif
