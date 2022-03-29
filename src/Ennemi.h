#ifndef _ENNEMI
#define _ENNEMI

#include "Vecteur.h"

class Ennemi {

    private :

    unsigned int type;
    Vecteur position;
    double vie;
    float vitesse;

    public :

    Ennemi(int);

    ~Ennemi();

    void DevienFort();

    void Deplacement (Vecteur v);

    void BoostVitesse(float n);

};

#endif