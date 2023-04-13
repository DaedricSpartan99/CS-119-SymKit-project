#ifndef PENDULEC_H
#define PENDULEC_H

#include "descriptors/oscillateur.h"

class PenduleC : public Oscillateur
{
public:

    /* Constructeurs */
    PenduleC(const Vector&, const Vector&, const double&, const double&);

    PenduleC(const std::vector<double>&, const std::vector<double>&, const double&, const double&);

    virtual void setOtherPendule(const PenduleC*);

    /* Accesseurs */
    double getl() const;
    double getm() const;

    /* Manipulateurs */
    void setl(const double&);
    void setm(const double&);

    /* Set de la gravité pour tout Pendule couplé */
    static void setGravity(const double&);

    /* Fonction qui specifie le type */
    virtual unsigned int getnom() const = 0;


    static double g;

protected:

    /* Fonctions qui spécifient (pour chaque sous-classe) les bonnes paramétres
     * pour la fonction "equation", donc pour l'evolution de chaqu'un des deux pendules.
     */
    virtual double mp() const = 0;
    virtual double dteta() const = 0;
    virtual double m2() const = 0;
    virtual double m1() const = 0;

    /* Reference à autre pendule avec qui il est couplé (pour accèder à ses attributs) */
    const PenduleC * other;

private:

    double l;
    double m;

    /* Equation caractérisant le mouvement d'un Pendule Couplé */
    virtual Vector equation() const override;
};

#endif // PENDULECOUPLE_H
