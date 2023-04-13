#include "penduleressort.h"
#include <cmath>


PenduleRessort::PenduleRessort(const std::vector<double>& p, const std::vector<double>& p_p, const double& k, const double& l, const double& m1, const double& m2, const double& fr1, const double& fr2, const double& g, integral_operation op)
    : Oscillateur(p, p_p, op), l(l), k(k), m1(m1), m2(m2), fr1(fr1), fr2(fr2), g(g)
{}

PenduleRessort::PenduleRessort(const Vector& p, const Vector& p_p, const double& k, const double& l, const double& m1, const double& m2, const double& fr1, const double& fr2, const double& g,integral_operation op)
    : Oscillateur(p, p_p, op), l(l), k(k), m1(m1), m2(m2), fr1(fr1), fr2(fr2), g(g)
{}

double PenduleRessort::getl() const
{
    return l;
}

double PenduleRessort::getk() const
{
    return k;
}

double PenduleRessort::getm1() const
{
    return m1;
}

double PenduleRessort::getm2() const
{
    return m2;
}

double PenduleRessort::getfr1() const
{
    return fr1;
}

double PenduleRessort::getfr2() const
{
    return fr2;
}

double PenduleRessort::getg() const
{
    return g;
}



void PenduleRessort::setl(const double& l)
{
    this->l=l;
}

void PenduleRessort::setk(const double& k)
{
    this->k=k;
}

void PenduleRessort::setm1(const double& m1)
{
    this->m1=m1;
}

void PenduleRessort::setm2(const double& m2)
{
    this->m2=m2;
}

void PenduleRessort::setfr1(const double& fr1)
{
    this->fr1=fr1;
}

void PenduleRessort::setfr2(const double& fr2)
{
    this->fr2=fr2;
}

void PenduleRessort::setg(const double& g)
{
    this->g=g;
}


double PenduleRessort::energy() const
{
    double k(0.5*m1*p_prime[0]*p_prime[0] + 0.5*m2*l*l*p_prime[1]*p_prime[1]);
    double u(0.5*k*p[0]*p[0] + m2*g*(1-cos(p[1])));

    return k+u;
}

/*
SVector<3> PenduleRessort::cartesiennes() const
{
      return { p[0], 0 , 0 };
}

SVector<3> PenduleRessort::cartesiennes2() const
{
    SVector<3> v({ sin(p[1]) * l, -cos(p[1]) * l, 0 });
    return cartesiennes() + v;
}
*/
Vector PenduleRessort::equation() const
{
    double a(m1 + m2*sin(p[1])*sin(p[1]));
    double b(k*p[0] + fr1*p_prime[0] - m2*l*p_prime[1]*p_prime[1]*sin(p[1]));
    double c(g*sin(p[1]) + fr2*p_prime[1]);

    return { (-b + m2*c*cos(p[1]))/a , (b*cos(p[1]) - (m1+m2)*c)/(l*a) };
}


