#ifndef SYMSYSTEM_H
#define SYMSYSTEM_H

#include "actorgroup.h"
#include "specs/describable.h"
#include "specs/positionable.h"

class SymSystem : public ActorGroup, public Describable, public Positionable
{

    //offset autour du quel les particules evoluent
    SVector<3> offset;

public:

    /* Constructors */
    SymSystem(  Descriptor * desc = 0,
                const SVector<3> &offset = SVector<3>::nullv,
                const QString& label = "",
                specs_t flags = S_EVOLVE | S_RENDER | S_POSITION | S_DESCRIPTOR);

    SPECS_DESCRIPTOR

    virtual SVector<3> position() const override;

    SPECS_POSITION

    /* Manipulateur de l'offset */
    void setOffset(const SVector<3>&);

    const SVector<3>& getOffset() const;
};

#endif // SYMSYSTEM_H
