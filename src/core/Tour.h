#ifndef _TOUR
#define _TOUR

#include <iostream>
#include "Vecteur.h"

class Tour {

    private :

    Vecteur position;
    int prix;
    float chargement;

    public :

    unsigned int type; 
    int degat;
    float vitesse;
    int portee;
    int prixUpgrade;
    int upgrade;

    Tour(Vecteur,int);

    ~Tour();

    // ne pas enlever ça casse tout
    void Amelioration();

    bool Charg();

    // ne pas enlever ça casse tout
    int Vendre();

    int getX();

    int getY();

};

#endif