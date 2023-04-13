#include "pendulec.h"
#include <cmath>

double PenduleC::g = 9.81;

void PenduleC::setGravity(const double& g)
{
    PenduleC::g=g;
}


PenduleC::PenduleC(const Vector& p, const Vector& p_prime, const double& l, const double& m)
    : Oscillateur(p, p_prime), l(l), m(m)
{}

PenduleC::PenduleC(const std::vector<double>& p, const std::vector<double>& p_prime, const double& l, const double& m)
    : Oscillateur(p, p_prime), l(l), m(m)
{}

void PenduleC::setOtherPendule(const PenduleC * other)
{
    this->other=other;
}


double PenduleC::getl() const
{
    return l;
}

double PenduleC::getm() const
{
    return m;
}

void PenduleC::setl(const double& l)
{
    this->l=l;
}

void PenduleC::setm(const double& m)
{
    this->m=m;
}


Vector PenduleC::equation() const
{
    double a(mp()*g*cos(dteta())*sin(other->getp()[0]));
    double b((m+other->getm())*g*sin(p[0]));
    double c(m2()*l*p_prime[0]*p_prime[0]*cos(dteta())*sin(dteta()));
    double d(mp()*other->getl()*other->getp_prime()[0]*other->getp_prime()[0]*sin(dteta()));

    return { (a -b +c -d)/(l*m1() + l*m2()*sin(dteta())*sin(dteta())) };
}
