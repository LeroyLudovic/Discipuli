#ifndef _TOUR
#define _TOUR

#include <iostream>
#include "Vecteur.h"

class Tour {

    private :

    Vecteur position;
    int type;
    int typeT;  
    int prix;

    public :

    int degat;
    float vitesse;
    int portee;

    Tour(Vecteur,int);

    ~Tour();

    void Amelioration();

    int Vendre();

    int PosX();

    int PosY();

};

#endif