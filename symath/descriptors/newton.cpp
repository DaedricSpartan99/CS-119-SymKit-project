#include "newton.h"
#include "integrators.h"

using namespace symkit;

NewtonDescriptor::NewtonDescriptor(const NewtonDescriptor& desc)
{
    *this = desc;
}

NewtonDescriptor::NewtonDescriptor(const double &mass, const SVector<3> &position, const SVector<3> &speed)

    : mass(mass), position(position), speed(speed), forces(SVector<3>::nullv)
{

}

const double NewtonDescriptor::sq_speed_zero = 1.0e-6;

void NewtonDescriptor::update(float dt)
{
    integrateEulerCromer<SVector<3>>(position, speed, forces / mass, dt);

    if (speed > 0 && speed <= sq_speed_zero)
        speed.null();

    forces.null();
}

double NewtonDescriptor::getMass() const
{
    return mass;
}

const SVector<3>& NewtonDescriptor::getPosition() const
{
    return position;
}

const SVector<3>& NewtonDescriptor::getSpeed() const
{
    return speed;
}

const SVector<3>& NewtonDescriptor::getForces() const
{
    return forces;
}

void NewtonDescriptor::setMass(const double& mass)
{
    this->mass = mass;
}

void NewtonDescriptor::setPosition(const SVector<3>& position)
{
    this->position = position;
}

void NewtonDescriptor::setSpeed(const SVector<3>& speed)
{
    this->speed = speed;
}

void NewtonDescriptor::setForces(const SVector<3>& forces)
{
    this->forces = forces;
}

void NewtonDescriptor::operator+=(const SVector<3>& v)
{
    forces += v;
}

void NewtonDescriptor::operator+(const SVector<3>& v)
{
    (*this) += v;
}
void NewtonDescriptor::operator-=(const SVector<3>& v)
{
    forces -= v;
}
void NewtonDescriptor::operator-(const SVector<3>& v)
{
    (*this) -= v;
}
