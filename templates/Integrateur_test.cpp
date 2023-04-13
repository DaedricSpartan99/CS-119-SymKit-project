#include "pendules.h"
#include <iostream>

using namespace std;

//Fonction pour simulation écrite utilisant l'integrateur d'Euler Cromer
// (methode implementée dans la classe Oscillateur)

int symulate_euler(PenduleS &pend, const float &dt, float time = 10)
{
    cout << "   Debut simulation   " << endl;

    if (time > 10)
    {
        cout << "Temps de simulation trop eleve, change en 10s" << endl;
        time = 10;
    }
    
    cout << endl;

    double t(0);

    //Boucle pour afficher les valeurs actuelles de position et vitesse
    // et les mettre à jour à chaque pas de temps jusqu'à la fin du temps de simulation
    do {

        cout << " At time " << t << " :" << endl;

        cout << pend << endl;
       
        // Appelle la methode d'integration EulerCromer pour mettre à jour position et vitesse
        pend.update_EulerC(dt);

        t+=dt;

    } while(t <= time);

    cout << endl;
    cout << "    Fin simulation    " << endl;

    return 0;
}

//Fonction pour simulation écrite utilisant l'integrateur NewMark
// (methode implementée dans la classe Oscillateur)

int symulate_newmark(PenduleS &pend, const float &dt, float time = 10)
{
    cout << "   Debut simulation   " << endl;

    if (time > 10)
    {
        cout << "Temps de simulation trop eleve, change en 10s" << endl;
        time = 10;
    }
    
    cout << endl;

    double t(0);

    //Boucle pour afficher les valeurs actuelles de position et vitesse
    // et les mettre à jour à chaque pas de temps jusqu'à la fin du temps de simulation
    do {

        cout << " At time " << t << " :" << endl;

        cout << pend << endl;
       
        // Appelle la methode d'integration NewMark pour mettre à jour position et vitesse
        pend.update_NewMark(dt);

        t+=dt;

    } while(t <= time);

    cout << endl;
    cout << "    Fin simulation    " << endl;

    return 0;
}

//Definitions de constantes globale pour notre test

#ifndef M_PI
#define M_PI 3.141592654
#endif

const Vector p = { M_PI / 2 };
const Vector p_prime = { 0 };
const double l = 1.0;
const double m = 1.0;

const float dt = 0.02;

const float total_time = 20;

int main(int argc, char * argv[])
{
    PenduleS pendule(p, p_prime, l, m);


    //Simulation avec Euler Cromer
    symulate_euler(pendule, dt, total_time);
    cout << endl;

    //Simulation avec Newmark
    symulate_newmark(pendule, dt, total_time);
    
    // On pourra maintenant appeler comparer les deux methodes

    return 0;
}

