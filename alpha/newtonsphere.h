#ifndef NEWTON_SPHERE_H
#define NEWTON_SPHERE_H

#include "actors/particles/newtonparticle.h"

class Camera;

namespace models
{
    class GLSphere;
}

class NewtonSphere : public NewtonParticle
{

public:

    NewtonSphere(models::GLSphere *);

    virtual void evolve(float dt) override;

    // adds on
    virtual void render(symkit::render_s) override;

    void setVerbose(bool value);

    bool getVerbose() const;

    void applyRepulsion(const Camera*);

private:

    /* Constants */

    static const double K;

    static const double pendule_l;

    static const SVector<3> gravity;

    static const double friction;

    static const double mass;

    static const SVector<3> init_position;

    static const SVector<3> init_speed;

    static const NewtonDescriptor init_desc;

    /* Verbose option */

    bool verbose;

    unsigned long int counter;
};

#include <iosfwd>
std::ostream& operator<<(std::ostream&, const NewtonSphere&);

#endif // SPHERE_H
