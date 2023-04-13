#ifndef INTEGRATORS_H
#define INTEGRATORS_H

#define INTEGRATION_ERR 1.0E-8
#define MAX_NEWMARK_LOOPS 10000;


/* fonctions d'integration pour les descriptor*/
namespace symkit
{
    template<typename T>
    void integrateEulerCromer(T&, T&, const T&, float);

    template<typename T, class Owner>
    using equation_f = T (Owner::*)(void) const;

    template<typename T, class Owner>
    void integrateNewmark(T&, T&, equation_f<T, Owner>, Owner *, float, double error = INTEGRATION_ERR);
}

#define __INTEGRATORS_TPP__
#include "integrators.tpp"
#undef __INTEGRATORS_TPP__

#endif // INTEGRATORS_H
