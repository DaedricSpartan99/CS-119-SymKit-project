#ifndef __DESCRIPTOR_H__
#define __DESCRIPTOR_H__

#include <iosfwd>

class Descriptor
{

public:

    // virtual destructor for abtract class
    virtual ~Descriptor() {}

    virtual void update(float) = 0;

    virtual void affiche(std::ostream&) const;
};

// ostream forward declaration
std::ostream& operator<<(std::ostream&, const Descriptor&);

#endif

