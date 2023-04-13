#include "penduledesc.h"

#include <cmath>

PenduleDesc::PenduleDesc(double l1, double l2, double m1, double m2,
                         const Vector &p, const Vector &pp, double g)
    : Oscillateur(p, pp), g(g)
{
    l[0] = l1;
    l[1] = l2;

    m[0] = m1;
    m[1] = m2;

    //corriger dimension position et vitesse
    adjust(2);
}

PenduleDesc::PenduleDesc(double l1, double l2, double m1, double m2,
                         const std::vector<double> &p, const std::vector<double> &pp, double g)
    : Oscillateur(p, pp), g(g)
{
    l[0] = l1;
    l[1] = l2;

    m[0] = m1;
    m[1] = m2;

    //corriger dimension position et vitesse
    adjust(2);
}

#define CHECK_BOUND_INDEX(index) index < 2 && index >= 0

#include "skerror.h"

using namespace symkit;


//SKerror pour lancer des erreurs en cas de valeurs physiquement incohèrente... et autre

void PenduleDesc::setLength(double l, int index)
{
    if (l<=0)
        throw SKError(ERR_NUMERICAL, "setLenght", "PenduleDesc", "trying to set to an incoherent value", false);
    if (CHECK_BOUND_INDEX(index))
        this->l[index] = l;
    else
        throw SKError(ERR_BOUND, "setLength", "PenduleDesc", "Looking for a non-existing memory-buffer", false);

}

void PenduleDesc::setMass(double m, int index)
{
    if (m<=0)
        throw SKError(ERR_NUMERICAL, "setMass", "PenduleRessort", "trying to set to an incoherent value", false);
    if (CHECK_BOUND_INDEX(index))
        this->m[index] = m;
    else
        throw SKError(ERR_BOUND, "setMass", "PenduleDesc", "Looking for a non-existing memory-buffer", false);
}

double PenduleDesc::getLength(int index) const
{
    if (CHECK_BOUND_INDEX(index))
        return l[index];
    else
        throw SKError(ERR_BOUND, "getLength", "PenduleDesc", "Looking for a non-existing value", false);
}

double PenduleDesc::getMass(int index) const
{
    if (CHECK_BOUND_INDEX(index))
        return m[index];
    else
        throw SKError(ERR_BOUND, "getMass", "PenduleDesc", "Looking for a non-existing value", false);
}

double PenduleDesc::getAngle(int index) const
{
    if (CHECK_BOUND_INDEX(index))
        return getp()[index];
    else
        throw SKError(ERR_BOUND, "getAngle", "PenduleDesc", "Looking for a non-existing value", false);
}

double PenduleDesc::getAngularSpeed(int index) const
{
    if (CHECK_BOUND_INDEX(index))
        return getp_prime()[index];
    else
        throw SKError(ERR_BOUND, "getAngularSpeed", "PenduleDesc", "Looking for a non-existing value", false);
}

double PenduleDesc::getGravity() const
{
    return g;
}

double PenduleDesc::kineticEnergy(int index) const
{
    double out(0);

    if (CHECK_BOUND_INDEX(index))
    {
        if (index == 0)
            out = 0.5 * m[0] * l[0] * l[0] * p_prime[0] * p_prime[0];
        else {

            out += l[0]*l[0]*p_prime[0]*p_prime[0];
            out += l[1]*l[1]*p_prime[1]*p_prime[1];
            out += 2*l[0]*l[1]*p_prime[0]*p_prime[1]*cos(p[0]-p[1]);

            out *= 0.5 * m[1];
        }

    } else
        throw SKError(ERR_BOUND, "kineticEnergy", "PenduleDesc", "Looking for a non-existing value", false);

    return out;
}

#include <cmath>

Vector PenduleDesc::equation() const
{
    Vector out = {0, 0};

    double dteta =  p[0] - p[1];
    double M = m[0] + m[1];
    double sin_dteta = sin(dteta);
    double cos_dteta = cos(dteta);
    double denom = m[0] + m[1] * sin_dteta * sin_dteta;

    // first angle
    out[0] = m[1] * g * cos_dteta * sin(p[1])
                - M * g * sin(p[0])
                - m[1] * l[0] * p_prime[0] * p_prime[0] * sin_dteta * cos_dteta
                - m[1] * l[1] * p_prime[1] * p_prime[1] * sin_dteta;

    out[0] /= denom * l[0];

    // second angle
    out[1] = M * g * cos_dteta * sin(p[0])
                - M * g * sin(p[1])
                + m[1] * l[1] * p_prime[1] * p_prime[1] * sin_dteta * cos_dteta
                + M * l[0] * p_prime[0] * p_prime[0] * sin_dteta;

    out[1] /= denom * l[1];

    return out;
}

void PenduleDesc::setAngle(double l, int index)
{
    if (CHECK_BOUND_INDEX(index))
        p[index] = l;
}

void PenduleDesc::setAngularSpeed(double l, int index)
{
    if (CHECK_BOUND_INDEX(index))
        p_prime[index] = l;
}

void PenduleDesc::setGravity(double g)
{
    if (g<0)
        throw SKError(ERR_NUMERICAL, "setGravity", "PenduleRessort", "trying to set to an incoherent value", false);
    this->g = g;
}

double PenduleDesc::energy() const
{
    double a(0.5*m[0]*l[0]*l[0]*p_prime[0]*p_prime[0]);
    double b(l[0]*l[0]*p_prime[0]*p_prime[0]);
    double c(l[1]*l[1]*p_prime[1]*p_prime[1]);
    double d(2*l[0]*l[1]*p_prime[0]*p_prime[1]*cos(p[0]-p[1]));
    double f(l[0] * m[0] * g * cos(p[0]));
    double h((l[1]*cos(p[1]) + l[0]*cos(p[0])) * m[1] * g);

    double e(a + 0.5*m[1]*(b + c + d));
    double u(-f - h);

    return (e+u);
}
