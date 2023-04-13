#ifndef MARBLED_H
#define MARBLED_H

#include "actors/decoration.h"

namespace models
{
    class GLMarbled;
}

class Marbled : public Decoration
{
public:

    /* Constructor and destructor */
    Marbled(models::GLMarbled *);

    ~Marbled();

private:

    static const symkit::color_s color;
};

#endif // MARBLED_H
