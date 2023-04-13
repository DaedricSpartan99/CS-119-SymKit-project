#include "pendulec2.h"

PenduleC2::PenduleC2(const Vector& p, const Vector& p_prime, const double& l, const double& m)
    : PenduleC(p, p_prime, l, m)
{}

PenduleC2::PenduleC2(const std::vector<double>& p, const std::vector<double>& p_prime, const double& l, const double& m)
    : PenduleC(p, p_prime, l, m)
{}

double PenduleC2::mp() const
{
    return getm()+ other->getm();
}

double PenduleC2::dteta() const
{
    return  other->getp()[0] -p[0];
}

double PenduleC2::m1() const
{
    return other->getm();
}

double PenduleC2::m2() const
{
    return getm();
}


SVector<3> PenduleC2::cartesiennes() const
{
    SVector<3> v({ sin(p[0]) * getl(), -cos(p[0]) * getl(), 0 });
    return other->cartesiennes() + v;
}

unsigned int PenduleC2::getnom() const
{
    return 2;
}

#include "skerror.h"

using namespace symkit;

void PenduleC2::setOtherPendule(const PenduleC* penduler)
{
    if (!penduler)
        throw SKError(ERR_INIT, "setOtherPedule", "PenduleC2", "Tryng to link a nullreference to a pendulec2", 1);
    if((penduler->getnom() == 2))
        throw SKError(ERR_INIT, "setOtherPedule", "PenduleC2", "Tryng to link a pendulec2 to a pendulec2", 1);
    PenduleC::setOtherPendule(penduler);
}
