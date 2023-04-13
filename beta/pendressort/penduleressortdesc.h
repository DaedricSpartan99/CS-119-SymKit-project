#ifndef PENDULERESSORTDESC_H
#define PENDULERESSORTDESC_H

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
    double getLenght() const;
    double getk() const;
    double getMass(int index) const;
    double getg() const;
    double getFrottement(int index) const;

    double getPenduleAngle() const;
    double getPenduleSpeed() const;

    double getRessortPosition() const;
    double getRessortSpeed() const;

    /* Manipulateurs */
    void setLenght(const double&);
    void setk(const double&);
    void setMass(const double& m, int index);
    void setg(const double&);
    void setFrottement(const double& fr, int index);

    void setPenduleAngle(double);
    void setPenduleSpeed(double);

    void setRessortPosition(double);
    void setRessortSpeed(double);

    double energy() const;

    double ressortKineticEnergy() const;
    double penduleKineticEnergy() const;

private:

    /* Attributs */

    double k;
    double l;
    double g;
    double m[2];
    double fr[2];

    /* Equation caractérisant le mouvement d'un Pendule-Ressort */
    virtual Vector equation() const override;
};


#endif // PENDULERESSORTDESC_H
