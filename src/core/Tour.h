#ifndef _TOUR
#define _TOUR

#include <iostream>
#include "Vecteur.h"

class Tour {

    private :

    Vecteur position;
    int prix;

    public :

    unsigned int type; 
    int degat;
    float vitesse;
    int portee;

    Tour(Vecteur,int);

    ~Tour();

    void Amelioration();

    int Vendre();

    int getX();

    int getY();

};

#endif