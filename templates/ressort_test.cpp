#include "ressort.h"
#include <iostream>

using namespace std;

//Fonction pour la simulation écrite du pendule

int symulate(Ressort &res, const float &dt, float time = 10)
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
        cout << res << endl;
       
        // on appelle update lequel met à jour les vecteur position et vitesse
        res.update(dt);

        t+=dt;

    } while(t <= time);

    cout << endl;
    cout << "    Fin simulation    " << endl;

    return 0;
}

//definition de variables globales pour le test de simulation

const Vector p = { 0.18 };
const Vector p_prime = { 0 };
const double l = 0.0;
const double m = 0.25;
const double k = 0.33;
const double fr = 0.15;
const Vector axe = {0.8, 0, 0.6};

const float dt = 0.01;

const float total_time = 0.5;

int main(int argc, char * argv[])
{
    Ressort res(p, p_prime, axe, l, m, k, fr);

    // test simulation écrite
    return symulate(res, dt, total_time);
}

