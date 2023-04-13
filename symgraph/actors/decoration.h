#ifndef DECORATION_H
#define DECORATION_H

#include "shape.h"
#include "specs/positionable.h"
#include "specs/orientable.h"
#include "specs/scalable.h"

/*
 * Basic abstract class for all decorations in the world
 * which are detached from any physics
 */

class Decoration : public Shape, public Positionable, public Orientable, public Scalable
{

public:

    /* Constructor and Desctructor */

    Decoration(     GLModel * model = 0,
                    const SVector<3> location = SVector<3>::nullv,
                    const SVector<3> angles = SVector<3>::nullv,
                    const double& scale = 1.0,
                    const QString& label = "",
                    specs_t flags = S_RENDER | S_FILL_MODE | S_POSITION | S_ORIENTATION | S_SCALING | S_COLOR);

    ~Decoration();

    /* returns the offset location */
    virtual SVector<3> position() const override;

    /* returns the angle orientation in the space (Euler angles) */
    virtual SVector<3> orientation() const override;

    /* returns the scaling proportion radius */
    virtual double scaling() const override;

    /* sets a new centre position */
    void setPosition(const SVector<3>& centre);

    /* sets the euler angles orientation in the space */
    void setOrientation(const SVector<3>& angles);

    void setScalingRatio(const double&);

    /* updates the centre position relatively to the old one */
    void move(const SVector<3>& delta);

    /* rotate from the euler angles */
    void rotate(const SVector<3>& delta);

    /* set a relative scaling */
    void scale(const double&);

    /* Generate specs methods */
    SPECS_POSITION

    SPECS_ORIENTATION

    SPECS_SCALING

private:

    SVector<3> location;
    SVector<3> angles; //pour l'orientation de l'objet

    double scalingRatio;
};

#endif // DECORATION_H
