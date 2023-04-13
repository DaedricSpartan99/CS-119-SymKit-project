#include "pendules.h"
#include <cmath>

// TODO gérer erreur (dimension differentes etc.)

using namespace std;

PenduleS::PenduleS(const Vector& p, const Vector& p_prime , const double& l, const double& m, const double& fr, const double& g, integral_operation op)
    : OscillateurSimple(p, p_prime, op), g(g), fr(fr), l(l), m(m)
{

}

PenduleS::PenduleS(const std::vector<double>& p, const std::vector<double>& p_prime, const double& l, const double& m, const double& fr, const double& g, integral_operation op)
    : OscillateurSimple(p, p_prime, op), g(g), fr(fr), l(l), m(m)
{

}

Vector PenduleS::equation() const
{
    return { -(g/l) * sin(p[0]) - (fr/(m*l*l)) * p_prime[0] };
}

#include <cmath>

SVector<3> PenduleS::cartesiennes() const
{
    return { sin(p[0]) * l, -cos(p[0]) * l, 0 };
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

void PenduleS::setg(const double& g)
{
    this->g=g;
}

void PenduleS::setfr(const double& fr)
{
    this->fr=fr;
}

void PenduleS::setl(const double& l)
{
    this->l=l;
}

void PenduleS::setm(const double& m)
{
    this->m=m;
}

