#include "marbled.h"

#include "models/glmarbled.h"

#include "graphtools.h"

using namespace symkit;

const color_s Marbled::color = { 0.1f, 0.5f, 0.2f, 1.0f };

Marbled::Marbled(models::GLMarbled * model)

    : Decoration(model, {0, -15, 0}, SVector<3>::nullv, 30)
{
    toggleFillMode();

    setColor(color);
}

Marbled::~Marbled()
{

}
