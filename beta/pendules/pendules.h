#ifndef PENDULES_H_
#define PENDULES_H_

#include "descriptors/oscillateursimple.h"

class PenduleS : public OscillateurSimple
{
public:

    /* Constructeurs */
    PenduleS(   const Vector& p,
                const Vector& p_prime,
                const double& l,
                const double& m,
                const double& fr = 0,
                const double& g = 9.81,
                integral_operation op = NEWMARK);

    PenduleS(const std::vector<double>& p,
             const std::vector<double>& p_prime,
             const double& l,
             const double& m,
             const double& fr = 0,
             const double& g = 9.81,
             integral_operation op = NEWMARK);

    /* Accesseurs */
    double getg() const;
    double getl() const;
    double getfr() const;
    double getm() const;

    /* Manipulateurs */
    void setg(const double&);
    void setfr(const double&);
    void setl(const double&);
    void setm(const double&);

    /* Convertit position en un SVector<3> pour l'implementation graphique */
    virtual SVector<3> cartesiennes() const override;

    double kineticEnergy() const;

private:

    double g;
    double fr;
    double l;
    double m;

    /* Equation caractérisant le mouvement d'un Pendule Simple */
    virtual Vector equation() const override;
};



#endif
