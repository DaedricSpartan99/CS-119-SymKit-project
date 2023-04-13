#ifndef RESSORT_H_
#define RESSORT_H_

#include "descriptors/oscillateursimple.h"

class Ressort : public OscillateurSimple
{
public:

    /* Constructeurs */
    Ressort(const Vector& p, const Vector& p_prime, const Vector& axe, const double& l, const double& m, const double& k, const double& fr = 0, const double& g = 9.81, integral_operation op = NEWMARK);

    Ressort(const std::vector<double>& p, const std::vector<double>& p_prime, const std::vector<double>& axe, const double& l, const double& m, const double& k, const double& fr = 0, const double& g = 9.81, integral_operation op = NEWMARK);

    ~Ressort() {}

    /* Accesseurs */
    double getk() const;
    double getl() const;
    double getfr() const;
    double getm() const;
    double getg() const;

    //SVector<3> getOrigine() const;
    const Vector& getAxe() const;

    /* Manipulateurs */
    void setk(const double&);
    void setfr(const double&);
    void setl(const double&);
    void setm(const double&);
    void setg(const double&);

    //void setOrigine(const std::vector<double>& origine);
   //void setOrigine(const SVector<3>&);
    void setAxe(const Vector&);

    /* Pour convertir le vecteur de position p
     * dans un vecteur à cordonnées cartesiennes
     * important pour notre implementation graphique
     * travailliant sur des SVector de dimension 3
     */
    virtual SVector<3> cartesiennes() const override;

    double kineticEnergy() const;

private:

    double k;
    double fr;
    double l;
    double m;
    double g;
   // SVector<3> origine;

    /* Important!!!
     * Axe long lequel se déplace la masse, décrit par un vecteur
     * Vecteur (toujours unitaire, pour faciliter les calculs)
     * donnant la direction de déplacement de la masse
     */
    Vector axe;

    /* Equation caractérisant le mouvement d'un Ressort contraint à un axe de mouvement */
    virtual Vector equation() const override;
};



#endif
