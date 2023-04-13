#include "penduledesc.h"

PenduleDesc::PenduleDesc(double l1, double l2, double m1, double m2,
                         const Vector &p, const Vector &pp, double g)
    : Oscillateur(p, pp), g(g)
{
    l[0] = l1;
    l[1] = l2;

    m[0] = m1;
    m[1] = m2;
}

#define CHECK_BOUND_INDEX(index) index < 2 && index >= 0

void PenduleDesc::setLength(double l, int index)
{
    if (CHECK_BOUND_INDEX(index))
        this->l[index] = l;
}

void PenduleDesc::setMass(double m, int index)
{
    if (CHECK_BOUND_INDEX(index))
        this->m[index] = m;
}

double PenduleDesc::getLength(int index) const
{
    if (CHECK_BOUND_INDEX(index))
        return l[index];
    else
        return 0; // TODO, throw error
}

double PenduleDesc::getMass(int index) const
{
    if (CHECK_BOUND_INDEX(index))
        return m[index];
    else
        return 0; // TODO, throw error
}

double PenduleDesc::getAngle(int index) const
{
    if (CHECK_BOUND_INDEX(index))
        return getp()[index];
    else
        return 0; // TODO, throw error
}

double PenduleDesc::getAngularSpeed(int index) const
{
    if (CHECK_BOUND_INDEX(index))
        return getp_prime()[index];
    else
        return 0; // TODO, throw error
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
