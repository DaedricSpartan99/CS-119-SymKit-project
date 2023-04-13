#ifndef OSCILLATEUR_H_
#define OSCILLATEUR_H_

#include "vector.h"
#include <initializer_list>
#include "descriptor.h"
#include <iosfwd>

enum integral_operation
{
    EULER_CROMER,
    NEWMARK
};

class Oscillateur : public Descriptor {

protected:

    /* Vecteur contenant les paramètres libres de l'oscillateur */
    Vector p;

    /* Vecteur derivee de p */
    Vector p_prime;

    /* Foction caracterisant chaque oscillateur
     * Definie virtuelle, une fonction concrète
     * pour chaque sous classe de "Oscillateur"
     * sera implementée.
     */
    virtual Vector equation() const = 0;

    /* Pour corriger la dimension des vecteurs position et vitesse */
    void adjust(std::size_t);

private:

    integral_operation op;

    virtual void update(float) override;

public:

    /* Constructeurs pour affecter les vecteurs p et p_prime
     * en exploitant les constructeurs implementés dans la
     * classe Vector
     */
    Oscillateur(const Vector& p, const Vector& p_prime, integral_operation op = NEWMARK);

    Oscillateur(const std::vector<double>&, const std::vector<double>&, integral_operation op = NEWMARK);

    /* Accesseurs */
    Vector getp() const;
    Vector getp_prime() const;

    /* Manipulateurs */

    void setp(const Vector&);
    void setp_prime(const Vector&);

    /*
     * Accesseurs et Manipulateur pour le choix de l'integrateur
     */

    integral_operation getIntegrationOperation() const;

    void setIntegrationOperation(integral_operation op);

    /* Pour l'affichage des attributs position et vitesse du descriptor*/
    virtual void affiche(std::ostream&) const override;
};

#endif
