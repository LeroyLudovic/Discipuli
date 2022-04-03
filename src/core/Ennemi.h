#ifndef _ENNEMI
#define _ENNEMI

#include "Vecteur.h"

class Ennemi {

    private :

    unsigned int type;
    Vecteur position;
    float vitesse;

    public :
    double vie;

    Ennemi(int);

    ~Ennemi();

    void DevienFort();

    void Deplacement (Vecteur v);

    void BoostVitesse(float n);

    int PosX();

    int PosY();

};

#endif