#ifndef PENDULEC1_H
#define PENDULEC1_H

#include "pendulec.h"

/* Forward declaration */
class PenduleC2;

/* Premier pendule de la couple */

class PenduleC1 : public PenduleC
{
public:

    /* Constructeurs (qui appellent juste celui de "PenduleC" ) */
    PenduleC1(const Vector&, const Vector&, const double&, const double&);

    PenduleC1(const std::vector<double>&, const std::vector<double>&, const double&, const double&);

    /* Override des fonctions pour la désimbiguation des paramètres dans la fonction "equation"
     * Pour qu'à chaque sous classe de PenduleC corresponde la bonne equation differentielle
     */
    virtual double mp() const override;
    virtual double ms() const override;
    virtual double mt() const override;
    virtual double dteta() const override;
    virtual double m2() const override;
    virtual double m1() const override;

    /* Convertit position en un SVector<3> pour l'implementation graphique */
    virtual SVector<3> cartesiennes() const override;

    virtual void setOtherPendule(const PenduleC*) override;

    /* Fonction qui specifie le type */
    virtual unsigned int getnom() const override;

};

#endif // PENDULEC1_H
