#include "specs/describable.h"
#include "descriptor.h"

#include <QString>

#include "skerror.h"

using namespace std;
using namespace symkit;

Describable::Describable(Descriptor *desc)

    : descriptor(desc)
{

}

Describable::~Describable()
{
    release();
}

void Describable::bind(Descriptor * desc)
{
    if (!desc)
        throw SKError(ERR_NULL_POINTER,
                      "bindDescriptor",
                      "symgraph.Descriptable",
                      "Cannot bind a null pointer as descriptor");

    descriptor = desc;
}

void Describable::release()
{
    descriptor = 0;
}

bool Describable::isBound() const
{
    return descriptor != 0;
}

Descriptor * Describable::getDescriptor()
{
    return this->descriptor;
}

const Descriptor * Describable::getDescriptor() const
{
    return descriptor;
}

//met à jour le Descriptor en fonction du pas de temps
void Describable::updateDescriptor(float dt)
{
    descriptor->update(dt);
}

#include <ostream>

ostream& operator<<(ostream& out, const Describable& d)
{
    out << *(d.getDescriptor());
    return out;
}

