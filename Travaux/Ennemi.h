#ifndef _ENNEMI
#define _ENNEMI

#include "Vecteur.h"

class Ennemi {

    private :

    unsigned int type;
    Vecteur position;
    double int vie;
    float vitesse;

    public :

    Ennemi();

    ~Ennemi();

    void DevienFort();

    Vecteur Deplacement (Vecteur v);

    void BoostVitesse(float n);

};