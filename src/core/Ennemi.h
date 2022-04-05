#ifndef _ENNEMI
#define _ENNEMI

#include "Vecteur.h"

class Ennemi {

    private :


    float vitesse;

    public :

    unsigned int type;
    Vecteur position;
    double vie;

    Ennemi(Vecteur, int);

    ~Ennemi();

    void DevienFort();

    void lvlUp();

    void Deplacement (Vecteur v);

    void BoostVitesse(float n);

    int PosX();

    int PosY();

};

#endif