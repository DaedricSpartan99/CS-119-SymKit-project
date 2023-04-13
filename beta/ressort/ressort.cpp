#include "ressort.h"
#include <cmath>
#include <iostream>

using namespace std;

Ressort::Ressort(const Vector& p, const Vector& p_prime, const Vector& axe, const double& l,const double& m,const double& k, const double& fr, const double& g, integral_operation op)
    : OscillateurSimple(p, p_prime, op), k(k), fr(fr), l(l), m(m), g(g), axe(axe.unit())
{
    adjust(1); // corrige la dimension de vitesse et position
}

Ressort::Ressort(const std::vector<double>& p, const std::vector<double>& p_prime, const std::vector<double>& axe, const double& l,const double& m,const double& k, const double& fr, const double& g, integral_operation op)
    : OscillateurSimple(p, p_prime, op), k(k), fr(fr), l(l), m(m), g(g)
{
    this->setAxe(Vector(axe)); // rends l'axe de direction unitaire, pour faciliter les calculs de projection

    adjust(1);  // corrige la dimension de vitesse et position
}

Vector Ressort::equation() const
{
    Vector y({0,-g,0});

    return {-(k/m)*(p[0]-l)-(fr/m)*p_prime[0]+y*axe};
}



double Ressort::getk() const
{
    return k;
}

double Ressort::getg() const
{
    return g;
}

double Ressort::getl() const
{
    return l;
}

double Ressort::getfr() const
{
    return fr;
}

double Ressort::getm() const
{
    return m;
}

/*
SVector<3> Ressort::getOrigine() const
{
    return origine;
}
*/

const Vector& Ressort::getAxe() const
{
    return axe;
}


#include "skerror.h"

using namespace symkit;
//pour lancer des erreurs en cas de valeurs physiquement incohèrente


void Ressort::setk(const double& k)
{
    if (k<0)
        throw SKError(ERR_NUMERICAL, "setk", "PenduleRessort", "trying to set to an incoherent value", false);
    this->k=k;
}

void Ressort::setfr(const double& fr)
{
    if (fr<0)
        throw SKError(ERR_NUMERICAL, "setfr", "Ressort", "trying to set to an incoherent value", false);
    this->fr=fr;
}

void Ressort::setl(const double& l)
{
    this->l=l;
}

void Ressort::setm(const double& m)
{
    if (m<=0)
        throw SKError(ERR_NUMERICAL, "setm", "Ressort", "trying to set to an incoherent value", false);
    this->m=m;
}

void Ressort::setg(const double& g)
{
    if (g<0)
        throw SKError(ERR_NUMERICAL, "setg", "Ressort", "trying to set to an incoherent value", false);
    this->g=g;
}


/*void Ressort::setOrigine(const std::vector<double>& origine)
{
    this->origine=origine;
}
*/
/*
void Ressort::setOrigine(const SVector<3>& v)
{
    origine=v;
}
*/

void Ressort::setAxe(const Vector & v)
{
    axe = v.unit(); // set l'axe de direction à la reduction unitaire du vecteur en argument
}


SVector<3> Ressort::cartesiennes() const
{

    double x, y, z;
    Vector xi({1,0,0}), yi({0,1,0}), zi({0,0,1});

    x=((axe*p[0])*xi);
    y=((axe*p[0])*yi);
    z=((axe*p[0])*zi);

    return {x, y, z}; // retourne le vecteur position du ressort
}

double Ressort::kineticEnergy() const
{
    return 0.5 * m * p_prime.sq_module();
}
