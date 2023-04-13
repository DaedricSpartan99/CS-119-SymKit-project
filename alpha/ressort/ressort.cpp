#include "ressort.h"
#include <cmath>
#include <iostream>

// TODO gérer erreur (dimension differentes etc.)

using namespace std;

Ressort::Ressort(const Vector& p, const Vector& p_prime, const Vector& axe, const double& l,const double& m,const double& k, const double& fr, const double& g, integral_operation op)
    : OscillateurSimple(p, p_prime, op), k(k), fr(fr), l(l), m(m), g(g), axe(axe.unit())
{

}

Ressort::Ressort(const std::vector<double>& p, const std::vector<double>& p_prime, const std::vector<double>& axe, const double& l,const double& m,const double& k, const double& fr, const double& g, integral_operation op)
    : OscillateurSimple(p, p_prime, op), k(k), fr(fr), l(l), m(m), g(g), axe(axe)
{
    this->setAxe(axe);    
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

Vector Ressort::getAxe() const
{
    return axe;
}


void Ressort::setk(const double& k)
{
    this->k=k;
}

void Ressort::setfr(const double& fr)
{
    this->fr=fr;
}

void Ressort::setl(const double& l)
{
    this->l=l;
}

void Ressort::setm(const double& m)
{
    this->m=m;
}

void Ressort::setg(const double& g)
{
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
    axe = v.unit();
}


SVector<3> Ressort::cartesiennes() const
{

    double x, y, z;
    Vector xi({1,0,0}), yi({0,1,0}), zi({0,0,1});

    x=((axe*p[0])*xi);
    y=((axe*p[0])*yi);
    z=((axe*p[0])*zi);

    /* Pour simplifier le deplacement du système (Ressort) dans l'espace graphique, en fonction d'où l'on choisit son origine
     * on fait intervenir le vecteur origine ici, ainsi on pourra voir sur la simulation graphique cette translation
     * Lorsque l'on imprime la position en simulation textuelle, cela affichera de toute façon la distance de l'origine
     * suivant l'axe de déplacement du ressort.
     * Cette position cartesienne sera donc implicite, dans le cas d'une simulation textuelle

    x+=origine[0];
    y+=origine[1];
    z+=origine[2];

    */

    return {x, y, z};
}
