#include "pendulec1.h"

PenduleC1::PenduleC1(const Vector& p, const Vector& p_prime, const double& l, const double& m)
    : PenduleC(p, p_prime, l, m)
{}

PenduleC1::PenduleC1(const std::vector<double>& p, const std::vector<double>& p_prime, const double& l, const double& m)
    : PenduleC(p, p_prime, l, m)
{}

double PenduleC1::mp() const
{
    return other->getm();
}

double PenduleC1::ms() const
{
    return -(other->getm());
}

double PenduleC1::mt() const
{
    return ms();
}

double PenduleC1::dteta() const
{
    return p[0] -other->getp()[0];
}

double PenduleC1::m1() const
{
    return getm();
}

double PenduleC1::m2() const
{
    return other->getm();
}

SVector<3> PenduleC1::cartesiennes() const
{
    return { sin(p[0]) * getl(), -cos(p[0]) * getl(), 0 };
}

unsigned int PenduleC1::getnom() const
{
    return 1;
}

#include "skerror.h"

using namespace symkit;

void PenduleC1::setOtherPendule(const PenduleC* penduler)
{
    if (!penduler)
        throw SKError(ERR_INIT, "setOtherPedule", "PenduleC1", "Tryng to link a nullreference to a pendulec1", 1);
    if((penduler->getnom() == 1))
        throw SKError(ERR_INIT, "setOtherPedule", "PenduleC1", "Tryng to link a pendulec1 to a pendulec1", 1);
    PenduleC::setOtherPendule(penduler);
}
