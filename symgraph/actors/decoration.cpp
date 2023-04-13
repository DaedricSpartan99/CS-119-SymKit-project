#include "decoration.h"

Decoration::Decoration (GLModel * model,
                        const SVector<3> location,
                        const SVector<3> angles,
                        const double &scale,
                        const QString& label,
                        specs_t flags   )

    : Shape(model, label, flags), location(location), angles(angles), scalingRatio(scale)
{

}

Decoration::~Decoration()
{

}

/* returns the centre position */
SVector<3> Decoration::position() const
{
    return location;
}

SVector<3> Decoration::orientation() const
{
    return angles;
}

double Decoration::scaling() const
{
    return scalingRatio;
}

void Decoration::setPosition(const SVector<3>& location)
{
    this->location = location;
}

void Decoration::setOrientation(const SVector<3>& angles)
{
    this->angles = angles;
}

void Decoration::setScalingRatio(const double& scale)
{
    this->scalingRatio = scale;
}

void Decoration::move(const SVector<3>& delta)
{
    this->location += delta;
}

void Decoration::rotate(const SVector<3>& delta)
{
    this->angles += delta;
}

void Decoration::scale(const double& ratio)
{
    this->scalingRatio *= ratio;
}
