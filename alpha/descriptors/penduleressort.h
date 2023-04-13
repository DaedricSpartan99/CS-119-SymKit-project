#ifndef PENDULERESSORT_H
#define PENDULERESSORT_H

#include "descriptors/oscillateur.h"

class PenduleRessort : public Oscillateur
{
public:
    /* Constructeurs */
    PenduleRessort(const Vector& p,
               const Vector& p_p,
               const double& k, const double& l,
               const double& m1, const double& m2,
               const double& fr1 = 0, const double& fr2 = 0,
               const double& g = 9.81,
               integral_operation op = NEWMARK);

    PenduleRessort(const std::vector<double>& p,
               const std::vector<double>& p_p,
               const double& k, const double& l,
               const double& m1, const double& m2,
               const double& fr1 = 0, const double& fr2 = 0,
               const double& g = 9.81,
               integral_operation op = NEWMARK);

    /* Accesseurs */
    double getl() const;
    double getk() const;
    double getm1() const;
    double getm2() const;
    double getg() const;
    double getfr1() const;
    double getfr2() const;

    /* Manipulateurs */
    void setl(const double&);
    void setk(const double&);
    void setm1(const double&);
    void setm2(const double&);
    void setg(const double&);
    void setfr1(const double&);
    void setfr2(const double&);

    /* Calcule l'energie du système */
    double energy() const;


private:

    /* Attributs */

    double l;
    double k;
    double m1;
    double m2;
    double fr1;
    double fr2;
    double g;

    /* Equation caractérisant le mouvement d'un Pendule Couplé */
    virtual Vector equation() const override;
};


#endif // PENDULERESSORT_H
