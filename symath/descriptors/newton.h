#ifndef NEWTON_H
#define NEWTON_H

#include "descriptor.h"
#include "svector.h"

class NewtonDescriptor : public Descriptor
{
    /* Attributes */
    double mass;

    SVector<3> position;
    SVector<3> speed;

    SVector<3> forces;

public:

    /* Constructors and destractors */
    NewtonDescriptor(   const double& mass = 1.0,
                        const SVector<3>& position = SVector<3>::nullv,
                        const SVector<3>& speed = SVector<3>::nullv);

    NewtonDescriptor(const NewtonDescriptor&);

    ~NewtonDescriptor() {}

    virtual void update(float) override;

    /* Set and Get methods */

    double getMass() const;
    const SVector<3>& getPosition() const;
    const SVector<3>& getSpeed() const;
    const SVector<3>& getForces() const;

    void setMass(const double&);
    void setPosition(const SVector<3>&);
    void setSpeed(const SVector<3>&);
    void setForces(const SVector<3>&);

    /* operateurs pour ajouter ou annuller des forces sur la particule*/
    void operator+=(const SVector<3>&);
    void operator+(const SVector<3>&);
    void operator-=(const SVector<3>&);
    void operator-(const SVector<3>&);


    static const double sq_speed_zero;

};

#endif // NEWTON_H
