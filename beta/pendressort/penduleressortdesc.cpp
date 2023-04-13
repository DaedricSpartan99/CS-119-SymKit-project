#include "penduleressortdesc.h"
#include <cmath>


PenduleRessort::PenduleRessort(const std::vector<double>& p, const std::vector<double>& p_p, const double& k, const double& l, const double& m1, const double& m2, const double& fr1, const double& fr2, const double& g, integral_operation op)
    : Oscillateur(p, p_p, op), k(k), l(l), g(g)
{
    m[0] = m1;
    m[1] = m2;

    fr[0] = fr1;
    fr[1] = fr2;

    //corriger la dimension de position et vitesse
    adjust(2);
}

PenduleRessort::PenduleRessort(const Vector& p, const Vector& p_p, const double& k, const double& l, const double& m1, const double& m2, const double& fr1, const double& fr2, const double& g,integral_operation op)
    : Oscillateur(p, p_p, op), k(k), l(l), g(g)
{
    m[0] = m1;
    m[1] = m2;

    fr[0] = fr1;
    fr[1] = fr2;

    //corriger la dimension de position et vitesse
    adjust(2);
}

double PenduleRessort::getLenght() const
{
    return l;
}

double PenduleRessort::getk() const
{
    return k;
}

#define CHECK_BOUND_INDEX(index) index < 2 && index >= 0

#include "skerror.h"

using namespace symkit;

double PenduleRessort::getMass(int index) const
{
    if (CHECK_BOUND_INDEX(index))
        return m[index];
    else
        throw SKError(ERR_BOUND, "getMass", "PenduleRessort", "Looking for a non-existing value", false);
}

double PenduleRessort::getFrottement(int index) const
{
    if (CHECK_BOUND_INDEX(index))
        return fr[index];
    else
        throw SKError(ERR_BOUND, "getFrottement", "PenduleRessort", "Looking for a non-existing value", false);
}

double PenduleRessort::getg() const
{
    return g;
}


//SKerror pour lancer des erreurs en cas de valeurs physiquement incohèrente...

void PenduleRessort::setLenght(const double& l)
{
    if (l<=0)
        throw SKError(ERR_NUMERICAL, "setLenght", "PenduleRessort", "trying to set to an incoherent value", false);
    this->l=l;
}

void PenduleRessort::setk(const double& k)
{
    if (k<0)
        throw SKError(ERR_NUMERICAL, "setk", "PenduleRessort", "trying to set to an incoherent value", false);
    this->k=k;
}

void PenduleRessort::setMass(const double& m, int index)
{
    if (m<=0)
        throw SKError(ERR_NUMERICAL, "setMass", "PenduleRessort", "trying to set to an incoherent value", false);
    if (CHECK_BOUND_INDEX(index))
        this->m[index] = m;
    else
        throw SKError(ERR_BOUND, "setMass", "PenduleRessort", "Looking for a non-existing memory-buffer", false);
}

void PenduleRessort::setFrottement(const double& fr, int index)
{
    if (fr<0)
        throw SKError(ERR_NUMERICAL, "setFrottement", "PenduleRessort", "trying to set to an incoherent value", false);
    if (CHECK_BOUND_INDEX(index))
        this->fr[index] = fr;
    else
        throw SKError(ERR_BOUND, "setFrottement", "PenduleRessort", "Looking for a non-existing memory-buffer", false);
}

void PenduleRessort::setg(const double& g)
{
    if (g<0)
        throw SKError(ERR_NUMERICAL, "setLenght", "PenduleRessort", "trying to set to an incoherent value", false);
    this->g=g;
}

void PenduleRessort::setPenduleAngle(double value)
{
    p[1] = value;
}

void PenduleRessort::setPenduleSpeed(double value)
{
    p_prime[1] = value;
}

void PenduleRessort::setRessortPosition(double value)
{
    p[0] = value;
}

void PenduleRessort::setRessortSpeed(double value)
{
    p_prime[0] = value;
}


double PenduleRessort::getPenduleAngle() const
{
    return p[1];
}

double PenduleRessort::getPenduleSpeed() const
{
    return p_prime[1];
}

double PenduleRessort::getRessortPosition() const
{
    return p[0];
}

double PenduleRessort::getRessortSpeed() const
{
    return p_prime[0];
}


Vector PenduleRessort::equation() const
{
    double a(m[0] + m[1]*sin(p[1])*sin(p[1]));
    double b(k*p[0] + fr[0]*p_prime[0] - m[1]*l*p_prime[1]*p_prime[1]*sin(p[1]));
    double c(g*sin(p[1]) + fr[1]*p_prime[1]);

    return { (-b + m[1]*c*cos(p[1]))/a , (b*cos(p[1]) - (m[0]+m[1])*c)/(l*a) };
}

double PenduleRessort::energy() const
{
    double u(0.5 * p[0]*p[0]*k + m[1]*g*l * (1 -cos(p[1])));

    return ressortKineticEnergy() + penduleKineticEnergy() + u;
}

double PenduleRessort::ressortKineticEnergy() const
{
    return 0.5 * m[0] * p_prime[0] * p_prime[0];
}

double PenduleRessort::penduleKineticEnergy() const
{
    double out(0);

    out += p_prime[0] * p_prime[0];
    out += 2 * l * p_prime[0] * p_prime[1] * cos(p[1]);
    out += l * l * p_prime[1] * p_prime[1];

    return 0.5 * m[1] * out;
}
