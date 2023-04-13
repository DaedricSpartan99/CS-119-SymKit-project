#include "oscillateur.h"
#include "integrators.h"
#include "skerror.h"
#include <ostream>

using namespace std;
using namespace symkit;

Oscillateur::Oscillateur(const Vector& p, const Vector& p_prime, integral_operation op)
    : p(p), p_prime(p_prime), op(op)
{}

Oscillateur::Oscillateur(const std::vector<double>& p, const std::vector<double>& p_prime, integral_operation op)
    : p(p), p_prime(p_prime), op(op)
{}

void Oscillateur::update(float dt)
{
    switch(op)
    {

    case EULER_CROMER:

        integrateEulerCromer<Vector>(p, p_prime, equation(), dt);
        break;

    case NEWMARK:

        integrateNewmark<Vector, Oscillateur>(p, p_prime, &Oscillateur::equation, this, dt);
        break;

    default:
        break;
    }
}

integral_operation Oscillateur::getIntegrationOperation() const
{
    return op;
}

void Oscillateur::setIntegrationOperation(integral_operation op)
{
    this->op = op;
}

Vector Oscillateur::getp() const
{
    return p;
}

Vector Oscillateur::getp_prime() const
{
    return p_prime;
}

void Oscillateur::setp(const Vector& p)
{
   this->p=p;
}

void Oscillateur::setp_prime(const Vector& p_prime)
{
    this->p_prime=p_prime;
}

//La methode qui défini l'affichage d'un oscillateur
void Oscillateur::affiche(ostream& out) const
{
    out << "Vecteur position :" << endl;
    out << p << endl;
    out << "Vecteur vitesse :" << endl;
    out << p_prime;
}

//La méthode qui corrige la dimension des vecteur vitesse et position si initialisés mal
void Oscillateur::adjust(size_t i)
{
    /* Corrige si plus petit */
    while(p.size()<i){
        p.augmente();
    }
    while(p_prime.size()<i){
        p_prime.augmente();
    }

    /* Corrige si plus grand */
    while(p.size()>i){
        p.decale();
    }
    while(p_prime.size()>i){
        p_prime.decale();
    }
}
