#include "descriptor.h"
#include <ostream>

using namespace std;

void Descriptor::affiche(std::ostream&) const{}

ostream& operator<<(ostream& out, const Descriptor& o)
{
    o.affiche(out);
    return out;
}
