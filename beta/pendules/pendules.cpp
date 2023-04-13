#include "pendules.h"
#include <cmath>

using namespace std;

PenduleS::PenduleS(const Vector& p, const Vector& p_prime , const double& l, const double& m, const double& fr, const double& g, integral_operation op)
    : OscillateurSimple(p, p_prime, op), g(g), fr(fr), l(l), m(m)
{
    adjust(1); // corrige dimension de vitesse et position
}

PenduleS::PenduleS(const std::vector<double>& p, const std::vector<double>& p_prime, const double& l, const double& m, const double& fr, const double& g, integral_operation op)
    : OscillateurSimple(p, p_prime, op), g(g), fr(fr), l(l), m(m)
{
    adjust(1); // corrige dimension de vitesse et position
}

Vector PenduleS::equation() const
{
    return { -(g/l) * sin(p[0]) - (fr/(m*l*l)) * p_prime[0] };
}

#include <cmath>

SVector<3> PenduleS::cartesiennes() const
{
    return { sin(p[0]) * l, -cos(p[0]) * l, 0 }; //retourne vecteur position euclidian du pendule
}


double PenduleS::getg() const
{
    return g;
}

double PenduleS::getl() const
{
    return l;
}

double PenduleS::getfr() const
{
    return fr;
}

double PenduleS::getm() const
{
    return m;
}

#include "skerror.h"

using namespace symkit;
//pour lancer des erreurs en cas de valeurs physiquement incohèrente

void PenduleS::setg(const double& g)
{
    if (g<0)
        throw SKError(ERR_NUMERICAL, "setg", "PenduleS", "trying to set to an incoherent value", false);
    this->g=g;
}

void PenduleS::setfr(const double& fr)
{
    if (fr<0)
        throw SKError(ERR_NUMERICAL, "setfr", "PenduleS", "trying to set to an incoherent value", false);
    this->fr=fr;
}

void PenduleS::setl(const double& l)
{
    if (l<=0)
        throw SKError(ERR_NUMERICAL, "setl", "PenduleS", "trying to set to an incoherent value", false);
    this->l=l;
}

void PenduleS::setm(const double& m)
{
    if (m<=0)
        throw SKError(ERR_NUMERICAL, "setl", "PenduleS", "trying to set to an incoherent value", false);
    this->m=m;
}

double PenduleS::kineticEnergy() const
{
    return 0.5 * m * l * l * p_prime.sq_module();
}
