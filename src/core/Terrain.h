#ifndef _TERRAIN
#define _TERRAIN

#include "Vecteur.h"

class Terrain{
    private :

        const int Largeur = 10;
        const int Longeur = 40;
        char tab[10][40];
    
    public :

        int depart;

        Terrain();

        ~Terrain();

        void generation();

        Vecteur prochaineCase(Vecteur);

        char getCase(int,int);

        int getX();

        int getY();
};

    
#endif