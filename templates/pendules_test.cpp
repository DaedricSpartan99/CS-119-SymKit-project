#include "pendules.h"
#include <iostream>

using namespace std;

//Fonction pour la simulation écrite du pendule

int symulate(PenduleS &pend, const float &dt, float time = 10)
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

        // on affiche les nouvelles valeurs de position et vitesse du pendule
        cout << pend << endl;
       
        // on appelle update lequel met à jour les vecteur position et vitesse
        pend.update(dt);

        t+=dt;

    } while(t <= time);

    cout << endl;
    cout << "    Fin simulation    " << endl;

    return 0;
}

//definition de variables globales pour le test de simulation

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

    // test simulation écrite
    return symulate(pendule, dt, total_time);
}

