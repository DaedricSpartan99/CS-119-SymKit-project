#include "symsystem.h"

SymSystem::SymSystem(Descriptor *desc, const SVector<3> & offset, const QString &label, specs_t flags)

    : ActorGroup(label, flags), Describable(desc), offset(offset)
{

}

SVector<3> SymSystem::position() const
{
    return offset;
}

void SymSystem::setOffset(const SVector<3>& offset)
{
    this->offset = offset;
}

const SVector<3>& SymSystem::getOffset() const
{
    return offset;
}
